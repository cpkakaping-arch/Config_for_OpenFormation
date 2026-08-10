#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define VERSION "0.1.0"

/* =========================================================
 * STRUCTURE D'UN OUTIL
 * ========================================================= */

typedef struct {
    const char *package;
    const char *command;
} Tool;


/* =========================================================
 * OUTILS CONFIGURATION C
 * ========================================================= */

Tool c_tools[] = {

    /* Outils de base */
    {"coreutils", "ls"},
    {"util-linux", "lsblk"},
    {"findutils", "find"},
    {"diffutils", "diff"},
    {"grep", "grep"},
    {"gawk", "awk"},
    {"sed", "sed"},
    {"tar", "tar"},
    {"gzip", "gzip"},
    {"bzip2", "bzip2"},
    {"xz-utils", "xz"},
    {"zip", "zip"},
    {"unzip", "unzip"},
    {"p7zip", "7z"},
    {"which", "which"},
    {"file", "file"},
    {"tree", "tree"},
    {"less", "less"},
    {"man", "man"},
    {"procps", "ps"},
    {"termux-tools", "termux-info"},

    /* Développement C/C++ */
    {"clang", "clang"},
    {"make", "make"},
    {"cmake", "cmake"},
    {"ninja", "ninja"},
    {"binutils", "objdump"},
    {"lld", "ld.lld"},

    /* LLVM */
    {"llvm", "llvm-ar"},

    /* Debug */
    {"gdb", "gdb"},
    {"lldb", "lldb"}
};

#define C_TOOLS_COUNT (sizeof(c_tools) / sizeof(c_tools[0]))


/* =========================================================
 * UTILITAIRES
 * ========================================================= */

void clear_screen(void)
{
    system("clear");
}


void pause_screen(void)
{
    printf("\nAppuyez sur Entrée pour continuer...");
    getchar();
}


/*
 * Demande une confirmation à l'utilisateur.
 */
int ask_confirmation(const char *question)
{
    char answer[16];

    printf("\n%s [o/N] : ", question);

    if (fgets(answer, sizeof(answer), stdin) == NULL)
        return 0;

    return (
        answer[0] == 'o' ||
        answer[0] == 'O' ||
        answer[0] == 'y' ||
        answer[0] == 'Y'
    );
}


/*
 * Vérifie si une commande existe dans le PATH.
 */
int command_exists(const char *command)
{
    char test[256];

    snprintf(
        test,
        sizeof(test),
        "command -v %s >/dev/null 2>&1",
        command
    );

    return system(test) == 0;
}


/*
 * Vérifie si nous sommes bien dans Termux.
 */
int is_termux(void)
{
    const char *prefix = getenv("PREFIX");

    if (prefix == NULL)
        return 0;

    return strstr(prefix, "com.termux") != NULL;
}


/* =========================================================
 * INSTALLATION
 * ========================================================= */

int install_package(const Tool *tool)
{
    char command[512];

    printf("\n------------------------------------------\n");
    printf("[!] %s n'est pas installé.\n", tool->package);

    if (!ask_confirmation("Voulez-vous l'installer ?"))
    {
        printf("[SKIP] %s ignoré.\n", tool->package);
        return 0;
    }

    printf("[...] Installation de %s...\n", tool->package);

    /*
     * Pas de -y :
     * Termux pourra demander lui-même confirmation.
     */
    snprintf(
        command,
        sizeof(command),
        "pkg install %s",
        tool->package
    );

    int result = system(command);

    if (result != 0)
    {
        printf("[ERREUR] Impossible d'installer %s.\n",
               tool->package);

        return 0;
    }

    if (command_exists(tool->command))
    {
        printf("[OK] %s installé.\n", tool->package);
        return 1;
    }

    printf("[!] Installation terminée mais commande non trouvée : %s\n",
           tool->command);

    return 0;
}


/* =========================================================
 * CONFIGURATION C
 * ========================================================= */

void configure_c(void)
{
    size_t i;

    clear_screen();

    printf("==========================================\n");
    printf("       CONFIGURATION C / C++\n");
    printf("==========================================\n\n");

    printf("Cette configuration va vérifier :\n");
    printf("- outils système\n");
    printf("- compilateur C\n");
    printf("- outils de compilation\n");
    printf("- LLVM\n");
    printf("- débogueurs\n\n");

    if (!ask_confirmation("Commencer la configuration ?"))
        return;

    for (i = 0; i < C_TOOLS_COUNT; i++)
    {
        Tool *tool = &c_tools[i];

        if (command_exists(tool->command))
        {
            printf("[OK] %-15s déjà installé\n",
                   tool->package);
        }
        else
        {
            install_package(tool);
        }
    }

    printf("\n==========================================\n");
    printf("       CONFIGURATION TERMINÉE\n");
    printf("==========================================\n");

    pause_screen();
}


/* =========================================================
 * MISE À JOUR
 * ========================================================= */

void update_system(void)
{
    clear_screen();

    printf("==========================================\n");
    printf("              MISE À JOUR\n");
    printf("==========================================\n\n");

    printf("Termux va mettre à jour ses dépôts et\n");
    printf("les paquets installés.\n\n");

    if (!ask_confirmation("Voulez-vous continuer ?"))
        return;

    printf("\n[...] Mise à jour des dépôts...\n");

    system("pkg update");

    printf("\n[...] Mise à jour des paquets...\n");

    system("pkg upgrade");

    printf("\n[OK] Mise à jour terminée.\n");

    pause_screen();
}


/* =========================================================
 * VERIFICATION ENVIRONNEMENT
 * ========================================================= */

void check_environment(void)
{
    size_t i;

    clear_screen();

    printf("==========================================\n");
    printf("        VÉRIFICATION ENVIRONNEMENT\n");
    printf("==========================================\n\n");

    for (i = 0; i < C_TOOLS_COUNT; i++)
    {
        Tool *tool = &c_tools[i];

        if (command_exists(tool->command))
        {
            printf("[✓] %-15s disponible\n",
                   tool->package);
        }
        else
        {
            printf("[!] %-15s absent\n",
                   tool->package);
        }
    }

    pause_screen();
}


/* =========================================================
 * MES OUTILS
 * ========================================================= */

void my_tools(void)
{
    clear_screen();

    printf("==========================================\n");
    printf("               MES OUTILS\n");
    printf("==========================================\n\n");

    printf("[INFO] Aucun outil personnel n'est encore\n");
    printf("       enregistré.\n\n");

    printf("Cette section sera développée plus tard.\n");

    pause_screen();
}


/* =========================================================
 * INFORMATIONS SYSTÈME
 * ========================================================= */

void system_information(void)
{
    clear_screen();

    printf("==========================================\n");
    printf("          INFORMATIONS SYSTÈME\n");
    printf("==========================================\n\n");

    printf("Version du manager : %s\n", VERSION);

    if (is_termux())
        printf("Plateforme         : Termux\n");
    else
        printf("Plateforme         : inconnue\n");

    printf("Architecture       : ");

    system("uname -m");

    printf("Kernel             : ");

    system("uname -r");

    printf("\nPREFIX             : ");

    const char *prefix = getenv("PREFIX");

    if (prefix != NULL)
        printf("%s\n", prefix);
    else
        printf("non disponible\n");

    pause_screen();
}


/* =========================================================
 * CONFIGURATION APPAREIL
 * ========================================================= */

void device_configuration(void)
{
    int choice;

    while (1)
    {
        clear_screen();
        system("../start/start.sh");

        printf("==========================================\n");
        printf("       CONFIGURATION DE L'APPAREIL\n");
        printf("==========================================\n\n");

        printf("1. Configuration C\n");
        printf("2. Configuration Python\n");
        printf("3. Configuration CTF\n");
        printf("4. Configuration complète\n");
        printf("0. Retour\n\n");

        printf("Votre choix : ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        switch (choice)
        {
            case 1:
                configure_c();
                break;

            case 2:
                printf("\n[INFO] Configuration Python prévue pour une prochaine version.\n");
                pause_screen();
                break;

            case 3:
                printf("\n[INFO] Configuration CTF prévue pour une prochaine version.\n");
                pause_screen();
                break;

            case 4:
                printf("\n[INFO] Configuration complète prévue pour une prochaine version.\n");
                pause_screen();
                break;

            case 0:
                return;

            default:
                printf("\n[!] Choix invalide.\n");
                pause_screen();
        }
    }
}


/* =========================================================
 * MENU PRINCIPAL
 * ========================================================= */

void main_menu(void)
{
    int choice;

    while (1)
    {
        clear_screen();

        printf("==========================================\n");
        printf("          CTF DEV MANAGER v%s\n", VERSION);
        printf("==========================================\n\n");

        printf("1. Configuration de l'appareil\n");
        printf("2. Mes outils\n");
        printf("3. Vérifier l'environnement\n");
        printf("4. Mise à jour\n");
        printf("5. Informations système\n");
        printf("0. Quitter\n\n");

        printf("Votre choix : ");

        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        switch (choice)
        {
            case 1:
                device_configuration();
                break;

            case 2:
                my_tools();
                break;

            case 3:
                check_environment();
                break;

            case 4:
                update_system();
                break;

            case 5:
                system_information();
                break;

            case 0:
                clear_screen();
                printf("Au revoir !\n");
                return;

            default:
                printf("\n[!] Choix invalide.\n");
                pause_screen();
        }
    }
}


/* =========================================================
 * MAIN
 * ========================================================= */

int main(void)
{
    clear_screen();

    printf("==========================================\n");
    printf("          CTF DEV MANAGER v%s\n", VERSION);
    printf("==========================================\n\n");

    if (!is_termux())
    {
        printf("[!] Attention : ce programme est actuellement\n");
        printf("    conçu pour Termux.\n\n");

        if (!ask_confirmation("Continuer malgré tout ?"))
            return 0;
    }

    main_menu();

    return 0;
}