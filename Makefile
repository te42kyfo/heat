.PHONY: all main clean
NAME=heat
CXX=g++
LIB= `sdl2-config --libs` -lGL
CPPFLAGS= -O3 -Wall -Werror -Wshadow -ansi -fopenmp -std=c++0x `sdl2-config --cflags`
SRC= main.cpp

HEADERS= $(shell find . -iname "*.hpp")

all: $(NAME)


run: $(NAME)
	./$(NAME)

$(NAME): $(SRC) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(INCLUDE) $(SRC) -o $(NAME) $(LIB)


clean:
	rm -f $(NAME)
