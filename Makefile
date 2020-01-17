CC=gcc
CLANG=-Wall -g
FILENAME=cow-interpreter

all: $(FILENAME)

run:
	./$(FILENAME) ./Samples/hello_world_commented.cow

clean:
	rm -f $(FILENAME)