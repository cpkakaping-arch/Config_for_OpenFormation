#include <stdio.h>
#include "fonction.h"
#include <stdlib.h>
int main ()
{
        char *ps = getenv("PSModulePath");

    if (ps != NULL)
    {
        printf("PowerShell détecté\n");
        system("powershell -ExecutionPolicy Bypass -File ./start.ps1");
    }
    else
    {
        printf("CMD détecté\n");
        system("start.bat");
    }
        int e;
        puts("Ce programme est utilisé pour calculer l'écart-type selon la physique.\nL'écart-type est une mesure de la dispersion des valeurs d'un échantillon par rapport à la moyenne de cet échantillon.\nIl est calculé en prenant la racine carrée de la variance, qui est la moyenne des carrés des écarts entre chaque valeur et la moyenne de l'échantillon.\n");
        puts("Le calcul de l'écart-type ne concerne que les tableaux contenant au moins deux valeurs.\n");

        printf("Combien de nombres voulez-vous calculer leur écart-type ? : ");
        scanf ("%d",&e);
        if (e >= 2)
        {

                puts("Entrez à tour de rôle les nombres de votre tableau :");
                puts("NB : pour les nombres à virgule, utilisez le point (.) comme séparateur.");
                double tab[e];
                for (int i = 0; i < e; i++)
                {
                        printf("Nombre %d : ", i + 1);
                        scanf("%lf", &tab[i]);
                }
                ecart_type(e, tab);
                return 0;
        }
        else
        {
                puts("Il faut au minimum deux valeurs pour executer ce programme");
                return 1;
        }
}
