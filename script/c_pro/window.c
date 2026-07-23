#include <stdio.h>
#include "fonction.h"
#include <stdlib.h>
#include <windows.h>
int main ()
{
        
        char *ps = getenv("PSModulePath");

    if (ps != NULL)
    {
        printf("PowerShell detecte\n");
        //system("powershell -ExecutionPolicy Bypass -File ./start.ps1");
        system("start.bat");
    }
    else
    {
        printf("CMD detecte\n");
        system("start.bat");
    }
        int e;
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
        system("color 0F");
        system("cls");
        puts("Ce programme est utilise pour calculer l'ecart-type selon la physique.\nL'ecart-type est une mesure de la dispersion des valeurs d'un echantillon par rapport a la moyenne de cet echantillon.\nIl est calcule en prenant la racine carree de la variance, qui est la moyenne des carres des ecarts entre chaque valeur et la moyenne de l'echantillon.\n");
        puts("Le calcul de l'ecart-type ne concerne que les tableaux contenant au moins deux valeurs.\n");

        printf("Combien de nombres voulez-vous calculer leur ecart-type ? : ");
        scanf ("%d",&e);
        if (e >= 2)
        {

                puts("Entrez a tour de role les nombres de votre tableau :");
                puts("NB : pour les nombres a virgule, utilisez le point (.) comme separateur.");
                double tab[e];
                for (int i = 0; i < e; i++)
                {
                        printf("Nombre %d : ", i + 1);
                        scanf("%lf", &tab[i]);
                }
                ecart_type(e, tab);
                puts("Appuyer sur une touhe pour sortir\n\t\t\t By Dieson Parfait");
                getchar();
                system("pause");
                return 0;
        }
        else
        {
                puts("Il faut au minimum deux valeurs pour executer ce programme");
                return 1;
        }
}
