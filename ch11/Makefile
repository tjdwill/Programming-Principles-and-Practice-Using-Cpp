# Variables
output_dir = exec
obj_ex01 = ex01.o
obj_ex02 = ex02.o
obj_ex03 = ex03.o
obj_ex04 = ex04.o
obj_ex10_11 = ex10_11.o
objects = $(obj_ex01) $(obj_ex02) $(obj_ex03) $(obj_ex04) $(obj_ex10_11)


# Directory Searches
vpath %.cpp src:drill
vpath %.hpp headers


# Recipes
ex01: $(obj_ex01) | $(output_dir)
	clang++ $< -o $(output_dir)/$@ --std=c++11 -Wall -Wpedantic
	$(output_dir)/$@
$(obj_ex01):

ex02: $(obj_ex02) | $(output_dir)
	clang++ $^ -o $(output_dir)/$@ --std=c++11 -Wall -Wpedantic
	$(output_dir)/$@
$(obj_ex02):

ex03: $(obj_ex03) | $(output_dir)
	clang++ $^ -o $(output_dir)/$@ --std=c++11 -Wall -Wpedantic
	$(output_dir)/$@
$(obj_ex03):

ex04: $(obj_ex04) | $(output_dir)
	clang++ $^ -o $(output_dir)/$@ --std=c++11 -Wall -Wpedantic
	$(output_dir)/$@
$(obj_ex04):

ex10_11: $(obj_ex10_11) | $(output_dir)
	clang++ $^ -o $(output_dir)/$@ --std=c++11 -Wall -Wpedantic
	$(output_dir)/$@
$(obj_ex10_11):

$(output_dir):
	mkdir $(output_dir)

.PHONY: clean clean_exec

clean:
	rm -f $(objects)
clean_exec:
	rm -rf $(output_dir)
clean_all: clean clean_exec