# Raspberry Pi nRF24L01+ Communication with IRQ Support

This project provides a basic transmitter (TX) and receiver (RX) implementation for the nRF24L01+ wireless transceiver on Raspberry Pi using WiringPi. It uses IRQ interrupts to efficiently detect transmission and reception events without busy waiting.

---

## Features

- Transmitter and receiver examples with IRQ-based notification.
- Uses WiringPi for GPIO and SPI control.
- Configurable channel and payload size.
- Non-blocking interrupt-driven communication for better CPU efficiency.

---

## Inspiration

This project is heavily inspired by [kehribar/nrf24L01_plus](https://github.com/kehribar/nrf24L01_plus?tab=readme-ov-file) by Ihsan Kehribar. His work laid the foundation for handling the nRF24L01+ on embedded Linux platforms and guided the adaptation for Raspberry Pi IRQ handling.


## Requirements

- Raspberry Pi with WiringPi installed.
- nRF24L01+ module connected to SPI and GPIO pins.
- GCC or compatible C compiler.

---

## License

This project follows the “THE COFFEEWARE LICENSE” (Revision 1). Keep the notice and buy a coffee for Ihsan if you find it useful.
