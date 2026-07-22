#include <stdio.h>
#include "fonction.h"
int main ()
{

        int e;
        printf("Ce programme est utilisé pour calculer l'écart-type selon la physique.");
        printf("Le calcul de l'écart-type ne concerne que les tableaux contenant au moins deux valeurs.");

        puts ("Combien de nombres voulez-vous calculer leur écart-type ?");
        scanf ("%d",&e);
        if (e >= 2)
        {

                printf("Entrez à tour de rôle les nombres de votre tableau :");
                printf("NB : pour les nombres à virgule, utilisez le point (.) comme séparateur.");
                double tab[e];
                for (int i = 0; i < e; i++)
                {
                        scanf("%lf", &tab[i]);
                }
                ecart_type(e, tab);
                return 0;
        }
        else
        {
                printf("Il faut au minimum deux valeurs pour executer ce programme");
                return 1;
        }
}
