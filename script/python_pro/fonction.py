# La fonction moyenne() prend en paramètre une liste de notes.
# La fonction sum_tableau() prend en paramètre un tableau à une liste et renvoie leur somme
# La fonction moyenne_pondere() prend en paramètre un tableau à deux dimensions :
# - tabs[0] contient les coefficients ;
# - tabs[1] contient les notes.

def sum_tableau(tab):
    a = 0
    for i in range(len(tab)):
        a += tab[i]
    return a

def moyenne(tab):
    a = sum_tableau(tab)
    a /= len(tab)
    return a
    
def moyenne_pondere(tabs):
    tab = []
    for i in range(len(tabs[0])):
        tab.append(tabs[0][i] * tabs[1][i])

    return (sum_tableau(tab) / sum_tableau(tabs[0]))
    