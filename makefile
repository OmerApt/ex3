all: StrList

StrList.o:StrList.c StrList.h
	-gcc -Wall -c StrList.c

Main.o:Main.c StrList.h
	-gcc -Wall -c Main.c

StrList: Main.o StrList.o
	-gcc -Wall -o StrList Main.o StrList.o

clean: 
	rm -f *.a *.o *.so StrList