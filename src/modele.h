#ifndef MODEL_H
#define MODEL_H

#define MAX_INPUT 32
typedef enum valeure_pieces {
    DEUX_EUROS = 200,
    UN_EURO = 100,
    CINQUANTE_CENTIMES = 50,
    VINGT_CENTIMES = 20,
    DIX_CENTIMES = 10,
    CINQUE_CENTIMES = 5,

    NB_TYPE_PIECES = 6
} valeure_e;

typedef enum categorie_pieces {
    PIECES_MACHINE,
    PIECES_PAIEMENT,
    PIECES_A_RENDRE,

    NB_CATEGORIE_PIECES
} categorie_pieces_e;

typedef enum type_boissons {
    CAPPUCINO,
    EXPRESSO,
    CHOCOLAT,
    THE_CITRON,
    POTAGE,

    NB_TYPE_BOISSONS
} boissons_e;

typedef enum commandes {
    ALIMENTATION_PIECES,
    ALIMENTATION_BOISSONS,
    AFFICHAGE_PIECES,
    AFFICHAGE_BOISSONS,
    AIDE_ADMIN,
    CHANGE_MDP,
    FINIR,

    NB_CMDS,
    CHANGE_MODE = 444
} commandes_e;

typedef enum status_vente {
    VENTE_VALIDE,
    VENTE_INVALIDE
} status_vente_e;

typedef enum operation {
    ADDITION = 1,
    SOUSTRACTION = -1
} operation_e;

typedef struct pieces {
    char* nom;
    valeure_e id; // renommer en val?
    int quantite;
} pieces_s;

typedef struct boissons {
    char* nom;
    boissons_e id;
    int prix;
    int quantite;
} boissons_s;

typedef struct inventaire {
    pieces_s pieces[NB_CATEGORIE_PIECES][NB_TYPE_PIECES];
    boissons_s boissons[NB_TYPE_BOISSONS];
} inventaire_s;

extern const pieces_s pieces_map[];
extern const boissons_s boissons_map[];

#endif
