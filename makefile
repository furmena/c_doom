doom: bin
	gcc src/doom.c -o bin/doom.o -I/usr/include/SDL2 -D_REENTRANT -lSDL2 -lm

bin: src/doom.c
	rm -d -r bin
	mkdir bin
