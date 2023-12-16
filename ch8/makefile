# Var defs
error = runtime_error.o
ex03_objects = ex02.o $(error)
ex07_objects = $(ex03_objects) ex06.o  # In progress
objects = $(ex07_objects)
executable_dir = ./exec


# Targets
all:
ex07: $(ex07_objects)
	clang++ ex07.cpp $(ex07_objects) -o $(executable_dir)/ex07 --std=c++11 -Wall -Wpedantic
ex06.o:
ex05: $(ex03_objects)
	clang++ ex05.cpp $(ex03_objects) -o $(executable_dir)/ex05 --std=c++11 -Wall -Wpedantic
ex03: $(ex03_objects)
	clang++ ex03.cpp $(ex03_objects) -o $(executable_dir)/ex03 --std=c++11 -Wall -Wpedantic
ex02.o:
runtime_error.o:


# Directives (Psuedo-targets)
clean:
	rm $(objects)
clean_exec:
	rm $(executable_dir)/*
clean_all: clean_exec clean
	
