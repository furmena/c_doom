doom: bin
	gcc src/doom.c -o bin/doom

bin: doom.c
	mkdir bin
