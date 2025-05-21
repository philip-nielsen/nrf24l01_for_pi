CC = gcc
CFLAGS = -Wall -I.. -DSPI_CHANNEL=1 #Use channel 1 for SPI
LDFLAGS = -lwiringPi

SRC = tx.c nrf24_gpio.c ../nrf24.c
OUT = tx

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

clean:
	rm -f $(OUT)
