# GNU Makefile

CFLAGS=-g -Wall -Werror -Wextra

all:
	$(CC) $(CFLAGS) server.c -o server.out -pthread
	$(CC) $(CFLAGS) client.c -o client.out -pthread

clean:
	rm -f *.o *.out *.sock
