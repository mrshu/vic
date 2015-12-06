CC=gcc -g -Wall
OFLAGS=-lm
OBJ=src/vic.o src/vic-serial.o src/vic-funcs.o src/vic-exec.o

DEST=/usr/lib
INCLDEST=/usr/include

%.o: %.c
	$(CC) -c -o $@ $< $(OFLAGS)

libvic.a: $(OBJ)
	ar rcs libvic.a $(OBJ)
	
example: example.c libvic.a
	$(CC) example.c -o example -L. -lvic -I./src/

shell: shell.c libvic.a
	$(CC) shell.c -o vic -L. -lvic -I./src/

arduino: $(OBJ)
	rm src/*.o
	cp src/* arduino/vic/src/
	cp src/vic.h arduino/vic/vic.h
	mkdir -p $(ARDUINODEST)
	cp -R arduino/vic/* $(ARDUINODEST)

install: libvic.a
	install libvic.a $(DEST)/libvic.a
	install src/vic.h $(INCLDEST)/vic.h

clean:
	rm -f src/*.o
	rm -f example
	rm -f libvic.a
