.PHONY: all main
NAME=heat
CXX=g++
LIB= `sdl2-config --libs` -lGL
CPPFLAGS= -O3 -Wall -Werror -Wshadow -ansi -fopenmp -std=c++0x
SRC= main.cpp

HEADERS=`find . -iname . *.hpp`

all: $(NAME)

run: $(NAME)
	./$(NAME)

$(NAME): $(SRC)
	$(CXX) $(CPPFLAGS) $(INCLUDE) $(SRC) -o $(NAME) $(LIB) 


clean:
	rm -f $(NAME)