DEPS = entry.h user.h node.h linked_list.h open_hash_map.h hash_map.h probing_methods.h hashing_methods.h

test: test.cpp $(DEPS)
	g++ -o test -O3 test.cpp

ejecutable: main.cpp $(DEPS)
	g++ -o ejecutable -O3 main.cpp

dataset: datasets/convert.py datasets/universities_followers.csv
	python datasets/convert.py
