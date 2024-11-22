#ifndef VUE_H
#define VUE_H

#include "modele.h"

void effacer_terminal();
int selection_boisson();
int selection_admin();
void determine_quantite_pieces(inventaire_s* inventaire, categorie_pieces_e categorie);
void determine_quantite_boissons(inventaire_s* inventaire);
void affiche_quantite_pieces(inventaire_s* inventaire, categorie_pieces_e categorie);
void affiche_quantite_boissons(inventaire_s* inventaire);
void afficher_vente_boisson();

int input_int_utilisateur();

#endif
