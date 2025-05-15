#ifndef NRF24_GPIO_H
#define NRF24_GPIO_H

#include <stdint.h>

void nrf24_setupPins(void);
void nrf24_ce_digitalWrite(uint8_t state);
void nrf24_csn_digitalWrite(uint8_t state);

#endif
