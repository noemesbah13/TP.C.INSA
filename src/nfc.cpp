#include "nfc.h"
#include "led.h"
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
PN532_I2C pn532_i2c(Wire); //Objet correspondant au lecteur de carte I2C
NfcAdapter nfc = NfcAdapter(pn532_i2c); //Object permettant d'accéder au lecteur I2C
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

/* Cette fonction compare deux ba*/
void test_badge(struct Tag Tab[])
{
    if (tag_present()) // véérifie si un badge est présent
    {
        Tag newTag = tag_read();
        for (int i = 0;i<4;i++) {                   //parcours le tableau de tags connus
            if (tag_are_equals(newTag, Tab[i]))     //vérifie si le tag lu est dans le tableau
            {
                led_set_color(ColorGreen);
                delay(1000);
                led_set_color(ColorOff);
                return;
            }
        }
        led_set_color(ColorRed);                    //tag non reconnu dans le tableau : allume la led rouge
        delay(1000);
        led_set_color(ColorOff);
    }
    else {
        led_set_color(ColorCyan);                   //pas de tag : fait clignoter la led en cyan
        delay(500);
        led_set_color(ColorOff);
        delay(500);
    }
}
    
    //*/
