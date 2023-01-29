#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
constexpr uint8_t DELAI = 100;
constexpr uint8_t D2_ACTIVE = 0x04;
constexpr uint8_t DELAI_VERT = 250;
constexpr uint8_t DELAI_ROUGE = 50;
constexpr uint8_t DELAI_ROUGE_AMBRE = 10;
constexpr uint8_t DELAI_VERT_AMBRE = 20;

volatile uint8_t gEtat = 0;

ISR(INT0_vect)
{
    _delay_ms(30);
    gEtat++;
    EIFR |= (1 << INTF0);
}

void initialisation(void)
{

    // cli est une routine qui bloque toutes les interruptions.
    cli();
    // configurer et choisir les ports pour les entrées
    // et les sorties. DDRx... Initialisez bien vos variables
    DDRA |= ((1 << DDA0) | (1 << DDA1));
    DDRD &= ~(1 << DDD2);
    PORTA &= (~(1 << PA0)) & (~(1 << PA1));
    // cette procédure ajuste le registre EIMSK
    // de l’ATmega324PA pour permettre les interruptions externes
    EIMSK |= (1 << INT0);
    // il faut sensibiliser les interruptions externes aux
    // changements de niveau du bouton-poussoir
    // en ajustant le registre EICRA
    EICRA |= (1 << ISC00);

    // sei permet de recevoir à nouveau des interruptions.

    sei();
}

bool estPresse()
{
    PIND &= ~(1 << PD2);
    if (PIND & D2_ACTIVE)
    {
        _delay_us(DELAI_ROUGE);
        return (PIND & D2_ACTIVE);
    }

    return false;
}

void afficherVert()
{
    PORTA |= 1 << PA0;
    _delay_ms(DELAI);
    PORTA &= ~(1 << PA0);
}

void afficherRouge()
{
    PORTA |= 1 << PA1;
    _delay_ms(DELAI);
    PORTA &= ~(1 << PA1);
}

void afficherAmbre()
{
    PORTA &= (~(1 << PA0)) | (~(1 << PA1));
    for (uint8_t i = 0; i < DELAI; i++)
    {

        PORTA |= 1 << PA0;

        for (uint8_t i = 0; i < DELAI_VERT_AMBRE; i++)
            _delay_us(DELAI_VERT);

        PORTA &= ~(1 << PA0);
        PORTA |= 1 << PA1;

        for (uint8_t i = 0; i < DELAI_ROUGE_AMBRE; i++)
            _delay_us(DELAI_ROUGE);
        PORTA &= ~(1 << PA1);
    }
}

void probleme2()
{
    switch (gEtat)
    {
    case 0:
        afficherRouge();
        break;

    case 1:
        afficherAmbre();
        break;
    case 2:
        afficherVert();
        break;

    case 3:
        afficherRouge();
        break;

    case 4:
        break;
    case 5:
        afficherVert();
        break;
    case 6:
        gEtat = 0;
        break;
    }
}

int main()
{
    while (true)
    {
        initialisation();
        probleme2();
    }

    return 0;
}