#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "vue.h"
#include "modele.h"
#include "controlleur.h"

/*
    * Fonction qui affiche le menu de la machine
    * @return int le choix de l'utilisateur
*/
int selection_boisson() {
    int choix_boisson;
    printf("\n\n**Faites votre choix**");
    for(int i = 0; i < NB_TYPE_BOISSONS; i++) {
        printf("\nPour un %s : %d, taper %d", boissons_map[i].nom, boissons_map[i].prix, i);
    }
    printf("\nVotre choix : ");
    scanf("%d", &choix_boisson);
    return choix_boisson;
}

/*
    * Fonction qui determine la quantite de pieces a alimenter
    * @param inventaire_s inventaire
    * @param categorie_pieces_e categorie
*/
void determine_quantite_pieces(inventaire_s* inventaire, categorie_pieces_e categorie) {
    printf("\n\n**Alimentation des pieces**\n");
    for(int i = 0; i < NB_TYPE_PIECES; i++) {
        printf("Nombre de pieces de %s: ", pieces_map[i].nom);
        scanf("%d", &inventaire->pieces[categorie][pieces_map[i].id].quantite);

        if(!est_piece_valide(inventaire->pieces[categorie][pieces_map[i].id].id)) {
            printf("\nVeuillez entrer une piece valide");
            determine_quantite_pieces(inventaire, categorie);
        }
    }
}

/*
    * Fonction qui determine la quantite de boissons a alimenter
    * @param inventaire_s inventaire
*/
void determine_quantite_boissons(inventaire_s* inventaire) {
    printf("\n\n**Alimentation des boissons**\n");
    for(int i = 0; i < NB_TYPE_BOISSONS; i++) {
        printf("Nombre de boissons de %s : ", boissons_map[i].nom);
        scanf("%d", &inventaire->boissons[i].quantite);
        if(!est_boisson_valide(inventaire->boissons[i].id)) {
            printf("\nVeuillez entrer une boisson valide");
            determine_quantite_boissons(inventaire);
        }
    }
}

/*
    * Fonction qui affiche la quantite de pieces
    * @param inventaire_s machine
    * @param categorie_pieces_e categorie
*/
void affiche_quantite_pieces(inventaire_s* inventaire, categorie_pieces_e categorie) {
    for(int i = 0; i < NB_TYPE_PIECES; i++)
        printf(
            "\nNombre de pieces de %s : %d",
            pieces_map[i].nom,
            inventaire->pieces[categorie][pieces_map[i].id].quantite);
}

/*
    * Fonction qui affiche la quantite de boissons
    * @param inventaire_s machine
*/
void affiche_quantite_boissons(inventaire_s* machine) {
    for(int i = 0; i < NB_TYPE_BOISSONS; i++)
        printf(
            "\nNombre de boissons de %s : %d", boissons_map[i].nom, machine->boissons[i].quantite);
}

/*
    * Fonction qui efface le terminal
*/
void effacer_terminal() {
    printf("\033[2J\033[H");
}

/*
    * Art ASCII de vente de boisson
*/
void afficher_vente_boisson() {
    printf(
        "\n\n      ) (                                                                                                         ) (\n");
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

/*
    * Fonction qui affiche le menu d'aide pour les administrateurs
    * @return int le choix de l'utilisateur
*/
int selection_admin() {
    printf("\n\n**Menu d'aide - reserve aux administrateurs**");
    printf("\nPour alimenter la machine en pieces taper %d", ALIMENTATION_PIECES);
    printf("\nPour alimenter la machine en boissons taper %d", ALIMENTATION_BOISSONS);
    printf("\nPour afficher l'etat des pieces de la machine taper %d", AFFICHAGE_PIECES);
    printf("\nPour afficher l'etat des boissons de la machine taper %d", AFFICHAGE_BOISSONS);
    printf("\nPour afficher le menu d'aide taper %d", AIDE_ADMIN);
    printf("\nPour changer le mot de passe taper %d", CHANGE_MDP);
    printf("\nPour quitter taper %d", FINIR);
    printf("\nPour alterner entre mode admin et mode vente : taper %d", CHANGE_MODE);
    printf("\nVotre choix : ");
    int choix;
    scanf("%d", &choix);
    return choix;
}
