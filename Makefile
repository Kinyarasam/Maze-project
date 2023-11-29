CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
SDL_FLAGS = $(shell sdl2-config --cflags --libs)

SRCDIR = src
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(BINDIR)/%.o)

all: raycasting_game

raycasting_game: $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(SDL_FLAGS)

$(BINDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c -o $@ $< $(SDL_FLAGS)

clean:
	rm -rf $(BINDIR)
	rm -rf raycasting_game

.PHONY: all clean
