
CC=g++
CFLAGS=-I. `pkg-config --cflags --libs opencv`
INCL=*.h
OBJS=blur.o rgbsplit.o greyscale.o main.o

%.o: %.c $(INCL)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS)
	$(CC) -o main $^ $(CFLAGS)

.PHONY: clean

.PHONY: clean_lena

clean: 
	rm -f main *.o 

clean_lena:
	rm -f *_lena.png
