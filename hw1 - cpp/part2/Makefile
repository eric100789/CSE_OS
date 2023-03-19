CC:=g++
FLAG:= -Wall
OFILE:= main.o parser.o shell.o
SOURCE:= main.cpp parser.cpp shell.cpp

all: $(OFILE)
	$(CC) -o main $(OFILE)
dep: $(SOURCE)
	$(CC) $(FLAG) -c $(SOURCE)
clean:
	-rm *.o
