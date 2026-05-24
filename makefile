CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Ubah jadi file .exe
TARGET = hitung_pengeluaran.exe
