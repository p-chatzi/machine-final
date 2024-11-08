#ifndef CONTROLLEUR_H
#define CONTROLLEUR_H

void cycle_journee(inventaire_s inventaire);

bool est_boisson_valide(int choix_boisson, inventaire_s inventaire);
bool est_piece_valide(int choix_piece);
bool est_admin();
void mode_vente(inventaire_s inventaire);

#endif
