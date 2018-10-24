
compile:
	g++ $(wildcard source/*.cpp) -o build/rt.out -Iinclude -Ilib
	
run:
	./build/rt.out
