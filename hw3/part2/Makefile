CC:=g++
FLAG:= -Wall
OFILE:= main.o monitor.o
SOURCE:= main.cpp monitor.cpp

all: $(OFILE)
	$(CC) -o main $(OFILE)
dep: $(SOURCE)
	$(CC) $(FLAG) -c $(SOURCE)
clean:
	-rm *.o
