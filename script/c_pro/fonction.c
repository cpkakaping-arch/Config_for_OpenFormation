/*
# La fonction moyenne() prend en paramètre une liste de notes.
# La fonction sum_tableau() prend en paramètre un tableau à une liste et renvoie leur somme
# La fonction moyenne_pondere() prend en paramètre un tableau à deux dimensions :
# - tabs[0] contient les coefficients ;
# - tabs[1] contient les notes. 
*/

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

    double a = sum_tableau(tab, n);
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

    c = sum_tableau(tab, n);

    c = c / sum_tableau(tabs[0], n);

    return c;
}