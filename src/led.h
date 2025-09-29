#pragma once
#include "arduino.h"

/*
Énumération des couleurs que la LED peut prendre
*/
enum LedColor
{
    ColorOff = 0,
    ColorBlue = 1,
    ColorGreen = 2,
    ColorCyan = 3,
    ColorRed = 4,
    ColorWhite = 7,
};

/*
Initialisation de la LED
Cette fonction doit être appelée dans la fonction setup
*/
void led_init();

/*
Affichage de la couleur passée en paramètre
*/
void led_set_color(LedColor color);