#pragma once
#include "Arduino.h"

enum touche
{
    droit,
    gauche,
    haut,
    bas,
    select,
    aucune
};

enum touche clavier();
void afficheLCD();


