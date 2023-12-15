# Var defs
ex03_objects = ex02.o runtime_error.o
objects = $(ex03_objects)  # To be appended to
executable_dir = ./exec


# Targets
all:
ex03: $(ex03_objects)
	clang++ ex03.cpp $(ex03_objects) -o $(executable_dir)/ex03 --std=c++11 -Wall -Wpedantic
ex02.o:
runtime_error.o:


# Directives (Psuedo-targets)
clean:
	rm $(objects)
clean_all: clean
	rm $(executable_dir)/*
	