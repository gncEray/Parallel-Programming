CC=gcc
CFLAGS=-I.
DEPS = hellomake.h
OBJ = 19050111005.o hellofunc.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
