/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */

#include <Arduino.h>
#include "led.h"
#include "nfc.h"
#include "clavier.h"
#include "lcd.h"
#include "rtc.h"

// pre-enregistre deux tags de reference pour tester s'il sont dans le tableau
struct Tag tagVert = {{0x48, 0xA7, 0x4F, 0x03}};
struct Tag tagBleu = {{0x8A, 0x08, 0x18, 0x16}};

// cree le tableau pour stoker les tags
struct Tag tab[4] = {
    tagVert,
    tagBleu,
};

void setup()
{
  led_init();
  nfc_init();
  lcd_init();
  rtc_init();
}

void loop()
{
  test_badge(tab);
  interface();
}