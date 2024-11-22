#ifndef CONTROLLEUR_H
#define CONTROLLEUR_H

#include "modele.h"

void mode_admin(inventaire_s* inventaire, char* mdp);
void change_mdp(char* mdp);

// Fonctions de la gestion des ventes
void mode_vente(inventaire_s* inventaire, char* mdp);
bool est_mdp_valide(char* mdp);
bool est_boisson_valide(int choix_boisson);
bool est_piece_valide(int choix_piece);

// Fonctions de gestion des pieces
void vente(inventaire_s* inventaire, int boisson_id);
void rendre_monnaie(inventaire_s* inventaire);
void operation_pieces(inventaire_s* inventaire, int p1, int p2, int operation);
int calcul_monnaie_a_rendre(inventaire_s* inventaire, int a_rendre);
void reset_pieces(inventaire_s* inventaire, categorie_pieces_e categorie);

#endif
