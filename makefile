CC  = gcc
OUT = char
SRC = $(wildcard src/*.c)

all: build

build:
	$(CC) main.c $(SRC) -Wall -O2 -o $(OUT)