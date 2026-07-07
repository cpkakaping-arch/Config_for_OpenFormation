#!/usr/bin/env bash

cd ~/

bash ~/bash/start.sh

mkdir -p import

cd ~/storage/shared || exit 1

echo "Vous allez entrer à tour de rôle le nom et l'extension."

read -r -p "Le nom du fichier : " nom

read -r -p "Entrez l'extension du fichier (laisser vide si le fichier n'a pas d'extension) : " extension

# Supprime le point si l'utilisateur en a mis un
extension="${extension#.}"

if [ -z "$extension" ]; then
    echo "Recherche de ${nom}..."
    chemin=$(find . -type f -name "$nom" 2>/dev/null)
else
    echo "Recherche de ${nom}.${extension}..."
    chemin=$(find . -type f -name "${nom}.${extension}" 2>/dev/null)
fi

if [ -z "$chemin" ]; then
    echo "Aucun fichier trouvé avec ce nom."
    exit 1
fi

cp "$chemin" ~/import/
