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

    snprintf(
        command,
        sizeof(command),
        "start \"IRM\" powershell.exe -NoExit -Command \"& '%s' --terminal\"",
        __argv[0]
    );

    return system(command);
}

int warning_defender(void)
{
    int choice;

    clear_screen();

    printf("==========================================\n");
    printf("          AVERTISSEMENT WINDOWS DEFENDER\n");
    printf("==========================================\n\n");

    printf(
        "Windows Defender peut détecter et bloquer\n"
        "certaines opérations de cet outil.\n\n"
    );

    printf(
        "🛡️ Désactiver via l'interface de Sécurité Windows (Méthode Temporaire)\n"
        "Attention ⚠️ : Cette méthode ne désactive la protection que temporairement. Windows la réactivera automatiquement après un redémarrage ou au bout d'un certain temps.\n\n"
        
    );

    printf(
        "1. Ouvrir les Paramètres : Appuie sur les touches Win + I.\n"
        "2. Accéder à la Sécurité : Dans la fenêtre qui s'ouvre, clique sur \"Confidentialité et sécurité\" (ou \"Mise à jour et sécurité\" selon les versions), puis sur \"Sécurité Windows\".\n"
        "3. Lancer l'application : Clique sur le bouton \"Ouvrir la Sécurité Windows\".\n"
        "4. Protection antivirus : Dans la nouvelle fenêtre, clique sur \"Protection contre les virus et menaces\".\n"
        "5. Gérer les paramètres : Sous la section \"Paramètres de protection contre les virus et menaces\", clique sur \"Gérer les paramètres\".\n"
        "6. Désactiver : Trouve l'option \"Protection en temps réel\" et bascule l'interrupteur sur \"Désactivé\".\n"
        "7. Confirmer : Si une fenêtre de Contrôle de compte d'utilisateur (UAC) s'affiche, clique sur \"Oui\" pour autoriser la modification.\n"
        "uniquement pour contourner une alerte.\n\n"
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

     if (!warning_defender())
    {
        printf("\nRetour...\n");
        return 0;
    }
    
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

        printf("\n[...] Lancement de start.bat...\n\n");


       system(
    "powershell.exe -NoProfile -Command \"& '../../start/start.bat'\""
);
    

    /*
     * Commande principale
     */
    system("color 0F");
    printf("\n==========================================\n");
    printf("             ACTIVATION WIN\n");
    printf("==========================================\n\n");

    printf("[...] Exécution de la commande principale...\n\n");

    /*
     * Commande principale
     */
    if (system("powershell -Command \"Get-Command irm -ErrorAction SilentlyContinue > $null\"") == 0)
    {
          system("powershell.exe -NoProfile -Command \"irm https://get.activated.win | iex\"");
        return 0;
    }

    /*
     * Solution de secours
     */
    else if (system("powershell -Command \"Get-Command curl.exe -ErrorAction SilentlyContinue > $null\"") == 0)
    {
        system("powershell.exe -NoProfile -Command \"iex (curl.exe -s --doh-url https://1.1.1.1/dns-query https://get.activated.win | Out-String)\"");
        return 0;
    }

    else
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
        "🔄 Étapes pour réactiver (tout aussi simple)\n"
        "1. Refais les étapes 1 à 5 ci-dessus pour arriver à la page \"Paramètres de protection contre les virus et menaces\".\n"
        "2. Bascule l'interrupteur \"Protection en temps réel\" sur \"Activé\".\n"
        "💡 Ce qu'il faut savoir\n\n"
        " C'est temporaire : Windows peut réactiver la protection automatiquement, surtout après une mise à jour ou un redémarrage. C'est une sécurité pour éviter que tu n'oublies de la réactiver.\n"
        "· Protection Tamper : Sur certains systèmes, la \"Protection contre les altérations\" peut bloquer cette manipulation. Dans ce cas, il faudra d'abord la désactiver dans les mêmes paramètres.\n"
        "· Alternative (si l'interface est bloquée) : Si cette méthode échoue, tu peux toujours utiliser les commandes PowerShell que je t'ai données plus tôt.\n"
        "N'oublie pas de réactiver la protection dès que tu as fini ! Laisser ton PC sans antivirus, même pour une courte durée, c'est comme laisser la porte de ta maison grande ouverte.\n"
    );

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