CXX	=	gcc
INC	=	./include
FLAGS	=	-Wall -O3 -ggdb -I./bmp -I./bytes
SOURCE	=	main.c bmp/bmp.c bytes/bytes.c
BIN	=	main

all:
	$(CXX) $(FLAGS) $(SOURCE) -o $(BIN)

clean:
	rm -f *~ $(BIN)
