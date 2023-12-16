doom: bin
	gcc src/doom.c -o bin/doom.o

bin: doom.c
	mkdir bin
