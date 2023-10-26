CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =

SOURCES = main.c image.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = conversor_imagens_PPM

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
    $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $(OBJECTS)

.c.o:
    $(CC) $(CFLAGS) -c $< -o $@


clean:
    rm -f $(OBJECTS) $(EXECUTABLE)

.PHONY: all clean