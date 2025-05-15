#include "../nrf24.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

#define IRQ_PIN 23 

volatile uint8_t messageAvailable = 0;

void irqHandler() {
  messageAvailable = 1;
  printf("[RX] IRQ triggered\n");
}

int main() {
  uint8_t data[32];

  uint8_t tx_address[5] = {0xD7, 0xD7, 0xD7, 0xD7, 0xD7};
  uint8_t rx_address[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};

  nrf24_init();
  usleep(10000);

  wiringPiISR(IRQ_PIN, INT_EDGE_FALLING, &irqHandler);

  nrf24_config(2, 4);
  nrf24_tx_address(tx_address);
  nrf24_rx_address(rx_address);
  nrf24_ce_digitalWrite(1); // Start listening

  printf("nRF24L01+ RX w/ IRQ Ready\n");

  while (1) {
    usleep(10);

    if (messageAvailable) {
      messageAvailable = 0;

      if (nrf24_dataReady()) {
        nrf24_getData(data);
        printf("Received: %02X %02X %02X %02X\n", data[0], data[1], data[2],
               data[3]);
      }
    }
  }

  return 0;
}
