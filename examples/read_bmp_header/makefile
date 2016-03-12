CXX	=	gcc
INC	=	../include
FLAGS	=	-Wall -O3 -ggdb -I$(INC)
SOURCE	=	main.c $(INC)/bmp.c $(INC)/bytes.c
BIN	=	main

all:
	$(CXX) $(FLAGS) $(SOURCE) -o $(BIN)

clean:
	rm -f *~ $(BIN)
