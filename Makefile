DEPS = entry.h user.h node.h linked_list.h open_hash_map.h

ejecutable: main.cpp $(DEPS)
	g++ -o ejecutable -O3 main.cpp


