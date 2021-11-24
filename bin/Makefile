checks = -Wall -Wextra -pedantic-errors
libs = -lraylib -lgdi32 -lwinmm
no_console = -Wl,-subsystem,windows

default:
# windres resources.rc resources.o
	g++ -std=c++17 -O2 -c ../src/*.cpp $(checks) -I ../include 
	g++ ./*.o -o Connect4 -L ../lib $(libs) $(no_console)
