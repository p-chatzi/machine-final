#include <stdio.h>

#include "vue.h"
#include "modele.h"

int selection_boisson() {
    int choix_boisson;
    printf("\n\n**Faites votre choix**");
    for(int i = 0; i < NB_TYPE_BOISSONS; i++)
        printf("\n%s : %d, taper %d", boissons_map[i].nom, boissons_map[i].prix, i);
    return choix_boisson;
}

int determine_quantite_pieces(inventaire_s inventaire, categorie_pieces_e categorie) {
    printf("\n**Alimentation des pieces**");
    for(int i = 0; i < NB_TYPE_PIECES; i++) {
        printf("\nNombre de pieces de %s : ", pieces_map[i].nom);
        scanf("%d", inventaire.pieces[categorie][i].quantite);
    }
    return inventaire.pieces[categorie];
}

int determine_quantite_boissons(inventaire_s inventaire) {
    printf("\n**Alimentation des boissons**");
    for(int i = 0; i < NB_TYPE_BOISSONS; i++) {
        printf("\nNombre de boissons de %s : ", boissons_map[i].nom);
        scanf("%d", inventaire.boissons[i].quantite);
    }
    return inventaire.boissons;
}

void affiche_quantite_pieces(inventaire_s machine, categorie_pieces_e categorie) {
    printf("\n**Etat des pieces**");
    for(int i = 0; i < NB_TYPE_PIECES; i++)
        printf(
            "\nNombre de pieces de %s : %d",
            pieces_map[i].nom,
            machine.pieces[categorie][i].quantite);
}

void affiche_quantite_boissons(inventaire_s machine) {
    printf("\n**Stock de boissons restances**");
    for(int i = 0; i < NB_TYPE_BOISSONS; i++)
        printf(
            "\nNombre de boissons de %s : %d", boissons_map[i].nom, machine.boissons[i].quantite);
}

void effacer_terminal() {
    printf("\033[2J\033[H");
}

void afficher_vente_boisson() {
    printf(
        "\n      ) (                                                                                                         ) (\n");
    printf(
        "     (   ) )                                                                                                     (   ) )\n");
    printf(
        "      ) ( (                                                                                                       ) ( (\n");
    printf(
        "    _______)_                                                                                                   _______)_\n");
    printf(
        " .-'---------|                                                                                               .-'---------|\n");
    printf(
        "( C|/\\/\\/\\/\\/|                       Bonne consommation et bonne journee a vous! :)                         ( C|/\\/\\/\\/\\/|\n");
    printf(
        " '-./\\/\\/\\/\\/|                                                                                               '-./\\/\\/\\/\\/|\n");
    printf(
        "   '_________'                                                                                                 '_________'\n");
    printf(
        "    '-------'                                                                                                   '-------'\n");
}

void affiche_menu_admin() {
    printf("\n\n**Menu d'aide - reserve aux administrateurs**");
    printf("\nPour alimenter la machine en pieces taper %d", ALIMENTATION_PIECES);
    printf("\nPour alimenter la machine en boissons taper %d", ALIMENTATION_BOISSONS);
    printf("\nPour afficher l'etat des pieces taper %d", AFFICHAGE_PIECES);
    printf("\nPour afficher l'etat des boissons taper %d", AFFICHAGE_BOISSONS);
    printf("\nPour afficher le menu d'aide taper %d", AIDE_ADMIN);
    printf("\nPour quitter taper %d", FINIR);
    printf("\n\nPour alterner entre mode admin et mode vente : taper %d", CHANGE_MODE);
}
