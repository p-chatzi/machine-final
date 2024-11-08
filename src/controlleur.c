#include <stdbool.h>

#ifdef _WIN32
#include <windows.h> // Sleep()
#define sleep_ms(x) Sleep(x)

#else
#include <unistd.h> // sleep()
#define sleep_ms(x) sleep(x / 1000) // Convert ms to s

#endif

#include "modele.h"
#include "vue.h"

void cycle_journee(inventaire_s inventaire) {
    int choix = AIDE_ADMIN;

    while(choix == !FINIR) {
        effacer_terminal();

        choix = selection_boisson();
        if(!est_choix_valide(choix, inventaire)) {
            choix = selection_boisson();
            continue;
        }

        switch(choix) {
            // Alimente le stock de pieces que ce soit : machine, paiement ou a rendre
        case ALIMENTATION_PIECES:
            mdp_admin();
            determine_quantite_pieces(inventaire, PIECES_MACHINE);
            if(!est_piece_valide(choix)) {
                printf("\nVeuillez entrer une pièce valide");
                choix = selection_piece();
                continue;
            }
            break;

            // Alimente le stock de boissons
        case ALIMENTATION_BOISSONS:
            mdp_admin();
            determine_quantite_boissons(inventaire);
            if(!est_boisson_valide(choix, inventaire)) {
                printf("\nVeuillez entrer un choix valide");
                continue;
            }
            continue;

            // Affiche le stock de pieces restantes
        case AFFICHAGE_PIECES:
            mdp_admin();
            affiche_quantite_pieces(inventaire, PIECES_MACHINE);
            continue;

            // Affiche le stock de boissons restantes (Un client peut y avoir acces, pcq jsuis gentil)
        case AFFICHAGE_BOISSONS:
            affiche_quantite_boissons(inventaire);
            continue;

            // Mode de vente de boissons
        case CHANGE_MODE:
            mode_vente(inventaire);
            continue;

            // Liste des commandes disponobiles
        case AIDE_ADMIN:
            mdp_admin();
            affiche_menu_admin();
            continue;

            // Fin de la journée
        case FINIR:
            mdp_admin();
            return;

        default:
            printf("\nVeuillez entrer un choix valide");
            break;
        }
    }
}

void mode_vente(inventaire_s inventaire) {
    int choix_boisson = selection_boisson();
    if(!est_boisson_valide(choix_boisson, inventaire)) {
        printf("\nVeuillez entrer un choix valide");
        choix_boisson = selection_boisson();
        return;
    }
}

void mdp_admin() {
    char mdp[10];
    printf("\nVeuillez entrer le mot de passe : ");
    scanf("%s", mdp);
    if(strcmp(mdp, "4dm1n") != 0) { // MDP insecure temporairement pour les tests
        printf("\nMot de passe incorrect (Sleep anti brute force - patience)");
        sleep_ms(3000);
    }
    return true;
}

bool est_boisson_valide(int choix_boisson, inventaire_s inventaire) {
    if(choix_boisson < CAPPUCINO || choix_boisson >= NB_TYPE_BOISSONS) {
        printf("\nVeuillez entrer un choix valide");
        choix_boisson = selection_boisson();
        return false;
    }
    return true;
}

bool est_piece_valide(int choix_piece) {
    if(choix_piece < DEUX_EUROS || choix_piece >= NB_TYPE_PIECES) {
        printf("\nVeuillez entrer une pièce valide");
        choix_piece = selection_piece();
        return false;
    }
    return true;
}
