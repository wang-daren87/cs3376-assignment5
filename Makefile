# Daren Wang
# SE3376.502
#
# Makefile for Assignment 5
#
SHELL = /bin/sh
FLAGS = -Wall -g
CC = g++

all:	TwoPipesTwoChildren TwoPipesThreeChildren dynpipe

TwoPipesTwoChildren:	TwoPipesTwoChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesTwoChildren.cpp

TwhoPipesThreeChildren:	TwoPipesThreeChildren.cpp
	$(CC) $(FLAGS) -o $@ TwoPipesThreeChildren.cpp

dynpipe:		DynPipe.cpp
	$(CC) $(FLAGS) -o $@ DynPipe.cpp

clean:
	rm -f TwoPipesTwoChildren TwoPipesTwoChildren.o TwoPipesThreeChildren TwoPipesThreeChildren.o dynpipe DynPipe.o
