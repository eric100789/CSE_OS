CC:=gcc
FLAG:= -Wall
OFILE:= main.o
SOURCE:= main.c

all: $(OFILE)
	$(CC) -o main $(OFILE)
dep: $(SOURCE)
	$(CC) $(FLAG) -c $(SOURCE)
clean:
	-rm *.o
