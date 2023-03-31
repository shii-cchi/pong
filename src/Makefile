CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
SOURCES = pong.c

all: clean 
	$(CC) $(CFLAGS) -o pong $(SOURCES)

play: all
	./pong

clean:
	-rm -rf pong