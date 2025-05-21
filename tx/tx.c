#include "../nrf24.h"
#include "../nrf24_gpio.h"
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <wiringPi.h>

#define CHANNEL 2
#define PAYLOAD_LEN 4
#define IRQ_PIN 24

volatile int tx_done = 0;

void irqHandler() {
  uint8_t reason = nrf24_irqReason();

  if (reason & (1 << TX_DS)) {
    tx_done = 1;
    printf("[TX] Transmission complete\n");
  } else if (reason & (1 << MAX_RT)) {
    tx_done = 1;
    printf("[TX] Max retransmit reached (FAIL)\n");
  }

  // Always clear the IRQ flags
  nrf24_configRegister(STATUS, (1 << RX_DR) | (1 << TX_DS) | (1 << MAX_RT));
}

int main() {
  uint8_t data_array[PAYLOAD_LEN];
  uint8_t q = 0;
  uint8_t temp;

  uint8_t tx_address[5] = {0xD7, 0xD7, 0xD7, 0xD7, 0xD7};
  uint8_t rx_address[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};

  wiringPiSetupGpio(); // use BCM GPIO numbers

  // Set IRQ pin as input with pull-up
  pinMode(IRQ_PIN, INPUT);
  pullUpDnControl(IRQ_PIN, PUD_UP);


  // Initialize and configure
  nrf24_init();
  usleep(10000); // let WiringPi settle

  wiringPiISR(IRQ_PIN, INT_EDGE_FALLING, &irqHandler);

  nrf24_config(CHANNEL, PAYLOAD_LEN);
  nrf24_tx_address(tx_address);
  nrf24_rx_address(rx_address); // Needed for ACK in Enhanced ShockBurst

  printf("nRF24L01+ TX (IRQ-based) Ready\n");

  while (1) {
    data_array[0] = 0x00;
    data_array[1] = 0xAA;
    data_array[2] = 0x55;
    data_array[3] = q++;

    tx_done = 0;

    // Send payload
    nrf24_send(data_array);

    // Wait for interrupt to trigger
    while (!tx_done) {
      delay(1);
    }

    temp = nrf24_lastMessageStatus();
    if (temp == NRF24_TRANSMISSON_OK) {
      printf("[TX] OK: %02X %02X %02X %02X\n", data_array[0], data_array[1],
             data_array[2], data_array[3]);
    } else if (temp == NRF24_MESSAGE_LOST) {
      printf("[TX] LOST\n");
    }

    temp = nrf24_retransmissionCount();
    printf("[TX] Retries: %d\n", temp);

    nrf24_powerUpRx(); // Optionally enter RX to catch responses
    usleep(100000);    // 100 ms pause
  }

  return 0;
}
