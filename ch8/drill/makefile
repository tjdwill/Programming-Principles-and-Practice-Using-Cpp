# Writing my first ever `make` file.

drill_objects = use.o my.o
executable_dir = ./exec

# Drill 
use: $(drill_objects)
	clang++ $(drill_objects) -o $(executable_dir)/use

use.o:
	clang++ -c use.cpp -o use.o --std=c++11 -Wall -Wpedantic
my.o:
	clang++ -c my.cpp -o my.o --std=c++11  -Wall -Wpedantic

d02:
	clang++ d02.cpp -o $(executable_dir)/d02 --std=c++11 -Wall -Wpedantic

# Pseudos
all: d02 use  # makes all of the recipies

clean:
	rm $(drill_objects)
clean_exec:
	rm $(executable_dir)/*
clean_all: clean_exec clean
