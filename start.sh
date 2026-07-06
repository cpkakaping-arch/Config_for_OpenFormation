#!/data/data/com.termux/files/usr/bin/bash

# ----------------------------------
#  Script : Bannière Open Formation
#  Pour Termux (Android)
# ----------------------------------

# 1. Vérifier et installer figlet si absent
if ! command -v figlet &>/dev/null; then
    echo "Installation de figlet..."
    pkg update -y && pkg install figlet -y
fi

# 2. Détecter la largeur du terminal
cols=$(tput cols)

# 3. Choisir une police adaptée à la largeur pour les titres
if [ "$cols" -lt 60 ]; then
    font="small"      # compact, lisible sur téléphone
else
    font="standard"   # plus grand si tablette / mode paysage
fi

# 4. Couleurs et affichage
echo ""  # saut de ligne
echo -e "\e[1;36m"   # cyan gras
figlet -w "$cols" -f "$font" "OPEN"
echo -e "\e[1;34m"   # bleu gras
figlet -w "$cols" -f "$font" "FORMATION"
echo -e "\e[1;33m"   # jaune pour la signature
# Signature discrète alignée à droite
echo  "" $cols "by Dieson Parfait"
echo -e "\e[0m"      # réinitialise les couleurs
echo ""
