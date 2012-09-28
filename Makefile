CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c word_generator.c rule_generator.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=nagen

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean stat
clean:
	rm *.o
stat:
	cat *.c *.h | wc
