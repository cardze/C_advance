CC = gcc
OBJ = stack.o space.o main.o
EXE = run

all: $(EXE)

.c.o: ; $(CC) -c $*.c

$(EXE): $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	rm -rf $(EXE) *.o
