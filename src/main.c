#include <stdio.h> // printf()
#include <stdlib.h> // atoi()
#include <stdbool.h> // bool
#include <string.h> // strcmp()

#include "controlleur.h"
#include "vue.h"

int main() {
    effacer_terminal();
    inventaire_s inventaire;
    determine_quantite_pieces(inventaire, PIECES_MACHINE);
    determine_quantite_boissons(inventaire);
    affiche_menu_admin();
    cycle_journee(inventaire);
    return 0;
}
