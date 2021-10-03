CC := gcc
CFLAGS := -lwiringPi -lm

.PHONY = clean

%:
	$(CC) $(CFLAGS) -o $@.o $@.c

clean:
	rm -rvf *.o
