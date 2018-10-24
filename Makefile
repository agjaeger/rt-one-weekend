
compile:
	g++ $(wildcard source/*.cpp) lib/zupply.cpp -o build/rt.out -Iinclude -Ilib
	
run:
	./build/rt.out
