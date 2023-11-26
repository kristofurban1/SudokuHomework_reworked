all:
	./bin/sudoku.exe


Debug: compile
Release: compile

cleanRelease: Clean
cleanDebug: Clean


Clean:
	del .\bin\sudoku.exe

compile:
	gcc -g -Iinclude -Llib -o bin/sudoku src/*.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -Wall -Werror
