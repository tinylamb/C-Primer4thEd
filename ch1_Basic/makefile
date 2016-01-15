CC=clang++
CFLAGS=-Wall -g -O3 
LINKERFLAGS = -lz 
#-stdlib=libc++
INCLUDE=-I. -I
#-I/usr/local/include
VPATH=.:
OBJS=main.o
OUTPUT=main

main: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LINKERFLAGS)
clean:
	rm -f $(OUTPUT) *.o *.so

