#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
const int8_t ZERO = 255;
const int8_t VINGT_CINQ = 192;
const int8_t CINQUANTE = 128;
const int8_t SOIXANTE_QUINZE = 64;
const int8_t CENT = 0;

//TODO: COMPTEUR TCR02 EN SORTIE SUR C0 ET C1
void ajustementPwmTimer2(int maxCompteur)
{
    OCR2A = 255; // D7
    OCR2B = 0;   // D6
    TCCR2A |= (1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) | (1 << COM2B0) | (1 << WGM20);
    TCCR2B |= 1<< CS01;
    //TCCR2A = 11110001;
    //TCCR2B = 1;
    TCNT2 = 0;
}

//TODO: AVEC LE COMPTEUR TCR01 EN SORTIE SUR D4 ET D5
void ajustementPwm(int ratio){
    OCR1A = ratio;
    OCR1B = ratio;
    TCCR1A |= (1 << COM2A1) | (1 << COM2A0) | (1 << COM2B1) | (1 << COM2B0) | (1 << WGM20);//CHANGEMENT AU HIGH
    //TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM10);  // CHANGEMENT AU LOW
    TCCR1B |= 1<< CS11;
    TCCR1C = 0;
    TCNT1 = 0;
}
void setOCR(int ratio){
    OCR1A = ratio;
    OCR1B = ratio;
}

int main()
{
    DDRD |= (1 << DD4) | (1 << DD5);
    ajustementPwm(CENT);
  _delay_ms(2000);
  setOCR(SOIXANTE_QUINZE);
  _delay_ms(2000);
  setOCR(CINQUANTE);
  _delay_ms(2000);
  setOCR(VINGT_CINQ);
  _delay_ms(2000);
  setOCR(ZERO);
  _delay_ms(2000);
    while (true)
    {
          

    }
    return 0;
}