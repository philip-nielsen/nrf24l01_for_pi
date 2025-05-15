#include "../nrf24_gpio.h"
#include <wiringPi.h>

// Define wiringPi GPIO numbers
#define CE_PIN   27
#define CSN_PIN  18
#define SCK_PIN 21
#define MOSI_PIN 20
#define MISO_PIN 19
#define IRQ_PIN 24 

void nrf24_setupPins()
{
    wiringPiSetupGpio(); // BCM GPIO numbers

    pinMode(CE_PIN, OUTPUT);
    pinMode(CSN_PIN, OUTPUT);
    pinMode(SCK_PIN, OUTPUT);
    pinMode(MOSI_PIN, OUTPUT);
    pinMode(MISO_PIN, INPUT);
    pinMode(IRQ_PIN, INPUT);

    pullUpDnControl(IRQ_PIN, PUD_UP); // IRQ is active-low
}

void nrf24_ce_digitalWrite(uint8_t state)
{
    digitalWrite(CE_PIN, state);
}

void nrf24_csn_digitalWrite(uint8_t state)
{
    digitalWrite(CSN_PIN, state);
}
