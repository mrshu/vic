
CC=gcc -g -Wall 

OBJ= src/vic-serial.o src/vic-funcs.o src/vic.o src/vic-tasks.o src/vic-var.o 
OBJC=vic-serial.c vic-funcs.c vic-tasks.c vic-var.c vic.c

ARDUINODEST=~/sketchbook/libraries/vic/
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
	rm src/*.o
	rm example
	rm libvic.a
