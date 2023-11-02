INCLUDE = include
SOURCE = src

all:
	g++ $(wildcard $(SOURCE)/*.cpp) -o main -I$(INCLUDE)