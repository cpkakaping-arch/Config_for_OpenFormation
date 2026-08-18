/*
# La fonction moyenne() prend en paramètre une liste de notes.
# La fonction sum_tableau() prend en paramètre un tableau à une liste et renvoie leur somme
# La fonction moyenne_pondere() prend en paramètre un tableau à deux dimensions :
# - tabs[0] contient les coefficients ;
# - tabs[1] contient les notes. 
*/
#include "fonction.h"
#include <math.h>
#include <stdio.h>
double sum_tableau(int n, double tab[])
{
    double a = 0;
    for ( int i = 0; i < n; i++)
    {
        a += tab[i];
    }
    return a;

}

double moyenne(int n, double tab[] )
{

    double a = sum_tableau(n, tab);
    a = a / n;
    return a; 

}

double moyenne_pondere( int n,double tabs[2][n])
{
    double tab[n];
    double c = 0;

    for (int i = 0; i < n; i++)
    {
        tab[i] = tabs[0][i] * tabs[1][i];
    }

    c = sum_tableau(n, tab);

    c = c / sum_tableau(n, tabs[0]);

    return c;
}

double somme_carre(int n, double x, double tab[n])
{
    double b[n];
    for (int i = 0; i < n; i++)
    {
        double a = tab[i] - x;
        a = a * a;
        b[i] = a;
    }
    return sum_tableau(n, b);
}

double ecart_type(int n, double tab[n])
{

   double x = moyenne(n, tab);
    x = somme_carre(n, x, tab);
    double c = sqrt((1 / (n - 1)) * x);
    printf ("L'écart-type est : ");
    printf ("%lf\n\n",c);
    return c;

}