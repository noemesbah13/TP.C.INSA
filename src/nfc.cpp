#include "nfc.h"
#include "led.h"
#include "lcd.h"
#include "rtc.h"
#include "clavier.h"
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire); //Objet correspondant au lecteur de carte I2C
NfcAdapter nfc = NfcAdapter(pn532_i2c); //Object permettant d'accéder au lecteur I2C

int menus=3;

bool nfc_init()
{
    nfc.begin();
    return true;
}
bool tag_present()
{
return nfc.tagPresent(100);
}
struct Tag tag_read()
{
    Tag tag;
    NfcTag nfcTag = nfc.read();
    nfcTag.getUid(tag.uid, sizeof(tag.uid)/sizeof(byte));
    return tag;
}

/*Renvoie vraie si les deux tags sont égaux*/
bool tag_are_equals(struct Tag tag1, struct Tag tag2) {
    if (memcmp(&tag1, &tag2, sizeof(struct Tag)) == 0)      //verifie si les deux tags sont égaux
    {
        return true;                                        //tags égaux : retourne vrai
    }
    else 
    {
        return false;                                       //tags différents : retourne faux
    }
}
const struct Tag tagNull = {0x00, 0x00, 0x00, 0x00};
struct Tag tagAdmin = tagNull;
struct Tag tagUser = tagNull;
enum etat etat = demarage;

bool reconnait_badge_admin(struct Tag tag)
{
    if (tag_are_equals(tagNull,tagAdmin)) {tagAdmin = tag;}
    if (tag_are_equals(tagAdmin, tag)) {etat = menuAdmin; return true;}
    else {return false;}
}

bool reconnait_badge_util(struct Tag tag)
{
    if (tag_are_equals(tagUser, tag)) {etat = ouverture; return true;}
    else {return false;}
}

/* Cette fonction compare deux badges et fait clignoter la LED dans la couleur appropriée
en fonction de la présence ou non du tag dans le tableau*/
void test_badge()
{
    if (tag_present()) // vérifie si un badge est présent
    {
        Tag newTag = tag_read();                   //parcours le tableau de tags connus
        if (reconnait_badge_admin(newTag)||reconnait_badge_util(newTag))     //vérifie si le tag lu existe
        {
            led_set_color(ColorGreen);
            delay(1000);
            led_set_color(ColorOff);
            return;
        }
        
    }
    else {
        led_set_color(ColorCyan);                   //pas de tag : fait clignoter la led en cyan
        delay(250);
        led_set_color(ColorOff);
        delay(250);
    }
}

void interface() 
{
    switch (etat)
    {
        case attente:
            afficherTime();
        break;
        case ouverture:
            lcd_print(0,"Ouverture");
            lcd_print(1," ");
            delay(5000);
            etat=attente;
        break;
        case badgeInconnu:
            lcd_print(0,"Acess denied");
            lcd_print(1," ");
            led_set_color(ColorRed);                    //tag non reconnu dans le tableau : allume la led rouge
            delay(1000);
            led_set_color(ColorOff);
            delay(1000);
            etat=attente;
        break;
        case menuAdmin:
            Admin();
        break;
        case demarage:
            while (!tag_present())
            {
                lcd_print(0,"Presentez badge");
                lcd_print(1,"admin");
            }
        tagAdmin=tag_read();
        lcd_print(0,"Badge admin");
        lcd_print(1,"enregistre");
        delay(1000);
        etat=attente;
            
    }
}


/*-----------------Gestion interface-------------------*/


void ajoutUser()
{
    tagUser=tagNull;
    lcd_print(0,"Presentez badge");
    lcd_print(1,"utilisateur :");
    float time=millis();
    while (millis()<(time+4000))
    {if (tag_present()){tagUser=tag_read();etat=attente;return;}}  
}
void modifierAdmin()
{
    tagAdmin=tagNull;
    lcd_print(0,"Presentez badge");
    lcd_print(1,"admin :");
    int time=millis();
    while (millis()<(time+4000))
    {if (tag_present()){tagUser=tag_read();etat=attente;return;}}
}

void Admin()
{
    while (etat==menuAdmin)
    {
    lcd_print(0,"User R | Heure U");
    lcd_print(1,"Admin L | Exit D");
    switch (clavier())
    {
        case droit:
        lcd_print(1," ");
        ajoutUser();
        break;
        case gauche:
        lcd_print(1," ");
        modifierAdmin();
        break;
        case bas:
        etat=attente;
        break;
    }
    }
     
}


