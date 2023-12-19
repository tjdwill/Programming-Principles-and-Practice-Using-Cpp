# Var Defs
output_dir = ./exec
headers_dir = ./headers
src_dir = ./src
test_dir = ./tests
ex02_objs = name_pairs.o test_name_pairs.o

# Search Paths
vpath %.h  $(headers_dir)
vpath %.hpp  $(headers_dir)
vpath %.cpp $(src_dir) $(test_dir)
vpath %.o $(src_dir) $(test_dir)


test_name_pairs: $(ex02_objs) | $(output_dir)
	clang++ $(ex02_objs) -o $(output_dir)/$@ --std=c++11 -Wall -Wpedantic
	$(output_dir)/$@

test_name_pairs.o: name_pairs.hpp

name_pairs.o: name_pairs.hpp

$(output_dir):
	mkdir $(output_dir)

.PHONY: clean clean_exec clean_all
clean:
	rm -f $(ex02_objs)
clean_exec:
	rm -rf $(output_dir)
clean_all: clean clean_exec