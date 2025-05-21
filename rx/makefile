CC = gcc
CFLAGS = -Wall -I.. -DSPI_CHANNEL=0
LDFLAGS = -lwiringPi

SRC = rx.c nrf24_gpio.c ../nrf24.c
OUT = rx

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

clean:
	rm -f $(OUT)
