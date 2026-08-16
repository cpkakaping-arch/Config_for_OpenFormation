#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define VERSION "0.1.0"


/* =========================================================
 * UTILITAIRES
 * ========================================================= */

void clear_screen(void)
{
    system("cls");
}


void pause_screen(void)
{
    printf("\nAppuyez sur Entrée pour continuer...");
    (void)getchar();
}


/* =========================================================
 * NOUVEAU TERMINAL
 * ========================================================= */

int open_new_terminal(void)
{
    char command[1024];

    /*
     * Le nouveau terminal exécute ce programme
     * avec l'option --terminal.
     */

    snprintf(
        command,
        sizeof(command),
        "start \"IRM\" cmd /k \"%s\" --terminal",
        __argv[0]
    );

    return system(command);
}


/* =========================================================
 * AVERTISSEMENT 1
 * ========================================================= */

int warning_internet(void)
{
    int choice;

    clear_screen();

    printf("==========================================\n");
    printf("              AVERTISSEMENT\n");
    printf("==========================================\n\n");

    printf(
        "Cette application ou cet outil peut avoir\n"
        "besoin d'une connexion Internet pour fonctionner.\n\n"
    );

    printf(
        "Si vous disposez d'un forfait / d'une connexion\n"
        "Internet, vous pouvez continuer.\n\n"
    );

    printf("1. Continuer\n");
    printf("2. Retour\n\n");

    printf("Votre choix : ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n');
        return 0;
    }

    while (getchar() != '\n');

    if (choice == 1)
        return 1;

    return 0;
}


/* =========================================================
 * AVERTISSEMENT 2
 * ========================================================= */

int warning_files(void)
{
    int choice;

    clear_screen();

    printf("==========================================\n");
    printf("              AVERTISSEMENT\n");
    printf("==========================================\n\n");

    printf(
        "Les logiciels utilisés par cet outil ne sont\n"
        "pas nécessairement interdépendants.\n\n"
    );

    printf(
        "Déplacer, renommer ou modifier certains fichiers\n"
        "ou dossiers peut provoquer des erreurs ou un\n"
        "dysfonctionnement.\n\n"
    );

    printf(
        "Le fonctionnement peut également varier selon\n"
        "votre ordinateur et sa configuration.\n\n"
    );

    printf("1. J'ai compris, continuer\n");
    printf("2. Retour\n\n");

    printf("Votre choix : ");

    if (scanf("%d", &choice) != 1)
    {
        while (getchar() != '\n');
        return 0;
    }

    while (getchar() != '\n');

    if (choice == 1)
        return 1;

    return 0;
}


/* =========================================================
 * START.BAT
 * ========================================================= */

int launch_start_bat(void)
{
    printf("\n[...] Lancement de start.bat...\n\n");

    return system(
        "call ..\\..\\start\\start.bat"
    );
}


/* =========================================================
 * TEST PRINCIPAL
 * ========================================================= */

int run_main_command(void)
{
    int result;

    printf("\n==========================================\n");
    printf("             ACTIVATION WIN\n");
    printf("==========================================\n\n");

    printf("[...] Exécution de la commande principale...\n\n");

    /*
     * Commande principale
     */

    result = system(
        "irm https://get.activated.win | iex"
    );

    if (result == 0)
    {
        printf("\n[OK] Commande exécutée avec succès.\n");
        return 1;
    }

    /*
     * Solution de secours
     */

    printf(
        "\n[!] La commande principale n'a pas fonctionné.\n"
    );

    printf(
        "[...] Tentative avec la commande de secours...\n\n"
    );

    result = system(
        "iex (curl.exe -s --doh-url https://1.1.1.1/dns-query https://get.activated.win | Out-String)"
    );

    if (result == 0)
    {
        printf("\n[OK] Commande de secours exécutée.\n");
        return 1;
    }

    return 0;
}


/* =========================================================
 * MODE TERMINAL
 * ========================================================= */

int terminal_mode(void)
{
    clear_screen();

    printf("==========================================\n");
    printf("              IRM v%s\n", VERSION);
    printf("==========================================\n\n");

    /*
     * Première information
     */

    if (!warning_internet())
    {
        printf("\nRetour...\n");
        return 0;
    }


    /*
     * Deuxième information
     */

    if (!warning_files())
    {
        printf("\nRetour...\n");
        return 0;
    }


    /*
     * Lancement de start.bat
     */

    if (launch_start_bat() != 0)
    {
        printf(
            "\n[!] start.bat a rencontré une erreur.\n"
        );

        pause_screen();

        return 0;
    }


    /*
     * Commande principale
     */

    if (!run_main_command())
    {
        clear_screen();

        printf("==========================================\n");
        printf("                 DÉSOLÉ\n");
        printf("==========================================\n\n");

        printf(
            "L'opération n'a pas pu être exécutée.\n\n"
        );

        printf(
            "Vous n'êtes probablement pas éligible\n"
            "à cette opération sur cette configuration.\n"
        );

        pause_screen();

        return 0;
    }


    /*
     * Attendre avant fermeture
     */

    printf("\n==========================================\n");
    printf("              OPÉRATION TERMINÉE\n");
    printf("==========================================\n\n");

    printf(
        "Appuyez sur Entrée pour fermer ce terminal..."
    );

    (void)getchar();

    printf("\nAu revoir !\n");

    Sleep(1500);

    return 0;
}


/* =========================================================
 * MAIN
 * ========================================================= */

int main(int argc, char *argv[])
{
    /*
     * UTF-8 Windows
     */

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    /*
     * Si le programme est lancé avec --terminal,
     * nous sommes dans le nouveau terminal.
     */

    if (
        argc > 1 &&
        strcmp(argv[1], "--terminal") == 0
    )
    {
        return terminal_mode();
    }


    /*
     * Programme principal
     */

    clear_screen();

    printf("==========================================\n");
    printf("              IRM v%s\n", VERSION);
    printf("==========================================\n\n");

    printf(
        "Lancement d'un nouveau terminal...\n"
    );

    Sleep(1000);


    /*
     * Ouvrir le nouveau terminal
     */

    if (open_new_terminal() != 0)
    {
        clear_screen();

        printf(
            "[ERREUR] Impossible d'ouvrir le nouveau terminal.\n\n"
        );

        pause_screen();

        return 1;
    }


    /*
     * Le programme principal reste ouvert.
     */

    printf(
        "\nLe terminal IRM a été lancé.\n"
    );

    printf(
        "Vous pouvez revenir à cette fenêtre après son exécution.\n"
    );

    return 0;
}