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
  tx_done = 1;
  printf("[TX] IRQ triggered\n");
}

int main() {
  uint8_t data_array[PAYLOAD_LEN];
  uint8_t q = 0;
  uint8_t temp;

  uint8_t tx_address[5] = {0xD7, 0xD7, 0xD7, 0xD7, 0xD7};
  uint8_t rx_address[5] = {0xE7, 0xE7, 0xE7, 0xE7, 0xE7};

  nrf24_init();
  usleep(10000); // let wiringPi settle

  // IRQ setup
  wiringPiISR(IRQ_PIN, INT_EDGE_FALLING, &irqHandler);

  nrf24_config(CHANNEL, PAYLOAD_LEN);
  nrf24_tx_address(tx_address);
  nrf24_rx_address(rx_address);
  nrf24_ce_digitalWrite(1);

  printf("nRF24L01+ TX w/ IRQ Ready\n");

  while (1) {
    data_array[0] = 0x00;
    data_array[1] = 0xAA;
    data_array[2] = 0x55;
    data_array[3] = q++;

    tx_done = 0;
    nrf24_send(data_array);

    while (!tx_done) {
      delay(1);
    }

    printf("done\n");

    temp = nrf24_lastMessageStatus();
    if (temp == NRF24_TRANSMISSON_OK) {
      printf("[IRQ TX] OK: %02X %02X %02X %02X\n", data_array[0], data_array[1],
             data_array[2], data_array[3]);
    } else if (temp == NRF24_MESSAGE_LOST) {
      printf("[IRQ TX] LOST\n");
    }

    temp = nrf24_retransmissionCount();
    printf("[IRQ TX] Retries: %d\n", temp);

    nrf24_powerUpRx();
    usleep(100000); // 100 ms delay
  }

  return 0;
}
