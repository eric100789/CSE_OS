CC:=g++
FLAG:= -Wall
OFILE:= main.o mm.o
SOURCE:= main.cpp mm.cpp

all: $(OFILE)
	$(CC) -o main $(OFILE)
dep: $(SOURCE)
	$(CC) $(FLAG) -c $(SOURCE)
clean:
	-rm *.o
