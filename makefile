DEFINE 		= UNICODE
INCLUDE 	= include
LIBRARIES 	= gdi32
SOURCE 		= src

all: compile execute

compile:
	g++ $(wildcard $(SOURCE)/*.cpp) -o main -I$(INCLUDE) -l$(LIBRARIES) -D$(DEFINE)

execute:
	./main