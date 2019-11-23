

CC=gcc

CFLAGS=-Wall -g
LFLAGS=-L/usr/lib -lm -lGL -lglut

EXEC=plot
SRCS=$(wildcard source/*.c main.c)
OBJS=$(SRCS:.c=.o)

$(EXEC) : $(OBJS)
	$(CC) $^ -o $@ $(LFLAGS)

%.o :source/%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

clean :
	/bin/rm $(EXEC) source/*.o main.o
