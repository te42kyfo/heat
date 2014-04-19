.PHONY: all main clean debug
NAME=heat
CXX=g++
LIB= `sdl2-config --libs` -lGL -lGLEW
CPPFLAGS= -O3 -Wall -Werror -Wshadow -ansi -fopenmp -std=c++0x `sdl2-config --cflags`
SRC= main.cpp render.cpp

HEADERS= $(shell find . -iname "*.hpp")

all: $(NAME)


run: $(NAME)
	./$(NAME)

debug: $(SRC) $(HEADERS)
	$(CXX) $(CPPFLAGS) -g $(INCLUDE) $(SRC) -o $(NAME) $(LIB)

$(NAME): $(SRC) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(INCLUDE) $(SRC) -o $(NAME) $(LIB)


clean:
	rm -f $(NAME)
