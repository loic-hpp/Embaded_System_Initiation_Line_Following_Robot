/*
Rédigé le 10/09/2022 par:
- Loïc Nguemegne 2180845
- Jonathan Arrobas Gilbert 2120128

DESCRIPTION
Ce code permet d'implémenter le comportement d'une machine à 6 états: INIT, APPUI_1,
RELACHE_1,APPUI_2, RELACHE_2, APPUI_3
Dans le but de changer la couleur de la led après avoir appuyé ou relaché le bouton

MATÉRIEL UTILISÉ
Pour la réalisation du programme, nous avons utilisé l'interrupteur relié à la pin D2 de la carte ainsi que
les ports A0 et A1 et un cable d'alimentation pour relier le led à notre carte

+--------------+------------------+--------------+---------+
| État présent | Bouton D2 appuyé | État future  |   Led   |
+--------------+------------------+--------------+---------+
| etat_initial | non              | etat_initial | rouge   |
| etat_initial | oui              | appui_1      | ambre   |
| appui_1      | non              | relache_1    | verte   |
| appui_1      | oui              | appui_1      | ambre   |
| relache_1    | non              | relache_1    | verte   |
| relache_1    | oui              | appui_2      | rouge   |
| appui_2      | non              | relache_2    | éteinte |
| appui_2      | oui              | appui_2      | rouge   |
| relache_2    | non              | relache_2    | éteinte |
| relache_2    | oui              | appui_3      | verte   |
| appui_3      | non              | etat_initial | rouge   |
| appui_3      | oui              | appui_3      | verte   |
+--------------+------------------+--------------+---------+



*/

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>

constexpr uint8_t DELAI = 100;
constexpr uint8_t D2_ACTIVE = 0x04;
constexpr uint8_t DELAI_VERT = 250;
constexpr uint8_t DELAI_ROUGE = 50;
constexpr uint8_t DELAI_ROUGE_AMBRE = 10;
constexpr uint8_t DELAI_VERT_AMBRE = 20;

enum Etat
{
    INIT,
    APPUI_1,
    RELACHE_1,
    APPUI_2,
    RELACHE_2,
    APPUI_3
};


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
    Etat etatFutur;
    etatFutur = INIT;

    switch (etatFutur) 
    {
        case INIT : 
            while (!estPresse()) 
            {   
                afficherRouge();  
            }

            if (estPresse()) 
            {
                etatFutur = APPUI_1;
            }
        case APPUI_1 :
            while (estPresse()) 
            {
                afficherAmbre();   
            }

            if (!estPresse()) 
            {
                etatFutur = RELACHE_1;
            }  
        case RELACHE_1 :
            while (!estPresse()) 
            {
                afficherVert();
            }

            if (estPresse()) 
            {
                etatFutur = APPUI_2;
            }
  
        case APPUI_2 :
            while (estPresse()) 
            {
                afficherRouge();
            }

            if (!estPresse()) 
            {
                etatFutur = RELACHE_2;
            }  
        case RELACHE_2 :
            while (!estPresse()) 
            {  
                // Boucle vide puisque la LED est éteinte 
            }
            if (estPresse()) 
            {
                etatFutur = APPUI_3;
            }  
        case APPUI_3 :
            while (estPresse()) 
            {
                afficherVert();
            }

            if (!estPresse()) 
            {
                etatFutur = INIT;
            }
    }   
}

int main()
{
    DDRA |= ((1 << DDA0) | (1 << DDA1));
    DDRD &= ~(1 << DDD2);
    PORTA &= (~(1 << PA0)) | (~(1 << PA1));
    while (true)
    {
        probleme2();
    }

    return 0;
}
