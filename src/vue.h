#ifndef VUE_H
#define VUE_H

#include "modele.h"

void effacer_terminal();
int selection_menu();
void affiche_menu_admin();
int determine_quantite_pieces(inventaire_s inventaire, categorie_pieces_e categorie);
int determine_quantite_boissons(inventaire_s inventaire);
void affiche_quantite_pieces(inventaire_s inventaire, categorie_pieces_e categorie);
void affiche_quantite_boissons(inventaire_s inventaire);
void afficher_vente_boisson();

#endif
