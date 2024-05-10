CC = gcc
CFLAGS = -std=gnu99 # -Wall
TARGET = server client
all: $(TARGET)

server: servergpt.c net.c
	$(CC) $(CFLAGS) $^ -o $@

client: clientgpt.c net.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) *.exe
