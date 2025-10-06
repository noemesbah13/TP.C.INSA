#include"clavier.h"
#include "lcd.h"
#include <stdio.h>


enum touche clavier()
{
    static enum touche oldPress = aucune;
    int value=analogRead(A0);
    enum touche newPress = aucune;
    if (value<51) {newPress = droit;}
    else if (value<201) {newPress = haut;}
    else if (value<351) {newPress = bas;}
    else if (value<501) {newPress = gauche;}
    else if (value<751) {newPress = select;}
    else {newPress = aucune;}
    if (oldPress==newPress){return aucune;}
    oldPress = newPress; return newPress;
}

void afficheLCD()
{
    switch (clavier())
    {
        case haut:
        lcd_print(0,"haut");
        break;
        case bas :
        lcd_print(0,"bas");
        break;
        case droit:
        lcd_print(0,"droit");
        break;
        case gauche:
        lcd_print(0,"gauche");
        break;
        case select:
        lcd_print(0,"select");
        break;
        default:
        lcd_print(0,"none");

    }

}