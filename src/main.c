#include <stdio.h> // fopen()
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // memset(), strnlen()

#include "controlleur.h"
#include "vue.h"
#include "modele.h"
#include "main.h"

/*
    * Fonction qui sauvegarde le mot de passe
    * @return char* le mot de passe
*/
void sauvegarde_mdp(char* mdp) {
    FILE* fichier_mdp = fopen("mdp.txt", "w");
    if(fichier_mdp == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier");
        exit(1);
    }
    fprintf(fichier_mdp, "%s", mdp);
    fclose(fichier_mdp);
}

/*
    * Fonction qui charge le mot de passe
    * @return char* le mot de passe
*/
void chargement_mdp(char* mdp) {
    FILE* fichier_mdp = fopen("mdp.txt", "r");
    if(fichier_mdp == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier");
        exit(1);
    }
    fscanf(fichier_mdp, "%s", mdp);
    fclose(fichier_mdp);
}

/*
    * Fonction qui hash le mot de passe.
    * Hash avec en additionant des valeurs ASCII
    * @param char* mdp - le mot de passe qui passe au hashsage
*/
void hash_mdp(char* mdp) {
    for(int i = 0; i < strlen(mdp); i++) {
        // 126 - 33 = 93. 93 / 2 = 46. Et (126 + 33) / 2 = 79
        // Pour etre sur d'etre etre 126"~" et 33"!",
        // 79 - 46 = 33 et 78 + 46 = 124.
        // Les valeurs ASCII entre 33 et 126 sont tous des characteres.
        if(mdp[i] + 79 > 126) { // if(mdp[i] + 'O' > '~') si on est psycopathe
            mdp[i] = mdp[i] - 46;
        } else {
            mdp[i] = mdp[i] + 46;
        }
    }
}

int main() {
    effacer_terminal();
    inventaire_s inventaire;

    // On determine la quantite initial de pieces et de boissons
    determine_quantite_pieces(&inventaire, PIECES_MACHINE);
    determine_quantite_boissons(&inventaire);
    // (C'etait pour mes tests, je laisse ici pour des tests manuels plus rapide)
    // for(int i = 0; i < NB_TYPE_PIECES; i++) {
    //     inventaire.pieces[PIECES_MACHINE][i].nom = pieces_map[i].nom;
    //     inventaire.pieces[PIECES_MACHINE][i].id = pieces_map[i].id;
    //     inventaire.pieces[PIECES_MACHINE][pieces_map[i].id].quantite = 0;
    // }
    // for(int i = 0; i < NB_TYPE_BOISSONS; i++) {
    //     inventaire.boissons[i].nom = boissons_map[i].nom;
    //     inventaire.boissons[i].id = boissons_map[i].id;
    //     inventaire.boissons[i].prix = boissons_map[i].prix;
    //     inventaire.boissons[i].quantite = 2;
    // }

    char mdp[MAX_INPUT];
    FILE* fichier_mdp = fopen("mdp.txt", "r");
    // S'il n'existe pas de mdp (absence du fichier mdp.txt), on en demande un
    // On force donc l'admin/propietaire a avoir un mdp
    if(fichier_mdp == NULL) {
        printf("\nVeuillez entrer le nouveau mot de passe : ");
        scanf("%99s", mdp);
        hash_mdp(mdp);
        sauvegarde_mdp(mdp);
        printf("\nNouveau mot de passe créé et sauvegardé");
    } else { // Sinon on charge le mdp existant
        fclose(fichier_mdp);
        chargement_mdp(mdp);
    }

    // Et c'est parti!
    mode_admin(&inventaire, mdp);
    return 0;
}
