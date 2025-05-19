CC = gcc
CFLAGS = -Wall -I.. 
LDFLAGS = -lwiringPi

SRC = tx.c nrf24_gpio.c ../nrf24.c
OUT = tx

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CFLAGS) -o $(OUT) $(SRC) $(LDFLAGS)

clean:
	rm -f $(OUT)
