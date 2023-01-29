#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"

void initialisationUART(void)
{
    UBRR0H = 0;
    UBRR0L = 0xCF;
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void transmissionUART(uint8_t donnee)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    UDR0 = donnee;
}

void ecrireMemoire(Memoire24CXXX memoire, char phrasePourMemoire[])
{
    for (int i = 0; i < sizeof(phrasePourMemoire) / sizeof(phrasePourMemoire[0]); i++)
    {
        int resultat = memoire.ecriture(0x0000 + i, (int)phrasePourMemoire[i]);
        _delay_ms(6);
    }
}

void lecturememoire(Memoire24CXXX memoire){
    uint8_t* valeurLue;
    for(int i=0; i<256; i++){
        int resultat = memoire.lecture(uint16_t(0x0000+i), valeurLue);
        _delay_ms(6);
    }
}

int main()
{
    Memoire24CXXX memoire;
    int resultat = 0;
    initialisationUART();
    char mots[21] = "Le robot en INF1900\n";
    uint8_t i, j;
    for (i = 0; i < 20; i++)
    {
        for (j = 0; j < 21; j++){
            resultat = memoire.ecriture(0x0000 + j + i*(uint8_t)21, (uint8_t)mots[j]);
            _delay_ms(6);
            }
    }
    uint8_t* valeurLue;
    for(int i=0; i<256; i++){
        resultat = memoire.lecture(uint16_t(0x0000+(uint16_t)i), valeurLue);
        _delay_ms(6);
        transmissionUART(*valeurLue);
        //transmissionUART('\t');   
    }


    return 0;
}