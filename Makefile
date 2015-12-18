CC=gcc -g -Wall
OFLAGS=-lm
OBJ=src/vic.o src/vic-serial.o src/vic-funcs.o src/vic-exec.o

DEST=/usr/lib
INCLDEST=/usr/include

%.o: %.c
	$(CC) -c -o $@ $< $(OFLAGS)

libvic.a: $(OBJ)
	ar rcs libvic.a $(OBJ)
	
shell: shell/shell.c libvic.a
	$(CC) shell/shell.c -o vic -L. -lvic -I./src/

install: libvic.a
	install libvic.a $(DEST)/libvic.a
	install src/vic.h $(INCLDEST)/vic.h

clean:
	rm -f src/*.o
	rm -f example
	rm -f libvic.a
