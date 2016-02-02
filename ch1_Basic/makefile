CC=clang++
CFLAGS=-Wall -g -O3 
LINKERFLAGS = -lz 
INCLUDE=-I. -I
VPATH=.:

OBJS=main.o
OUTPUT=main

main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LINKERFLAGS)
clean:
	rm -f $(OUTPUT) *.o *.so

