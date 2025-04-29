CC = gcc
CFLAGS = -Wall -std=c11
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm

SOURCES = main.c ./star/star.c ./planet/planet.c ./utils/utils.c
OUTPUT = game.exe

all:
	$(CC) $(CFLAGS) $(SOURCES) -o $(OUTPUT) $(LIBS)

clean:
	del $(OUTPUT)