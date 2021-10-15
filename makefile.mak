game: 
	gcc main.c -o blocksOfLife.exe -O1 -Wall -std=c99 -Wno-missing-braces -I include/ -L lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

clean:
	-del -fR blocksOfLife.exe