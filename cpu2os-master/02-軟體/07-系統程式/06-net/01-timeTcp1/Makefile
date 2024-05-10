CC := gcc
CFLAGS = -std=c99 -O0
TARGET = server client

all: $(TARGET)

server: servergpt.c
	$(CC) $(CFLAGS) $^ -o $@

client: clientgpt.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o *.exe $(TARGET)
