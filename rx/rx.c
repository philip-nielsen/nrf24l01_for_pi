#include "../nrf24.h"
#include "../nrf24_gpio.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wiringPi.h>

#define IRQ_PIN 23          
#define CHANNEL 2
#define PAYLOAD_LEN 4

volatile uint8_t messageAvailable = 0;

void irqHandler() {
  messageAvailable = 1;
  printf("[RX] IRQ triggered\n");
}

int main() {
  uint8_t data[PAYLOAD_LEN];

  // This RX receives on address 0xE7... from TX 0xD7...
  uint8_t tx_address[5] = {0xD7, 0xD7, 0xD7, 0xD7, 0xD7}; // Set for ACK
  uint8_t rx_address[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};

  // Set GPIO mode
  wiringPiSetupGpio();

  // IRQ setup
  pinMode(IRQ_PIN, INPUT);
  pullUpDnControl(IRQ_PIN, PUD_UP);
  wiringPiISR(IRQ_PIN, INT_EDGE_FALLING, &irqHandler);

  // Init nRF24 and configure
  nrf24_init();
  usleep(10000); // let it settle

  nrf24_config(CHANNEL, PAYLOAD_LEN);
  nrf24_tx_address(tx_address);   // Needed for Enhanced ShockBurst ACK
  nrf24_rx_address(rx_address);
  nrf24_ce_digitalWrite(1);       // Start listening

  printf("nRF24L01+ RX (IRQ-based)");

  while (1) {
    delayMicroseconds(100); // non-blocking

    if (messageAvailable) {
      messageAvailable = 0;

      if (nrf24_dataReady()) {
        nrf24_getData(data);
        printf("[RX] Received: %02X %02X %02X %02X\n",
               data[0], data[1], data[2], data[3]);
      }
    }
  }

  return 0;
}
