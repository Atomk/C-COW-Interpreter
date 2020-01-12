CC=gcc
CLANG=-Wall -g
FILENAME=cowInterpreter

all: $(FILENAME)

run:
	./$(FILENAME)

clean:
	rm -f $(FILENAME)