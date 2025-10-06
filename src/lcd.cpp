#include "lcd.h"
#include <stdio.h>
#include <LiquidCrystal.h>
// Constantes des dimensions de l'écran
#define COLUMN_COUNT 16
#define ROWN_COUNT 2
#include "rtc.h"

LiquidCrystal liquidcrystal(8, 9, 4, 5, 6, 7);
static char buffer[COLUMN_COUNT +1];

void lcd_init()
{
    // set up the LCD's number of columns and rows:
    liquidcrystal.begin(COLUMN_COUNT, ROWN_COUNT);
    liquidcrystal.clear();
}

void lcd_print_internal(const char * text)
{
    memset(buffer, ' ', sizeof(buffer));
    size_t length = strlen(text);
    if(length > COLUMN_COUNT)
    {
        length = COLUMN_COUNT;
    }
    strncpy(buffer, text, length);
    liquidcrystal.print(buffer);
}

void lcd_print(unsigned char row, const char * text)
{
    liquidcrystal.setCursor(0,row);
    lcd_print_internal(text);
}

void afficherTime()
{
    DateTime now = rtc_get_current_time();
    sprintf(buffer, "%02i/%02i/%04i", now.day(), now.month(), now.year());
    lcd_print(0,buffer);
    sprintf(buffer, "%02i:%02i:%02i", now.hour(), now.minute(), now.second());
    lcd_print(1,buffer);
}