CC = gcc
CFLAGS = -std=gnu99 # -Wall
TARGET = server client
all: $(TARGET)

server: server.c net.c
	$(CC) $(CFLAGS) $^ -o $@

client: client.c net.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) *.exe
