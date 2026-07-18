from fonction import *
import math

def somme_exp(x, tab):
    b = []
    for i in range(len(tab)):
        a = tab[i] - x
        a = a * a
        b.append(a)
    return sum_tableau(b)

def ecart_type(tab):
    x = moyenne(tab)
    n = somme_exp(x, tab)
    c = math.sqrt((1 / (e - 1)) * n)
    print (f"{c}")
    return c

tab = []

print("Ce programme est utilisé pour calculer l'écart-type selon la physique.\n")
print("Le calcul de l'écart-type ne concerne que les tableaux contenant au moins deux valeurs.\n")

e = int(input("Combien de nombres voulez-vous calculer leur écart-type ? "))

if e >= 2:
	print("Entrez à tour de rôle les nombres de votre tableau.")
	print("NB : pour les nombres à virgule, utilisez le point (ex : 12.5).")

	for i in range(e):
    		a = float(input(f"N°{i+1} = "))
    		tab.append(a)
	ecart_type(tab)
else:
	print ("Il faut au minimum deux valeurs pour executer ce programme")
