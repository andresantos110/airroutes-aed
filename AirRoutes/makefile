OBJS	= main.o List.o modes.o Fileio.o heap.o
SOURCE	= main.c List.c modes.c Fileio.c heap.c
HEADER	= AirRoutes.h List.h modes.h Fileio.h heap.h
OUT	= backbone
CC	 = gcc
FLAGS	 = -Wall -O3 -std=c99 -c

all: $(OBJS)
	$(CC) -O3 $(OBJS) -o $(OUT)

main.o: main.c
	$(CC) $(FLAGS) main.c 

List.o: List.c
	$(CC) $(FLAGS) List.c 

modes.o: modes.c
	$(CC) $(FLAGS) modes.c

Fileio.o: Fileio.c
	$(CC) $(FLAGS) Fileio.c

heap.o: heap.c
	$(CC) $(FLAGS) heap.c

clean:
	rm -f $(OBJS) $(OUT)
