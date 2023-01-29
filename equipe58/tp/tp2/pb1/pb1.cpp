/*
Rédigé le 10/09/2022 par:
- Loïc Nguemegne 2180845
- Jonathan Arrobas Gilbert 2120128

DESCRIPTION
Ce code permet d'implémenter le comportement d'une machine à 4 états: etat_initial, appui1, appui2, appui3
Dans le but d'allumer la led verte après avoir appuyé et relaché 3 fois l'interrupteur

MATÉRIEL UTILISÉ
Pour la réalisation du programme, nous avons utilisé l'interrupteur relié à la pin D2 de la carte ainsi que
les ports A0 et A1 et un cable d'alimentation pour relier le led à notre carte

+--------------+-----------------------------+--------------+--------------+
| État présent | Bouton D2 appuyé et relaché | État future  |     Led      |
+--------------+-----------------------------+--------------+--------------+
| etat_initial | non                         | etat_initial | éteinte      |
| etat_initial | oui                         | appui1       | éteinte      |
| appui1       | non                         | appui1       | éteinte      |
| appui1       | oui                         | appui2       | éteinte      |
| appui2       | non                         | appui2       | éteinte      |
| appui2       | oui                         | appui3       | éteinte      |
| appui3       | X                           | etat_initial | allumé_verte |
+--------------+-----------------------------+--------------+--------------+


*/
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
constexpr uint8_t DELAI = 40;
constexpr uint8_t D2_ACTIVE = 0x04;
constexpr uint8_t DELAI_REBOND = 50;
enum class Etat
{
    etat_initial,
    appui1,
    appui2,
    appui3
};
Etat etat_future = Etat::etat_initial;

bool estPresse()
{
    PIND &= ~(1 << PD2);
    if (PIND & D2_ACTIVE)
    {
        _delay_us(DELAI_REBOND);
        return (PIND & D2_ACTIVE);
    }

    return false;
}

void afficherVert()
{
    PORTA |= 1 << PA0;
    for (uint8_t i = 0; i < DELAI_REBOND; i++)
        _delay_ms(DELAI);
    PORTA &= ~(1 << PA0);
}

void probleme1()
{
    switch (etat_future)
    {
    case Etat::etat_initial:
        if (estPresse())
        {
            while (PIND & D2_ACTIVE)
            {
                /* on ne fait rien on attent juste que le bouton soit relaché*/
            }
            etat_future = Etat::appui1;
        }
        else
            etat_future = Etat::etat_initial;

        break;
    case Etat::appui1:
        if (estPresse())
        {
            while (PIND & D2_ACTIVE)
            {
                /* on ne fait rien on attent juste que le bouton soit relaché*/
            }
            etat_future = Etat::appui2;
        }
        else
            etat_future = Etat::appui1;

        break;
    case Etat::appui2:
        if (estPresse())
        {
            while (PIND & D2_ACTIVE)
            {
                /* on ne fait rien on attent juste que le bouton soit relaché*/
            }
            etat_future = Etat::appui3;
        }
        else
            etat_future = Etat::appui2;

        break;
    case Etat::appui3:
        afficherVert();
        etat_future = Etat::etat_initial;
        break;
    }
}

int main()
{

    DDRA |= ((1 << DDA0) | (1 << DDA1));
    DDRD &= ~(1 << DDD2);
    PORTA &= (~(1 << PA0)) | (~(1 << PA1));
    while (true)
    {
        probleme1();
    }

    return 0;
}
