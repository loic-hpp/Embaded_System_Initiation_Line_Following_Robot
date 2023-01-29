/*
Refaire le programme avec string.h où 0x00 représente '\0'
le caractère nul, utiliser sting compare
strcmp
strcpy
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "memoire_24.h"
#include <avr/eeprom.h>
constexpr uint8_t DELAI = 100;

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
void ecrireMemoire(Memoire24CXXX memoire, char phrasePourMemoire[])
{
    for (int i = 0; i < sizeof(phrasePourMemoire) / sizeof(phrasePourMemoire[0]); i++)
    {
        int resultat = memoire.ecriture(0x0000 + i, (int)phrasePourMemoire[i]);
        _delay_ms(6);
    }
}

bool estSimilaire(Memoire24CXXX memoire, char phrase[])
{
    bool similarite = true;
    uint8_t* caractereMemoire ;
    for (int i = 0; i < sizeof(phrase) / sizeof(phrase[0]); i++)
    {
        int resultat = memoire.lecture(uint16_t(0x0000+i), caractereMemoire);
        if ((int)phrase[i] != *caractereMemoire)
            similarite = false;
        _delay_ms(6);
    }
    return similarite;
}

int main()
{
    DDRA |= 1<<DDA0;
    DDRA |= 1<<DDA1;
    Memoire24CXXX memoire;
    char MOTAECRIRE[] = "*P*O*L*Y*T*E*C*H*N*I*Q*U*E* *M*O*N*T*R*E*A*L*";
    ecrireMemoire(memoire, MOTAECRIRE);
    bool similarite = estSimilaire(memoire, MOTAECRIRE);
    if(similarite)
        afficherVert();
    else
        afficherRouge();
    return 0;
}
