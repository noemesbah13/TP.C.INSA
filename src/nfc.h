#pragma once
#include "arduino.h"

/*
Définition du type Tag, contenant les informations du badge présenté sur le
lecteur NFC.
*/

enum etat
{
    attente,
    ouverture,
    badgeInconnu,
    menuAdmin,
    demarage
};

enum page
{
    un,
    deux,
    trois,
    quatre
};

bool reconnait_badge_admin(struct Tag tag);

struct Tag
{
byte uid[4];
};

/*
Initialisation du lecteur NFC
Cette fonction doit être appelée dans la fonction setup
*/
bool nfc_init();

/*
Permet de vérifier si un badge est présent sur le lecteur NFC.
*/
bool tag_present();

/*
Lis les informations du badge présent sur le lecteur NFC.
S’il n'y a pas de badge, la fonction est bloquante jusqu'à ce qu'un badge soit
présenté.
*/
struct Tag tag_read();

/*
Teste si les deux tags passes en parametres sont identiques.
retourne 1 si les deux tags sont identiques et 0 sinon.
*/
bool tag_are_equals(struct Tag tag1, struct Tag tag2);

/*
Teste si le Tag qui passe devant le capteur NFC appartient
au tableau passe en parametre et allume la led en vert s'il 
appartient et en rouge sinon.
*/
void test_badge();

void interface();
void Admin();