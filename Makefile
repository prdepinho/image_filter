
CC=g++
CFLAGS=-I. `pkg-config --cflags --libs opencv`
INCL=filter.h filter_view.h global_filters.h filter_exception.h blur.h blur_view.h rgbsplit.h rgbsplit_view.h
OBJS=blur.o blur_view.o rgbsplit.o rgbsplit_view.o main.o

%.o: %.c $(INCL)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS)
	$(CC) -o main $^ $(CFLAGS)

.PHONY: clean

.PHONY: clean_lena

clean: 
	rm -f main *.o 

clean_lena:
	rm -f blue_lena.png green_lena.png red_lena.png blurred_lena.png
