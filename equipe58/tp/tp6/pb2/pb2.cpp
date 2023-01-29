/*
Rédigé le 17/10/2022 par:
- Loïc Nguemegne 2180845
- Jonathan Arrobas Gilbert 2120128

DESCRIPTION
Ce programme permet de convertir un signal analogique en signal numérique
La LED affichera la couleur:
- Verte pour une une flaible intensité lumineuse(moins de 85 en valeur numérique)
- Ambre à la lumière ambiante  (entre 86 et 250 en valeur numérique)
- Rouge pour une forte intensité lumineuse (plus de 250 en valeur numérique) 

MATÉRIEL UTILISÉ
- Résistance de 10K Ohm
- Photorésistance variant de 4k à 11k Ohm
- Breadboard
- Condensateur
- Les ports B0(Connecté à la borne négative) et B1(Connecté à la borne positive)
  pour allumer la LED
- Le port A0 pour obtenir le signal analogique(tension)
*/

#include <avr/io.h>
#define F_CPU 8000000
#include <util/delay.h>
#include <avr/interrupt.h>
#include "can.h"

constexpr uint8_t DELAI = 100;
constexpr uint16_t DELAI_ROUGE_AMBRE = 500;
constexpr uint8_t DELAI_VERT_AMBRE = 5;
constexpr uint8_t HIGH_THRESH = 250;
constexpr uint8_t LOW_THRESH = 85;
constexpr uint8_t ADC_POS = PA0;
constexpr uint8_t ADC_MASK = 2;

void initialisation()
{
    DDRB |= ((1 << DDB0) | (1 << DDB1));
    DDRA &= ~(1 << DDA0);
}

void eteindreLED()
{
    PORTB &= (~(1 << PB0)) & (~(1 << PB1));
}

void afficherVert()
{
    eteindreLED();
    PORTB |= 1 << PB0;
}

void afficherRouge()
{
    eteindreLED();
    PORTB |= 1 << PB1;
}

void afficherAmbre()
{
    for (uint8_t i = 0; i < DELAI; i++)
    {
        afficherVert();
        _delay_ms(DELAI_VERT_AMBRE);

        afficherRouge();
        _delay_us(DELAI_ROUGE_AMBRE);
    }
}

void conversionAnalogiqueNumerique()
{
    can convert;

    while (true)
    {
        uint8_t analogVal = (convert.lecture(ADC_POS) >> ADC_MASK);

        if (analogVal > HIGH_THRESH)
        {
            afficherRouge();
        }
        else if (analogVal < LOW_THRESH)
        {
            afficherVert();
        }
        else
        {
            afficherAmbre();
        }
    }
}

int main()
{
    initialisation();
    conversionAnalogiqueNumerique();
    return 0;
}
