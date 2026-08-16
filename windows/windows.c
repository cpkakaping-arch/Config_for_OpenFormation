#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define VERSION "0.1.0"
#define TOOLS_DIR ".\\tools"
#define MAX_TOOLS 256


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
    {"Git", "git"},
    {"7-Zip", "7z"},
    {"curl", "curl"},
    {"wget", "wget"},
    {"jq", "jq"},
    {"tree", "tree"},
    {"grep", "grep"},
    {"sed", "sed"},
    {"awk", "awk"},

    /* Développement C/C++ */
    {"LLVM", "clang"},
    {"CMake", "cmake"},
    {"Ninja", "ninja"},
    {"Make", "make"},

    /* Debug */
    {"GDB", "gdb"},

    /* Python */
    {"Python", "python"},

    /* Node.js */
    {"Node.js", "node"}
};

#define C_TOOLS_COUNT \
    (sizeof(c_tools) / sizeof(c_tools[0]))


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
 * Vérifie si une commande existe dans le PATH Windows.
 */
int command_exists(const char *command)
{
    char test[512];

    snprintf(
        test,
        sizeof(test),
        "where %s >nul 2>&1",
        command
    );

    return system(test) == 0;
}


/*
 * Vérifie si nous sommes sous Windows.
 */
int is_windows(void)
{
#ifdef _WIN32
    return 1;
#else
    return 0;
#endif
}


/* =========================================================
 * INSTALLATION
 * ========================================================= */

int install_package(const Tool *tool)
{
    char command[512];

    printf("\n------------------------------------------\n");

    printf(
        "[!] %s n'est pas installé.\n",
        tool->package
    );

    if (!ask_confirmation(
            "Voulez-vous l'installer ?"))
    {
        printf(
            "[SKIP] %s ignoré.\n",
            tool->package
        );

        return 0;
    }

    printf(
        "[...] Installation de %s...\n",
        tool->package
    );


    /*
     * winget installe les applications Windows.
     *
     * --accept-source-agreements
     * --accept-package-agreements
     *
     * permettent d'éviter les questions
     * liées aux conditions de winget.
     *
     * La confirmation principale reste celle
     * demandée par notre programme.
     */

    snprintf(
        command,
        sizeof(command),
        "winget install --id \"%s\" "
        "--accept-source-agreements "
        "--accept-package-agreements",
        tool->package
    );


    int result = system(command);


    if (result != 0)
    {
        printf(
            "[ERREUR] Impossible d'installer %s.\n",
            tool->package
        );

        return 0;
    }


    /*
     * Vérification après installation.
     */

    if (command_exists(tool->command))
    {
        printf(
            "[OK] %s installé.\n",
            tool->package
        );

        return 1;
    }


    printf(
        "[!] Installation terminée mais commande "
        "non trouvée : %s\n",
        tool->command
    );

    printf(
        "[INFO] Il peut être nécessaire de "
        "redémarrer le programme.\n"
    );

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


    if (!ask_confirmation(
            "Commencer la configuration ?"))
    {
        return;
    }


    for (i = 0; i < C_TOOLS_COUNT; i++)
    {
        Tool *tool = &c_tools[i];


        if (command_exists(tool->command))
        {
            printf(
                "[OK] %-15s déjà installé\n",
                tool->package
            );
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

    printf(
        "Windows va rechercher les mises à jour\n"
        "des applications gérées par winget.\n\n"
    );


    if (!ask_confirmation(
            "Voulez-vous continuer ?"))
    {
        return;
    }


    printf(
        "\n[...] Recherche des mises à jour...\n"
    );

    system("winget upgrade");


    printf(
        "\n[OK] Vérification terminée.\n"
    );

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
            printf(
                "[OK] %-15s disponible\n",
                tool->package
            );
        }
        else
        {
            printf(
                "[!] %-15s absent\n",
                tool->package
            );
        }
    }


    pause_screen();
}


/* =========================================================
 * LANCEMENT D'UN OUTIL
 * ========================================================= */

void launch_tool(const char *filename)
{
    char path[512];
    char command[2048];

    const char *extension;


    snprintf(
        path,
        sizeof(path),
        "%s\\%s",
        TOOLS_DIR,
        filename
    );


    extension = strrchr(filename, '.');


    /* -----------------------------------------------------
     * BASH / SH
     * ----------------------------------------------------- */

    if (
        extension != NULL &&
        (
            _stricmp(extension, ".sh") == 0
        )
    )
    {
        snprintf(
            command,
            sizeof(command),
            "bash \"%s\"",
            path
        );
    }


    /* -----------------------------------------------------
     * BATCH
     * ----------------------------------------------------- */

    else if (
        extension != NULL &&
        (
            _stricmp(extension, ".bat") == 0 ||
            _stricmp(extension, ".cmd") == 0
        )
    )
    {
        snprintf(
            command,
            sizeof(command),
            "cmd /c \"\"%s\"\"",
            path
        );
    }


    /* -----------------------------------------------------
     * POWERSHELL
     * ----------------------------------------------------- */

    else if (
        extension != NULL &&
        _stricmp(extension, ".ps1") == 0
    )
    {
        snprintf(
            command,
            sizeof(command),
            "powershell -ExecutionPolicy Bypass "
            "-File \"%s\"",
            path
        );
    }


    /* -----------------------------------------------------
     * JAVASCRIPT
     * ----------------------------------------------------- */

    else if (
        extension != NULL &&
        _stricmp(extension, ".js") == 0
    )
    {
        snprintf(
            command,
            sizeof(command),
            "node \"%s\"",
            path
        );
    }


    /* -----------------------------------------------------
     * PYTHON
     * ----------------------------------------------------- */

    else if (
        extension != NULL &&
        _stricmp(extension, ".py") == 0
    )
    {
        snprintf(
            command,
            sizeof(command),
            "python \"%s\"",
            path
        );
    }


    /* -----------------------------------------------------
     * C
     * ----------------------------------------------------- */

    else if (
        extension != NULL &&
        _stricmp(extension, ".c") == 0
    )
    {
        snprintf(
            command,
            sizeof(command),
            "clang \"%s\" "
            "-o \"%s\\.tool_temp.exe\" "
            "&& \"%s\\.tool_temp.exe\"",
            path,
            TOOLS_DIR,
            TOOLS_DIR
        );
    }


    /* -----------------------------------------------------
     * C++
     * ----------------------------------------------------- */

    else if (
        extension != NULL &&
        (
            _stricmp(extension, ".cpp") == 0 ||
            _stricmp(extension, ".cc") == 0 ||
            _stricmp(extension, ".cxx") == 0
        )
    )
    {
        snprintf(
            command,
            sizeof(command),
            "clang++ \"%s\" "
            "-o \"%s\\.tool_temp.exe\" "
            "&& \"%s\\.tool_temp.exe\"",
            path,
            TOOLS_DIR,
            TOOLS_DIR
        );
    }


    /* -----------------------------------------------------
     * EXECUTABLE WINDOWS
     * ----------------------------------------------------- */

    else if (
        extension != NULL &&
        _stricmp(extension, ".exe") == 0
    )
    {
        snprintf(
            command,
            sizeof(command),
            "\"%s\"",
            path
        );
    }


    /* -----------------------------------------------------
     * TYPE INCONNU
     * ----------------------------------------------------- */

    else
    {
        printf(
            "\n[ERREUR] Type de fichier non reconnu.\n"
        );

        pause_screen();

        return;
    }


    /* -----------------------------------------------------
     * EXECUTION
     * ----------------------------------------------------- */

    printf(
        "\n[...] Lancement de %s...\n\n",
        filename
    );


    system(command);


    /* -----------------------------------------------------
     * NETTOYAGE C / C++
     * ----------------------------------------------------- */

    if (
        extension != NULL &&
        (
            _stricmp(extension, ".c") == 0 ||
            _stricmp(extension, ".cpp") == 0 ||
            _stricmp(extension, ".cc") == 0 ||
            _stricmp(extension, ".cxx") == 0
        )
    )
    {
        char temporary_file[512];

        snprintf(
            temporary_file,
            sizeof(temporary_file),
            "%s\\.tool_temp.exe",
            TOOLS_DIR
        );

        DeleteFileA(temporary_file);
    }


    printf(
        "\n[OK] Fin de l'outil.\n"
    );

    pause_screen();
}


/* =========================================================
 * MES OUTILS
 * ========================================================= */

void my_tools(void)
{
    WIN32_FIND_DATAA find_data;

    HANDLE handle;

    char *tools[MAX_TOOLS];

    int count = 0;
    int choice;
    int i;


    /* -----------------------------------------------------
     * OUVERTURE DU DOSSIER
     * ----------------------------------------------------- */

    handle = FindFirstFileA(
        TOOLS_DIR "\\*",
        &find_data
    );


    if (handle == INVALID_HANDLE_VALUE)
    {
        clear_screen();

        printf("==========================================\n");
        printf("               MES OUTILS\n");
        printf("==========================================\n\n");

        printf(
            "[INFO] Le dossier %s n'existe pas.\n",
            TOOLS_DIR
        );

        printf(
            "[INFO] Aucun outil personnel détecté.\n\n"
        );

        pause_screen();

        return;
    }


    /* -----------------------------------------------------
     * LECTURE DU DOSSIER
     * ----------------------------------------------------- */

    do
    {
        if (
            strcmp(find_data.cFileName, ".") == 0 ||
            strcmp(find_data.cFileName, "..") == 0
        )
        {
            continue;
        }


        /*
         * Ne pas afficher le fichier temporaire.
         */

        if (
            _stricmp(
                find_data.cFileName,
                ".tool_temp.exe"
            ) == 0
        )
        {
            continue;
        }


        /*
         * Ignorer les dossiers.
         */

        if (
            find_data.dwFileAttributes &
            FILE_ATTRIBUTE_DIRECTORY
        )
        {
            continue;
        }


        if (count >= MAX_TOOLS)
            break;


        tools[count] = malloc(
            strlen(find_data.cFileName) + 1
        );


        if (tools[count] == NULL)
            continue;


        strcpy(
            tools[count],
            find_data.cFileName
        );

        count++;

    }
    while (FindNextFileA(handle, &find_data));


    FindClose(handle);


    /* -----------------------------------------------------
     * MENU DES OUTILS
     * ----------------------------------------------------- */

    while (1)
    {
        clear_screen();

        printf("==========================================\n");
        printf("               MES OUTILS\n");
        printf("==========================================\n\n");


        if (count == 0)
        {
            printf(
                "[INFO] Aucun outil personnel détecté.\n\n"
            );


            for (i = 0; i < count; i++)
                free(tools[i]);


            pause_screen();

            return;
        }


        for (i = 0; i < count; i++)
        {
            printf(
                "%d. %s\n",
                i + 1,
                tools[i]
            );
        }


        printf("\n0. Retour\n\n");

        printf("Votre choix : ");


        if (scanf("%d", &choice) != 1)
        {
            while (getchar() != '\n');

            printf(
                "\n[!] Choix invalide.\n"
            );

            pause_screen();

            continue;
        }


        while (getchar() != '\n');


        /* -------------------------------------------------
         * RETOUR
         * ------------------------------------------------- */

        if (choice == 0)
        {
            for (i = 0; i < count; i++)
                free(tools[i]);

            return;
        }


        /* -------------------------------------------------
         * CHOIX INVALIDE
         * ------------------------------------------------- */

        if (
            choice < 1 ||
            choice > count
        )
        {
            printf(
                "\n[!] Choix invalide.\n"
            );

            pause_screen();

            continue;
        }


        /* -------------------------------------------------
         * LANCER L'OUTIL
         * ------------------------------------------------- */

        launch_tool(
            tools[choice - 1]
        );
    }
}


/* =========================================================
 * INFORMATIONS SYSTÈME
 * ========================================================= */

void system_information(void)
{
    SYSTEM_INFO system_info;

    char windows_version[256];


    clear_screen();

    printf("==========================================\n");
    printf("          INFORMATIONS SYSTÈME\n");
    printf("==========================================\n\n");


    printf(
        "Version du manager : %s\n",
        VERSION
    );


    printf(
        "Plateforme         : Windows\n"
    );


    GetSystemInfo(&system_info);


    printf(
        "Architecture       : "
    );


    switch (system_info.wProcessorArchitecture)
    {
        case PROCESSOR_ARCHITECTURE_AMD64:

            printf("x64\n");

            break;


        case PROCESSOR_ARCHITECTURE_ARM64:

            printf("ARM64\n");

            break;


        case PROCESSOR_ARCHITECTURE_INTEL:

            printf("x86\n");

            break;


        case PROCESSOR_ARCHITECTURE_ARM:

            printf("ARM\n");

            break;


        default:

            printf("inconnue\n");

            break;
    }


    printf(
        "Processeurs        : %lu\n",
        system_info.dwNumberOfProcessors
    );


    printf(
        "\nVersion Windows    : "
    );


    snprintf(
        windows_version,
        sizeof(windows_version),
        "ver"
    );


    system(windows_version);


    printf("\n");


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


        /*
         * Bannière Windows.
         */

        system(
            "call ..\\start\\start.bat"
        );


        printf(
            "==========================================\n"
        );

        printf(
            "       CONFIGURATION DE L'APPAREIL\n"
        );

        printf(
            "==========================================\n\n"
        );


        printf(
            "1. Configuration C\n"
        );

        printf(
            "2. Configuration Python\n"
        );

        printf(
            "3. Configuration CTF\n"
        );

        printf(
            "4. Configuration complète\n"
        );

        printf(
            "0. Retour\n\n"
        );


        printf(
            "Votre choix : "
        );


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

                printf(
                    "\n[INFO] Configuration Python "
                    "prévue pour une prochaine version.\n"
                );

                pause_screen();

                break;


            case 3:

                printf(
                    "\n[INFO] Configuration CTF "
                    "prévue pour une prochaine version.\n"
                );

                pause_screen();

                break;


            case 4:

                printf(
                    "\n[INFO] Configuration complète "
                    "prévue pour une prochaine version.\n"
                );

                pause_screen();

                break;


            case 0:

                return;


            default:

                printf(
                    "\n[!] Choix invalide.\n"
                );

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


        printf(
            "==========================================\n"
        );

        printf(
            "          CTF DEV MANAGER v%s\n",
            VERSION
        );

        printf(
            "==========================================\n\n"
        );


        puts(
            "By Dieson Parfait\n\n"
        );


        printf(
            "1. Configuration de l'appareil\n"
        );

        printf(
            "2. Mes outils\n"
        );

        printf(
            "3. Vérifier l'environnement\n"
        );

        printf(
            "4. Mise à jour\n"
        );

        printf(
            "5. Informations système\n"
        );

        printf(
            "0. Quitter\n\n"
        );


        printf(
            "Votre choix : "
        );


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

                printf(
                    "Au revoir !\n"
                );

                return;


            default:

                printf(
                    "\n[!] Choix invalide.\n"
                );

                pause_screen();
        }
    }
}


/* =========================================================
 * MAIN
 * ========================================================= */

int main(void)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    clear_screen();


    /*
     * Bannière Windows.
     */

    system(
        "call ..\\start\\start.bat"
    );


    (void)getchar();


    system("cls");


    printf(
        "==========================================\n"
    );

    printf(
        "          CTF DEV MANAGER v%s\n",
        VERSION
    );

    printf(
        "==========================================\n\n\n\n"
    );


    if (!is_windows())
    {
        printf(
            "[!] Attention : ce programme est "
            "actuellement conçu pour Windows.\n\n"
        );


        if (!ask_confirmation(
                "Continuer malgré tout ?"))
        {
            return 0;
        }
    }


    main_menu();


    return 0;
}
