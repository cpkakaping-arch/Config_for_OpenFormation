#!/usr/bin/env bash

# Mémorise le dossier depuis lequel le script est lancé
DOSSIER_ACTUEL="$(pwd)"

bash ./start.sh

cd ~/

mkdir -p import

cd ~/storage/shared || exit 1

echo "Vous allez entrer à tour de rôle le nom et l'extension."

read -r -p "Le nom du fichier : " nom

read -r -p "Entrez l'extension du fichier (laisser vide si le fichier n'a pas d'extension) : " extension

# Supprime le point si l'utilisateur en a mis un
extension="${extension#.}"

if [ -z "$extension" ]; then
    echo "Recherche de ${nom}..."
    chemin=$(find . -type f -name "$nom" 2>/dev/null | head -n 1)
else
    echo "Recherche de ${nom}.${extension}..."
    chemin=$(find . -type f -name "${nom}.${extension}" 2>/dev/null | head -n 1)
fi

if [ -z "$chemin" ]; then
    echo "Aucun fichier trouvé avec ce nom."
    exit 1
fi

echo
echo "Nous avons trouvé le fichier :"
echo "$chemin"
echo
echo "Quelle option choisissez-vous ?"
echo "1) Copier dans ~/import (par défaut)"
echo "2) Choisir un autre dossier"

read -r -p "Votre choix [1/2] : " choix

case "$choix" in
    ""|1)
        cp "$chemin" ~/import/
        echo "Le fichier a été copié dans ~/import."
        ;;
    2)
        read -r -p "Entrez le chemin du dossier de destination : " destination

        # Développe ~ si l'utilisateur l'utilise
        destination="${destination/#\~/$HOME}"

        # Gère les chemins relatifs commençant par ./
        if [[ "$destination" == ./* ]]; then
            destination="$DOSSIER_ACTUEL/${destination#./}"
        elif [[ "$destination" == "." || "$destination" == "./" ]]; then
            destination="$DOSSIER_ACTUEL"
        fi

        if [ ! -d "$destination" ]; then
            echo "Le dossier n'existe pas : $destination"
            exit 1
        fi

        cp "$chemin" "$destination/"
        echo "Le fichier a été copié dans : $destination"
        ;;
    *)
        echo "Choix invalide."
        exit 1
        ;;
esac
