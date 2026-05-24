CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC_DIR = src
SRCS = *.c

# Ubah jadi file .exe
TARGET = hitung_pengeluaran.exe

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)
