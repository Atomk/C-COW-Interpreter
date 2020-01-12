CC=gcc
CLANG=-Wall -g
FILENAME=cow-interpreter

all: $(FILENAME)

run:
	./$(FILENAME)

clean:
	rm -f $(FILENAME)