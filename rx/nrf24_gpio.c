#include "../nrf24_gpio.h"
#include <wiringPi.h>

// Define wiringPi GPIO numbers
#define CE_PIN   17
#define CSN_PIN  8
#define SCK_PIN  11
#define MOSI_PIN 10
#define MISO_PIN 9
#define IRQ_PIN 23 

void nrf24_setupPins()
{
    wiringPiSetupGpio(); // BCM GPIO numbers

    pinMode(CE_PIN, OUTPUT);
    pinMode(CSN_PIN, OUTPUT);
    pinMode(SCK_PIN, OUTPUT);
    pinMode(MOSI_PIN, OUTPUT);
    pinMode(MISO_PIN, INPUT);
    pinMode(IRQ_PIN, INPUT);

    pullUpDnControl(IRQ_PIN, PUD_UP); // nRF24 IRQ is active LOW
                                    // Setup interrupt on falling edge
}

void nrf24_ce_digitalWrite(uint8_t state)
{
    digitalWrite(CE_PIN, state);
}

void nrf24_csn_digitalWrite(uint8_t state)
{
    digitalWrite(CSN_PIN, state);
}
