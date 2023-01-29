#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
constexpr uint8_t GREEN = 0X01;
constexpr uint8_t RED = 0X02;
constexpr int DURATION = 3000;
constexpr int PERIOD_DURATION = 10;
constexpr int DELAY = 100;

void pwm(uint8_t color, int pin)
{
    for (int i = 1; i <= DURATION; i++) // changer pour uint8
    {
        PORTA |= color;
        for (int j = 0; j < PERIOD_DURATION - i / (DURATION / PERIOD_DURATION); j++)
            _delay_us(DELAY);
        PORTA &= ~(1 << pin);
        for (int j = 0; j < i / (DURATION / PERIOD_DURATION); j++)
            _delay_us(DELAY);
    }
}

int main()
{
    DDRA |= ((1 << DDA0) | (1 << DDA1));
    PORTA &= (~(1 << PA0)) | (~(1 << PA1));
    pwm(RED, PA1);
    _delay_ms(DELAY);
    pwm(GREEN, PA0);
}