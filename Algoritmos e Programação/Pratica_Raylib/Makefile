CC = gcc
CFLAGS = $(shell pkg-config --cflags raylib)
LDFLAGS = $(shell pkg-config --libs raylib)

FILE?=main.c

# Specifically for macOS
ifeq ($(shell uname), Darwin)
    LDFLAGS += -framework IOKit -framework Cocoa -framework OpenGL
endif

# I want to do a raylib file.c and execute the following command:
# Ex: make raylib file.c
compile-raylib: $(FILE)
	$(CC) -o $(OUTPUT) $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f praticaray
