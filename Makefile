.PHONY: all main clean debug

CXX=g++
LIB= `sdl2-config --libs` -lGL -lGLEW
CPPFLAGS= -Ofast -Wall -Werror -Wshadow -ansi -fopenmp -std=c++1y `sdl2-config --cflags`
HEAT_SRC= main.cpp simulation.cpp ./vis/sdl_gl.cpp  ./vis/draw_slice.cpp
HEADERS= $(shell find . -iname "*.hpp")
INCLUDE= -I./vis/

all: heat


run: heat
	./heat


heat: $(HEAT_SRC) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(INCLUDE) $(HEAT_SRC) -o heat $(LIB)


clean:
	rm -f heat
