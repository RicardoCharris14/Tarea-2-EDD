DEPS = entry.h user.h node.h linked_list.h open_hash_map.h close_hash_map.h probing_methods.h hashing_methods.h
VPATH = testing

all: test_id test_name test_results

test_id: test_id.cpp $(DEPS)
	g++ -O3 $< -o $@

test_name: test_name.cpp $(DEPS)
	g++ -O3 $< -o $@

test_results: test_id test_name test_all.sh
	./test_all.sh 1000 20000 20
