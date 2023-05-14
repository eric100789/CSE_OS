CC:=g++
FLAG:= -Wall
OFILE:= main.o
SOURCE:= main.cpp 

all: $(OFILE)
	$(CC) -o main $(OFILE)
dep: $(SOURCE)
	$(CC) $(FLAG) -c $(SOURCE)
clean:
	-rm *.o
