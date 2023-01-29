#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
const uint16_t DUREE = 1;

volatile uint8_t gMinuterieExpiree = 0;
volatile uint8_t gBoutonPoussoir = 0;

ISR(TIMER1_COMPA_vect)
{ 
    gMinuterieExpiree = 1;
}

ISR(INT0_vect)
{
    _delay_ms(30);
    gBoutonPoussoir = 1;
}

void initialisation(void)
{
    cli();
    EIMSK |= (1 << INT0);
    EICRA |= (1 << ISC00);
    sei();
}

void partirMinuterie(uint16_t duree)
{
    gMinuterieExpiree = 0;
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A |= 0b11110000;
    TCCR1B |= 0b00001101;
    TCCR1C = 0;
    TIMSK1 = 0x02;
}

int main()
{
    sei();
    DDRA |= ((1 << DDA0) | (1 << DDA1));
    DDRD &= ~(1 << DDD2);
    PORTA &= (~(1 << PA0)) & (~(1 << PA1));
    //_delay_ms(10000);
    partirMinuterie(7812);
    initialisation();
    for (uint8_t i = 0; i < 10; i++)
    {
        PORTA |= 1 << PA1;
        _delay_ms(10);
        PORTA &= ~(1 << PA1);
    }
    do
    {

    } while (gMinuterieExpiree == 0 && gBoutonPoussoir == 0);
    cli();
    if (gMinuterieExpiree == 1)
        PORTA |= 2;
    if (gBoutonPoussoir == 1)
        PORTA |= 1;

    // Verifier la réponse

    //'modifier ici'

    return 0;
}