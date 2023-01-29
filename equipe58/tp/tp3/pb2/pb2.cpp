#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
constexpr uint8_t GREEN = 0X01;
constexpr uint8_t RED = 0X02;
constexpr int FREQUENCY_DURATION = 1000;
constexpr int INTERVAL_DURATION = 2000;
constexpr int NUMBER_OF_INTERVAL = 5;

void pwm(uint8_t color, int pin, int frequency)
{
    for (int k = 0; k < NUMBER_OF_INTERVAL; k++)
    {
        for (int i = 1; i <= (INTERVAL_DURATION / FREQUENCY_DURATION) * frequency; i++) // changer pour uint8
        {
            PORTA |= color;
            for (int j = 0; j < (NUMBER_OF_INTERVAL - 1) * k; j++)
                _delay_ms(1);
            PORTA &= ~(1 << pin);
            for (int j = 0; j < (FREQUENCY_DURATION / frequency) - (NUMBER_OF_INTERVAL - 1) * k; j++)
                _delay_ms(1);
        }
    }
}

void pwm2(uint8_t color, int pin, int frequency)
{
    for (int k = 0; k < NUMBER_OF_INTERVAL; k++)
    {
        for (int i = 1; i <= (INTERVAL_DURATION / FREQUENCY_DURATION) * frequency; i++) // changer pour uint8
        {
            PORTA |= color;
            for (int j = 0; j < (NUMBER_OF_INTERVAL)*k; j++)
                _delay_us(100);
            PORTA &= ~(1 << pin);
            for (int j = 0; j < (FREQUENCY_DURATION / frequency) * 10 - (NUMBER_OF_INTERVAL)*k; j++)
                _delay_us(100);
        }
    }
}

int main()
{
    DDRA |= ((1 << DDA0) | (1 << DDA1));
    PORTA &= (~(1 << PA0)) | (~(1 << PA1));
    pwm(GREEN, PA0, 60);
    pwm2(GREEN, PA0, 400);
}