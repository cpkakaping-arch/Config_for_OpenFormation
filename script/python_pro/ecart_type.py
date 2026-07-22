from fonction import *
import math


tab = []

print("Ce programme calcule l'écart-type expérimental.\n")
print("Le calcul de l'écart-type ne concerne que les tableaux contenant au moins deux valeurs.\n")

e = int(input("Combien de nombres voulez-vous calculer leur écart-type ? "))
	
	
if e >= 2:
    print("Entrez à tour de rôle les nombres de votre tableau.\n")
    print("NB : pour les nombres à virgule, utilisez le point (ex : 12.5).")
    for i in range(e):
        a = float(input(f"N°{i+1} = "))
        tab.append(a)

    ecart_type(e, tab)

else:
    print ("Il faut au minimum deux valeurs pour executer ce programme")
