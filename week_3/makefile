.PHONY: clean

all: directories bin/main

bin/main: src/main.c
	gcc src/main.c -o bin/main

directories:
	mkdir -p bin

clean:
	rm -f bin/*