# Variables
output_dir = exec
obj_ex01 = ex01.o
objects = $(obj_ex01)


# Directory Searches
vpath %.cpp src:drill
vpath %.hpp headers


# Recipes
ex01: $(obj_ex01) | $(output_dir)
	clang++ $< -o $(output_dir)/$@ --std=c++11 -Wall -Wpedantic
	$(output_dir)/$@
ex01.o:

$(output_dir):
	mkdir $(output_dir)

.PHONY: clean clean_exec

clean:
	rm -f $(objects)
clean_exec:
	rm -rf $(output_dir)
clean_all: clean clean_exec