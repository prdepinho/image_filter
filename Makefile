
CC=g++
CFLAGS=-I. `pkg-config --cflags --libs opencv`
INCL=filter.h global_filters.h blur.h blur_view.h rgbsplit.h rgbsplit_view.h greyscale.h
OBJS=blur.o blur_view.o rgbsplit.o rgbsplit_view.o greyscale.o main.o

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
