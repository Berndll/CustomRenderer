DEFINE 		= UNICODE
INCLUDE 	= include
LIBRARIES 	= gdi32
SOURCE 		= src

all:
	g++ $(wildcard $(SOURCE)/*.cpp) -o main -I$(INCLUDE) -l$(LIBRARIES) -D$(DEFINE)