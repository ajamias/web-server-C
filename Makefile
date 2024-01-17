CC := gcc
CFLAGS := -std=c17 -Wall -Wextra -Werror

.PHONY: all

all: server.c
	$(CC) $< -o server

clean:
	rn server
