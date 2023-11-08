CC = gcc
OBJ = main.o list.o ui.o
HEADER = list.h ui.h
EXE = run

all: $(EXE)

.c.o: ; $(CC) -c $*.c -o $*.o

$(EXE): $(OBJ)
	$(CC) -o $@ $(OBJ)

clean:
	rm -rf $(EXE) *.o
