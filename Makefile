CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c word_generator.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=nagen

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean
clean:
	rm *.o
