```bash
#!/usr/bin/env bash

# ============================================================
# CTF DEV MANAGER
# Version Bash
# ============================================================

VERSION="0.1.0"

# ------------------------------------------------------------
# RÉPERTOIRES
# ------------------------------------------------------------

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TOOLS_DIR="$SCRIPT_DIR/tools"
START_SCRIPT="$SCRIPT_DIR/../start/start.sh"
TEMP_BINARY="$TOOLS_DIR/.tool_temp"

# ------------------------------------------------------------
# COULEURS
# ------------------------------------------------------------

RESET='\033[0m'
BOLD='\033[1m'

# ============================================================
# OUTILS DE CONFIGURATION C
# ============================================================

C_PACKAGES=(
    "coreutils:ls"
    "util-linux:lsblk"
    "findutils:find"
    "diffutils:diff"
    "grep:grep"
    "gawk:awk"
    "sed:sed"
    "tar:tar"
    "gzip:gzip"
    "bzip2:bzip2"
    "xz-utils:xz"
    "zip:zip"
    "unzip:unzip"
    "p7zip:7z"
    "which:which"
    "file:file"
    "tree:tree"
    "less:less"
    "man:man"
    "procps:ps"
    "termux-tools:termux-info"
    "ncurses-utils:tput"

    # Développement C/C++
    "clang:clang"
    "make:make"
    "cmake:cmake"
    "ninja:ninja"
    "binutils:objdump"
    "lld:ld.lld"

    # LLVM
    "llvm:llvm-ar"

    # Debug
    "gdb:gdb"
    "lldb:lldb"
)

# ============================================================
# UTILITAIRES
# ============================================================

clear_screen() {
    clear 2>/dev/null || printf '\033c'
}


pause_screen() {
    printf "\nAppuyez sur Entrée pour continuer..."
    read -r
}


ask_confirmation() {
    local question="$1"
    local answer

    printf "\n%s [o/N] : " "$question"

    read -r answer

    case "$answer" in
        o|O|y|Y)
            return 0
            ;;
        *)
            return 1
            ;;
    esac
}


command_exists() {
    command -v "$1" >/dev/null 2>&1
}


# ============================================================
# VÉRIFICATION TERMUX
# ============================================================

is_termux() {

    if [[ -z "${PREFIX:-}" ]]; then
        return 1
    fi

    [[ "$PREFIX" == *"com.termux"* ]]
}


# ============================================================
# INSTALLATION D'UN PAQUET
# ============================================================

install_package() {

    local package="$1"
    local command="$2"

    printf "\n------------------------------------------\n"
    printf "[!] %s n'est pas installé.\n" "$package"

    if ! ask_confirmation "Voulez-vous l'installer ?"; then
        printf "[SKIP] %s ignoré.\n" "$package"
        return 0
    fi

    printf "[...] Installation de %s...\n" "$package"

    # Pas de -y :
    # Termux peut demander lui-même confirmation.
    if pkg install "$package"; then

        if command_exists "$command"; then
            printf "[OK] %s installé.\n" "$package"
            return 0
        fi

        printf "[!] Installation terminée mais commande non trouvée : %s\n" \
            "$command"

        return 1

    else

        printf "[ERREUR] Impossible d'installer %s.\n" "$package"
        return 1
    fi
}


# ============================================================
# CONFIGURATION C
# ============================================================

configure_c() {

    local entry
    local package
    local command

    clear_screen

    printf "==========================================\n"
    printf "       CONFIGURATION C / C++\n"
    printf "==========================================\n\n"

    printf "Cette configuration va vérifier :\n"
    printf "- outils système\n"
    printf "- compilateur C\n"
    printf "- outils de compilation\n"
    printf "- LLVM\n"
    printf "- débogueurs\n\n"

    if ! ask_confirmation "Commencer la configuration ?"; then
        return
    fi

    for entry in "${C_PACKAGES[@]}"; do

        package="${entry%%:*}"
        command="${entry#*:}"

        if command_exists "$command"; then

            printf "[OK] %-15s déjà installé\n" "$package"

        else

            install_package "$package" "$command"

        fi

    done

    printf "\n==========================================\n"
    printf "       CONFIGURATION TERMINÉE\n"
    printf "==========================================\n"

    pause_screen
}


# ============================================================
# MISE À JOUR
# ============================================================

update_system() {

    clear_screen

    printf "==========================================\n"
    printf "              MISE À JOUR\n"
    printf "==========================================\n\n"

    printf "Termux va mettre à jour ses dépôts et\n"
    printf "les paquets installés.\n\n"

    if ! ask_confirmation "Voulez-vous continuer ?"; then
        return
    fi

    printf "\n[...] Mise à jour des dépôts...\n"

    if ! pkg update; then
        printf "\n[ERREUR] Échec de la mise à jour des dépôts.\n"
        pause_screen
        return
    fi

    printf "\n[...] Mise à jour des paquets...\n"

    if ! pkg upgrade; then
        printf "\n[ERREUR] Échec de la mise à jour des paquets.\n"
        pause_screen
        return
    fi

    printf "\n[OK] Mise à jour terminée.\n"

    pause_screen
}


# ============================================================
# VÉRIFICATION ENVIRONNEMENT
# ============================================================

check_environment() {

    local entry
    local package
    local command

    clear_screen

    printf "==========================================\n"
    printf "        VÉRIFICATION ENVIRONNEMENT\n"
    printf "==========================================\n\n"

    for entry in "${C_PACKAGES[@]}"; do

        package="${entry%%:*}"
        command="${entry#*:}"

        if command_exists "$command"; then

            printf "[✓] %-15s disponible\n" "$package"

        else

            printf "[!] %-15s absent\n" "$package"

        fi

    done

    pause_screen
}


# ============================================================
# LANCEMENT D'UN OUTIL
# ============================================================

launch_tool() {

    local filename="$1"
    local path="$TOOLS_DIR/$filename"

    local extension=""
    local result=0

    # --------------------------------------------------------
    # VÉRIFICATION
    # --------------------------------------------------------

    if [[ ! -f "$path" ]]; then

        printf "\n[ERREUR] Fichier introuvable : %s\n" "$path"

        pause_screen
        return 1
    fi


    # --------------------------------------------------------
    # RÉCUPÉRATION EXTENSION
    # --------------------------------------------------------

    if [[ "$filename" == *.* ]]; then
        extension="${filename##*.}"
        extension="${extension,,}"
    fi


    # --------------------------------------------------------
    # SHELL
    # --------------------------------------------------------

    case "$extension" in

        sh)

            printf "\n[...] Lancement de %s...\n\n" "$filename"

            bash "$path"
            result=$?

            ;;


        # ----------------------------------------------------
        # JAVASCRIPT
        # ----------------------------------------------------

        js)

            if ! command_exists node; then

                printf "\n[ERREUR] Node.js n'est pas installé.\n"

                pause_screen
                return 1
            fi

            printf "\n[...] Lancement de %s...\n\n" "$filename"

            node "$path"
            result=$?

            ;;


        # ----------------------------------------------------
        # PYTHON
        # ----------------------------------------------------

        py)

            local python_command=""

            if command_exists python; then
                python_command="python"
            elif command_exists python3; then
                python_command="python3"
            else
                printf "\n[ERREUR] Python n'est pas installé.\n"
                pause_screen
                return 1
            fi

            printf "\n[...] Lancement de %s...\n\n" "$filename"

            "$python_command" "$path"
            result=$?

            ;;


        # ----------------------------------------------------
        # C
        # ----------------------------------------------------

        c)

            if ! command_exists clang; then

                printf "\n[ERREUR] Clang n'est pas installé.\n"

                pause_screen
                return 1
            fi

            printf "\n[...] Compilation de %s...\n" "$filename"

            if ! clang "$path" -o "$TEMP_BINARY"; then

                printf "\n[ERREUR] Échec de la compilation.\n"

                rm -f "$TEMP_BINARY"

                pause_screen
                return 1
            fi

            printf "[...] Lancement de %s...\n\n" "$filename"

            "$TEMP_BINARY"
            result=$?

            rm -f "$TEMP_BINARY"

            ;;


        # ----------------------------------------------------
        # C++
        # ----------------------------------------------------

        cpp|cc|cxx)

            if ! command_exists clang++; then

                printf "\n[ERREUR] Clang++ n'est pas installé.\n"

                pause_screen
                return 1
            fi

            printf "\n[...] Compilation de %s...\n" "$filename"

            if ! clang++ "$path" -o "$TEMP_BINARY"; then

                printf "\n[ERREUR] Échec de la compilation.\n"

                rm -f "$TEMP_BINARY"

                pause_screen
                return 1
            fi

            printf "[...] Lancement de %s...\n\n" "$filename"

            "$TEMP_BINARY"
            result=$?

            rm -f "$TEMP_BINARY"

            ;;


        # ----------------------------------------------------
        # EXECUTABLE NATIF / AUTRE
        # ----------------------------------------------------

        *)

            if [[ ! -x "$path" ]]; then

                printf "\n[ERREUR] Ce fichier n'est pas exécutable"
                printf " ou son type n'est pas reconnu.\n"

                pause_screen
                return 1
            fi

            printf "\n[...] Lancement de %s...\n\n" "$filename"

            "$path"
            result=$?

            ;;

    esac


    # --------------------------------------------------------
    # RÉSULTAT
    # --------------------------------------------------------

    if [[ $result -eq 0 ]]; then
        printf "\n[OK] Fin de l'outil.\n"
    else
        printf "\n[!] L'outil s'est terminé avec le code : %d\n" "$result"
    fi

    pause_screen
}


# ============================================================
# MES OUTILS
# ============================================================

my_tools() {

    local tools=()
    local file
    local choice
    local index


    # --------------------------------------------------------
    # VÉRIFICATION DOSSIER
    # --------------------------------------------------------

    if [[ ! -d "$TOOLS_DIR" ]]; then

        clear_screen

        printf "==========================================\n"
        printf "               MES OUTILS\n"
        printf "==========================================\n\n"

        printf "[INFO] Le dossier %s n'existe pas.\n" "$TOOLS_DIR"
        printf "[INFO] Aucun outil personnel détecté.\n\n"

        pause_screen

        return
    fi


    # --------------------------------------------------------
    # LECTURE DU DOSSIER
    # --------------------------------------------------------

    while IFS= read -r -d '' file; do

        file="${file##*/}"

        # Ignorer le fichier temporaire C/C++
        [[ "$file" == ".tool_temp" ]] && continue

        tools+=("$file")

    done < <(
        find "$TOOLS_DIR" \
            -maxdepth 1 \
            -type f \
            -printf '%f\0' 2>/dev/null
    )


    # --------------------------------------------------------
    # LIMITE
    # --------------------------------------------------------

    if [[ ${#tools[@]} -gt 256 ]]; then
        tools=("${tools[@]:0:256}")
    fi


    # --------------------------------------------------------
    # MENU
    # --------------------------------------------------------

    while true; do

        clear_screen

        printf "==========================================\n"
        printf "               MES OUTILS\n"
        printf "==========================================\n\n"


        if [[ ${#tools[@]} -eq 0 ]]; then

            printf "[INFO] Aucun outil personnel détecté.\n\n"

            pause_screen

            return
        fi


        for index in "${!tools[@]}"; do

            printf "%d. %s\n" \
                "$((index + 1))" \
                "${tools[$index]}"

        done


        printf "\n0. Retour\n\n"
        printf "Votre choix : "

        read -r choice


        # ----------------------------------------------------
        # RETOUR
        # ----------------------------------------------------

        if [[ "$choice" == "0" ]]; then
            return
        fi


        # ----------------------------------------------------
        # VÉRIFICATION CHOIX
        # ----------------------------------------------------

        if ! [[ "$choice" =~ ^[0-9]+$ ]]; then

            printf "\n[!] Choix invalide.\n"

            pause_screen

            continue
        fi


        if (( choice < 1 || choice > ${#tools[@]} )); then

            printf "\n[!] Choix invalide.\n"

            pause_screen

            continue
        fi


        # ----------------------------------------------------
        # LANCER
        # ----------------------------------------------------

        launch_tool "${tools[$((choice - 1))]}"

    done
}


# ============================================================
# INFORMATIONS SYSTÈME
# ============================================================

system_information() {

    clear_screen

    printf "==========================================\n"
    printf "          INFORMATIONS SYSTÈME\n"
    printf "==========================================\n\n"

    printf "Version du manager : %s\n" "$VERSION"


    # --------------------------------------------------------
    # PLATEFORME
    # --------------------------------------------------------

    if is_termux; then
        printf "Plateforme         : Termux\n"
    else
        printf "Plateforme         : inconnue\n"
    fi


    # --------------------------------------------------------
    # ARCHITECTURE
    # --------------------------------------------------------

    printf "Architecture       : "

    uname -m


    # --------------------------------------------------------
    # KERNEL
    # --------------------------------------------------------

    printf "Kernel             : "

    uname -r


    # --------------------------------------------------------
    # PREFIX
    # --------------------------------------------------------

    printf "\nPREFIX             : "

    if [[ -n "${PREFIX:-}" ]]; then
        printf "%s\n" "$PREFIX"
    else
        printf "non disponible\n"
    fi


    # --------------------------------------------------------
    # SHELL
    # --------------------------------------------------------

    printf "Shell              : %s\n" "${SHELL:-inconnu}"


    # --------------------------------------------------------
    # BASH
    # --------------------------------------------------------

    printf "Bash               : %s\n" "${BASH_VERSION:-inconnu}"

    pause_screen
}


# ============================================================
# CONFIGURATION APPAREIL
# ============================================================

device_configuration() {

    local choice


    while true; do

        clear_screen


        # ----------------------------------------------------
        # START SCRIPT
        # ----------------------------------------------------

        if [[ -f "$START_SCRIPT" ]]; then
            bash "$START_SCRIPT"
        fi


        printf "==========================================\n"
        printf "       CONFIGURATION DE L'APPAREIL\n"
        printf "==========================================\n\n"

        printf "1. Configuration C\n"
        printf "2. Configuration Python\n"
        printf "3. Configuration CTF\n"
        printf "4. Configuration complète\n"
        printf "0. Retour\n\n"

        printf "Votre choix : "

        read -r choice


        case "$choice" in

            1)

                configure_c

                ;;


            2)

                printf "\n[INFO] Configuration Python prévue"
                printf " pour une prochaine version.\n"

                pause_screen

                ;;


            3)

                printf "\n[INFO] Configuration CTF prévue"
                printf " pour une prochaine version.\n"

                pause_screen

                ;;


            4)

                printf "\n[INFO] Configuration complète prévue"
                printf " pour une prochaine version.\n"

                pause_screen

                ;;


            0)

                return

                ;;


            *)

                printf "\n[!] Choix invalide.\n"

                pause_screen

                ;;

        esac

    done
}


# ============================================================
# MENU PRINCIPAL
# ============================================================

main_menu() {

    local choice


    while true; do

        clear_screen

        printf "==========================================\n"
        printf "          CTF DEV MANAGER v%s\n" "$VERSION"
        printf "==========================================\n\n"

        printf "By Dieson Parfait\n\n"

        printf "1. Configuration de l'appareil\n"
        printf "2. Mes outils\n"
        printf "3. Vérifier l'environnement\n"
        printf "4. Mise à jour\n"
        printf "5. Informations système\n"
        printf "0. Quitter\n\n"

        printf "Votre choix : "

        read -r choice


        case "$choice" in

            1)

                device_configuration

                ;;


            2)

                my_tools

                ;;


            3)

                check_environment

                ;;


            4)

                update_system

                ;;


            5)

                system_information

                ;;


            0)

                clear_screen

                printf "Au revoir !\n"

                return

                ;;


            *)

                printf "\n[!] Choix invalide.\n"

                pause_screen

                ;;

        esac

    done
}


# ============================================================
# MAIN
# ============================================================

main() {

    clear_screen


    # --------------------------------------------------------
    # START SCRIPT
    # --------------------------------------------------------

    if [[ -f "$START_SCRIPT" ]]; then
        bash "$START_SCRIPT"
    fi


    # --------------------------------------------------------
    # PAUSE INITIALE
    # --------------------------------------------------------

    read -r


    clear_screen


    # --------------------------------------------------------
    # BANNIÈRE
    # --------------------------------------------------------

    printf "==========================================\n"
    printf "          CTF DEV MANAGER v%s\n" "$VERSION"
    printf "==========================================\n\n\n\n"


    # --------------------------------------------------------
    # VÉRIFICATION TERMUX
    # --------------------------------------------------------

    if ! is_termux; then

        printf "[!] Attention : ce programme est actuellement\n"
        printf "    conçu pour Termux.\n\n"


        if ! ask_confirmation "Continuer malgré tout ?"; then
            return 0
        fi

    fi


    # --------------------------------------------------------
    # CRÉATION DU DOSSIER TOOLS
    # --------------------------------------------------------

    if [[ ! -d "$TOOLS_DIR" ]]; then

        mkdir -p "$TOOLS_DIR" 2>/dev/null || {

            printf "\n[ERREUR] Impossible de créer : %s\n" "$TOOLS_DIR"

            return 1
        }

    fi


    # --------------------------------------------------------
    # MENU
    # --------------------------------------------------------

    main_menu
}


# ============================================================
# LANCEMENT
# ============================================================

main "$@"
```
