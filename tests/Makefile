C=gcc -g -I../src 
C_LIBS=-L../ -lvic  

test-funcs: test-vic-funcs.c
	$(C) test-vic-funcs.c -o test-vic-funcs $(C_LIBS)
	./test-vic-funcs

test-serial: test-vic-serial.c
	$(C) test-vic-serial.c -o test-vic-serial $(C_LIBS)
	./test-vic-serial

test-var: test-vic-var.c
	$(C) test-vic-var.c -o test-vic-var $(C_LIBS)
	./test-vic-var

all-tests: test-serial test-funcs test-var
	@echo "All passed!"

clean:
	rm -f test-funcs
	rm -f test-serial
	rm -f test-var
	touch test-vic-var.c
	touch test-vic-serial.c
	touch test-vic-funcs.c
