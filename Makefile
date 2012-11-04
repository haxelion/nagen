CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=main.c word_generator.c rule_generator.c nagen.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=nagen
INSTALL_PATH?=/usr/local

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY : clean install uninstall

clean:
	rm -rf *.o

install: all
	cp ./nagen $(INSTALL_PATH)/bin

uninstall:
	rm $(INSTALL_PATH)/bin/nagen
