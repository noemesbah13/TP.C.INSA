#include "led.h"

#define LED_BLEUE 15
#define LED_ROUGE 17
#define LED_VERTE 16

/*initialise les LED rouge et verte en LOW*/
void led_init(){
    pinMode(LED_BLEUE, OUTPUT);
    pinMode(LED_ROUGE, OUTPUT);
    pinMode(LED_VERTE, OUTPUT);
    digitalWrite(LED_ROUGE, LOW);   
    digitalWrite(LED_VERTE, LOW);
    digitalWrite(LED_BLEUE, LOW);
    
}

// allume la Led de la courleur demandee
void led_set_color(LedColor color) 
{
    digitalWrite(LED_BLEUE, (color & ColorBlue)?HIGH:LOW);
    digitalWrite(LED_VERTE, (color & ColorGreen)?HIGH:LOW);
    digitalWrite(LED_ROUGE, (color & ColorRed)?HIGH:LOW);
}
