#include <stdbool.h> // bool
#include <stdio.h> // printf()
#include <string.h> // strcmp()
#include <stdlib.h> // exit(), free(),  ()

#include "controlleur.h"
#include "modele.h"
#include "vue.h"
#include "main.h"

#ifdef _WIN32
#include <windows.h> // Sleep()
#define sleep_ms(x) Sleep(x)

#else
#include <unistd.h> // sleep()
#define sleep_ms(x) sleep(x / 1000) // Convert ms to s

#endif

/*
    * Fonction qui gere le mode admin. Redirige selon le choix de l'admin
    * @param inventaire_s inventaire
    * @param char* hashed_mdp
*/
void mode_admin(inventaire_s* inventaire, char* mdp) {
    int choix = AIDE_ADMIN;
    while(choix != FINIR) {
        choix = selection_admin();
        // On effectue l'action selon le choix de l'admin
        switch(choix) {
        case ALIMENTATION_PIECES:
            determine_quantite_pieces(inventaire, PIECES_MACHINE);
            if(!est_piece_valide(choix)) {
                printf("\nVeuillez entrer des pièces valide");
            }
            continue;

        case ALIMENTATION_BOISSONS:
            determine_quantite_boissons(inventaire);
            if(est_boisson_valide(choix)) {
                printf("\nVeuillez entrer des boissons valide");
            }
            continue;

        case AFFICHAGE_PIECES:
            printf("\n**Etat des pieces**");
            affiche_quantite_pieces(inventaire, PIECES_MACHINE);
            continue;

        case AFFICHAGE_BOISSONS:
            printf("\n**Stock de boissons restances**");
            affiche_quantite_boissons(inventaire);
            continue;

        case AIDE_ADMIN:
            effacer_terminal();
            choix = selection_admin();
            continue;

        case CHANGE_MDP:
            change_mdp(mdp);
            continue;

        case FINIR:
            printf("\nAu revoir\n");
            exit(0);

        case CHANGE_MODE:
            effacer_terminal();
            mode_vente(inventaire, mdp);
            continue;

        default:
            printf("\nVeuillez entrer un choix valide");
            continue;
        }
    }
}

/*
    * Fonction qui change le mot de passe (hash + sauvegarde)...
    * ...apres validation du mdp actuel. 
*/
void change_mdp(char* mdp) {
    char nouveau_mdp[MAX_INPUT];
    if(est_mdp_valide(mdp)) {
        printf("\nVeuillez entrer le nouveau mot de passe : ");
        scanf("%s", nouveau_mdp);
        hash_mdp(nouveau_mdp);
        sauvegarde_mdp(nouveau_mdp);
    }
}

/*
    * Fonction qui gere le mode vente selon la boisson choisie
    * @param inventaire_s inventaire
    * @param char* hashed_mdp
*/
void mode_vente(inventaire_s* inventaire, char* mdp) {
    int choix = NB_TYPE_BOISSONS;
    while(1) {
        // Le client choisit la boisson et on verifie si le choix est valide
        choix = selection_boisson();
        if(!est_boisson_valide(choix)) {
            printf("\nVeuillez entrer un choix valide");
            continue;
        }

        // Reset les pieces de paiement et efface le terminal
        effacer_terminal();
        reset_pieces(inventaire, PIECES_PAIEMENT);

        // On effectue la vente selon le choix de la boisson
        switch(choix) {
        case CAPPUCINO:
            printf(
                "\n\nCappucino, prix : %d centimes\nVeuillez inserer les pieces",
                boissons_map[CAPPUCINO].prix);
            determine_quantite_pieces(inventaire, PIECES_PAIEMENT);
            vente(inventaire, CAPPUCINO);
            continue;

        case EXPRESSO:
            printf(
                "\n\nCappucino, prix : %d centimes\nVeuillez inserer les pieces",
                boissons_map[EXPRESSO].prix);
            determine_quantite_pieces(inventaire, PIECES_PAIEMENT);
            vente(inventaire, EXPRESSO);
            continue;

        case CHOCOLAT:
            printf(
                "\n\nCappucino, prix : %d centimes\nVeuillez inserer les pieces",
                boissons_map[CHOCOLAT].prix);
            determine_quantite_pieces(inventaire, PIECES_PAIEMENT);
            vente(inventaire, CHOCOLAT);
            continue;

        case THE_CITRON:
            printf(
                "\n\nCappucino, prix : %d centimes\nVeuillez inserer les pieces",
                boissons_map[THE_CITRON].prix);
            determine_quantite_pieces(inventaire, PIECES_PAIEMENT);
            vente(inventaire, THE_CITRON);
            continue;

        case POTAGE:
            printf(
                "\n\nCappucino, prix : %d centimes\nVeuillez inserer les pieces",
                boissons_map[POTAGE].prix);
            determine_quantite_pieces(inventaire, PIECES_PAIEMENT);
            vente(inventaire, POTAGE);
            continue;

        case CHANGE_MODE:
            if(est_mdp_valide(mdp)) {
                mode_admin(inventaire, mdp);
            }
            continue;

        default:
            printf("\nVeuillez entrer un choix valide");
            continue;
        }
    }
}

/* 
    * Fonction qui effectue la vente.
    * Categorise la vente selon le montant insere par l'utilisateur et le prix de la boisson
    * @param inventaire_s inventaire
    * @param int boisson_id
*/
void vente(inventaire_s* inventaire, int boisson_id) {
    // Montant total inserer par l'utilisateur ainsi que le prix de la boisson
    int prix = boissons_map[boisson_id].prix, somme = 0, reste_a_rendre;
    for(int i = 0; i < NB_TYPE_PIECES; i++) {
        somme += inventaire->pieces[PIECES_PAIEMENT][pieces_map[i].id].quantite * pieces_map[i].id;
    }

    // La machine recoit les pieces de paiement
    operation_pieces(inventaire, PIECES_MACHINE, PIECES_PAIEMENT, ADDITION);

    // Vente invalide - paiement insuffisant
    if(somme < prix) {
        printf("\nMonnaie inserer insuffisante, annulation de la vente");
        operation_pieces(inventaire, PIECES_MACHINE, PIECES_PAIEMENT, SOUSTRACTION);
        printf("\nMonnaie rendue : ");
        affiche_quantite_pieces(inventaire, PIECES_PAIEMENT);
        return;
    }

    // Vente invalide - boisson hors stock
    if(inventaire->boissons[boisson_id].quantite == 0) {
        printf("\nBoisson hors stock, annulation de la vente\nVeuillez en choisir une autre");
        operation_pieces(inventaire, PIECES_MACHINE, PIECES_PAIEMENT, SOUSTRACTION);
        printf("\nMonnaie rendue : ");
        affiche_quantite_pieces(inventaire, PIECES_PAIEMENT);
        return;
    }

    printf("\nVente en cours...");
    fflush(stdout); // On vide le buffer, forcant l'affichage avant de sleep
    sleep_ms(1000); // C'est estiqtiue, on fait semblant de calculer

    // Vente valide - montant exact
    if(somme == prix) {
        inventaire->boissons[boisson_id].quantite--;
        afficher_vente_boisson();
        return;
    }

    // Vente valide si la machine peut rendre la monnaie
    if(somme > prix) {
        // Reset les pieces a rendre des vente precedentes
        reset_pieces(inventaire, PIECES_A_RENDRE);

        // On calcule s'il reste de la monnaie que la machine ne peut rendre
        reste_a_rendre = calcul_monnaie_a_rendre(inventaire, somme - prix);

        // La machine peut rendre la monnaie
        if(reste_a_rendre == 0) {
            inventaire->boissons[boisson_id].quantite--;
            rendre_monnaie(inventaire);
            printf("\n\nVente effectue - Monnaie rendue: ");
            affiche_quantite_pieces(inventaire, PIECES_A_RENDRE);
            afficher_vente_boisson();
            return;
        }

        // La machine ne peut pas rendre la monnaie
        printf("\n\nAnulation de la vente, la machine manque de pieces pour rendre la monnaie");
        operation_pieces(inventaire, PIECES_MACHINE, PIECES_PAIEMENT, SOUSTRACTION);
        printf("\nMonnaie rendue : ");
        affiche_quantite_pieces(inventaire, PIECES_PAIEMENT);
        return;
    }
}

/* 
    * Effectue une operation entre les 2 categories de pieces
    * -> Pieces de categorie 1 +/- Pieces de categorie 2
    * @param inventaire_s inventaire
    * @param int 1ere categorie de piece
    * @param int 2eme categorie de piece
    * @param int operation (Addition ou soustraction)
*/
void operation_pieces(inventaire_s* inventaire, int p1, int p2, int operation) {
    for(int i = 0; i < NB_TYPE_PIECES; i++) {
        inventaire->pieces[p1][pieces_map[i].id].quantite +=
            (inventaire->pieces[p2][pieces_map[i].id].quantite * operation);
    }
}

/*
    * Fonction qui reset a 0 les pieces de la categorie donnee
    * @param inventaire_s inventaire
    * @param categorie_pieces_e categorie
*/
void reset_pieces(inventaire_s* inventaire, categorie_pieces_e categorie) {
    for(int i = 0; i < NB_TYPE_PIECES; i++) {
        inventaire->pieces[categorie][pieces_map[i].id].quantite = 0;
    }
}

/* 
    * Fonction qui rend la monnaie, retirant les pieces de la machine.
    * Annule la vente si la machine n'a pas assez de pieces pour rendre la monnaie
    * @param inventaire_s inventaire
    * @param int a_rendre
*/
void rendre_monnaie(inventaire_s* inventaire) {
    for(int i = 0; i < NB_TYPE_PIECES; i++) {
        inventaire->pieces[PIECES_MACHINE][pieces_map[i].id].quantite -=
            inventaire->pieces[PIECES_A_RENDRE][pieces_map[i].id].quantite;
    }
}

/*
    * Fonction qui calcule la monnaie a rendre.
    * Transfere les pieces a_rendre a la categorie PIECES_A_RENDRE
    * @param inventaire_s inventaire
    * @param int a_rendre
    * @return int - a_rendre, 0 si la machine peut rendre la monnaie
*/
int calcul_monnaie_a_rendre(inventaire_s* inventaire, int a_rendre) {
    // while(a_rendre > 0) {
    for(int i = 0; i < NB_TYPE_PIECES; i++) {
        // Les pieces sont ordonnees de plus grands au plus petit (voir modele.c et .h)
        // Donc on prioritise de rendre les plus grandes pieces (comme une machine normale)
        if(a_rendre >= pieces_map[i].id &&
           inventaire->pieces[PIECES_MACHINE][pieces_map[i].id].quantite > 0) {
            inventaire->pieces[PIECES_A_RENDRE][pieces_map[i].id].quantite++;
            a_rendre -= pieces_map[i].id;
        }
    }
    // }
    // Si la machine n'as pas assez de pieces, il vas rester de la monnaie a rendre
    return a_rendre;
}

/*
    * Fonction qui verifie si le mot de passe est valide. 
    * Compare les hashs du mot de passe entree et du mot de passe sauvegarde
    * @return bool - true si le mot de passe est valide */
bool est_mdp_valide(char* mdp) {
    // On demande le mot de passe
    char temptative_mdp[MAX_INPUT];
    printf("\nVeuillez entrer le mot de passe : ");
    scanf("%s", temptative_mdp);

    // On fais du hashiparmentier avec le mdp entree par l'utilisateur
    hash_mdp(temptative_mdp);

    // On charge le mdp actuel, au cas ou yas eu un changement de mdp
    chargement_mdp(mdp);

    // Si les hashs sont differents, on dit false!
    if(strcmp(temptative_mdp, mdp) != 0) {
        printf("\nMot de passe incorrect (Sleep anti brute force)");
        sleep_ms(1500);
        return false;
    }
    return true; // Sinon, on dit true!
}

/*
    * Fonction qui verifie si le choix de boisson est dans la liste des boissons
    * @param int choix_boisson
    * @param inventaire_s inventaire
    * @return bool - True si le choix est une boisson ou un changement de mode
*/
bool est_boisson_valide(int choix_boisson) {
    if(choix_boisson >= CAPPUCINO || choix_boisson < NB_TYPE_BOISSONS ||
       choix_boisson == CHANGE_MODE) {
        return true;
    }
    return false;
}

/*
    * Fonction qui verifie si le choix de piece est dans la liste des pieces
    * @param int choix_piece
    * @return bool - true si c'est une piece acceptable, crisse on veut pas se faire arnaquer
*/
bool est_piece_valide(int choix_piece) {
    if(choix_piece <= pieces_map[0].id || choix_piece >= pieces_map[NB_TYPE_PIECES - 1].id) {
        return true;
    }
    return false;
}
