/*
Rédigé le 17/10/2022 par:
- Loïc Nguemegne 2180845
- Jonathan Arrobas Gilbert 2120128

DESCRIPTION
Ce code permet d'implémenter le comportement d'une machine à 2 états: INITIAL
et APPUI_SANS_RELACHER
Lorsqu'on appuie et relache, on fait clignoter la Led au vert pendant une demie
seconde ensuite elle clignote compteur/2 fois au rouge et enfin elle affiche
la couleur verte une seconde 

MATÉRIEL UTILISÉ
- Résistance de 100K Ohm
- Interrupteur
- Breadboard
- Condensateur
- Minuterie1
- Les ports A0 et A1 pour allumer la LED
- Le bouton D2 pour détecter les pressions sur le bouton poussoir

+---------------------+------------------+---------------------+--------------------------------------------------+
|    État présent     | Bouton D2 appuyé |     État future     |                       Led                        |
+---------------------+------------------+---------------------+--------------------------------------------------+
| INITIAL             | non              | INITIAL             | éteinte                                          |
| INITIAL             | oui              | APPUI_SANS_RELACHER | éteinte                                          |
| APPUI_SANS_RELACHER | non              | INITIAL             | clignote vert ensuite rouge affiche vert ensuite |
| APPUI_SANS_RELACHER | oui              | APPUI_SANS_RELACHER | éteinte                                          |
+---------------------+------------------+---------------------+--------------------------------------------------+
*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
const uint16_t DUREE = 781;
const uint16_t DELAI_INACTIVITE = 2000;
const uint16_t TEMPS_AFFICHAGE_VERT = 1000;
const uint16_t TEMPS_CLIGNOTEMENT_ROUGE = 250;
const int8_t TEMPS_CLIGNOTEMENT = 50;
const uint8_t NFOIS = 5;
const uint8_t NFOIS_ROUGE = 1;
const uint8_t D2_INACTIVE = 0x04;
const uint8_t DIVISION = 2;
const uint8_t DELAI_REBOND = 50;
const uint8_t MATCH_DECOMPTE = 120;
volatile uint8_t gCompteur = 0;

ISR(TIMER1_COMPA_vect)
{
    OCR1A = DUREE;
    gCompteur++;
}
enum Couleur
{
    ROUGE,
    VERT
};
enum Etat
{
    INITIAL,
    APPUI_SANS_RELACHER
};

bool estPresse()
{
    if (!(PIND & D2_INACTIVE))
    {
        _delay_us(DELAI_REBOND);
        return !(PIND & D2_INACTIVE);
    }

    return false;
}

inline void clignoterCouleur(Couleur couleur, uint8_t nFois, uint16_t temps)
{
    for (uint8_t i = 0; i < nFois; i++)
    {
        PORTA |= 1 << couleur;
        _delay_ms(temps);
        PORTA &= ~(1 << couleur);
        _delay_ms(temps);
    }
}

inline void afficherCouleur(Couleur couleur, uint16_t temps)
{
    PORTA |= 1 << couleur;
    _delay_ms(temps);
    PORTA &= ~(1 << couleur);
}

void affichage()
{
    clignoterCouleur(Couleur::VERT, NFOIS, TEMPS_CLIGNOTEMENT);
    _delay_ms(DELAI_INACTIVITE);
    gCompteur /= DIVISION;
    while (gCompteur > 0)
    {
        clignoterCouleur(Couleur::ROUGE, NFOIS_ROUGE, TEMPS_CLIGNOTEMENT_ROUGE);
        gCompteur--;
    }
    afficherCouleur(Couleur::VERT, TEMPS_AFFICHAGE_VERT);
}

void partirMinuterie(uint16_t duree)
{
    TCNT1 = 0;
    OCR1A = duree;
    TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0);
    TCCR1B = (1 << WGM12) | (1 << CS12) | (1 << CS10);
    TCCR1C = 0;
    TIMSK1 = (1 << OCIE1A);
}

void tantQueBoutonPresseCompter()
{
    while (estPresse())
    {
        if (gCompteur == MATCH_DECOMPTE)
            break;
    }
    cli();
}

void allumerLedAvecBoutonPoussoir()
{
    Etat etat = Etat::INITIAL;
    while (true)
    {
        switch (etat)
        {
        case Etat::INITIAL:
            sei();
            gCompteur = 0;
            if (estPresse())
                etat = Etat::APPUI_SANS_RELACHER;
            break;
        case Etat::APPUI_SANS_RELACHER:
            partirMinuterie(DUREE);
            tantQueBoutonPresseCompter();
            affichage();
            etat = Etat::INITIAL;
            break;
        }
    }
}

void initialisationPorts()
{
    DDRD &= ~(1 << DDD2);
    DDRA |= ((1 << DDA0) | (1 << DDA1));
}

int main()
{
    initialisationPorts();
    allumerLedAvecBoutonPoussoir();
    return 0;
}