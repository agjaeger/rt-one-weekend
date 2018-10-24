
compile:
	g++ $(wildcard source/*.cpp) -o build/rt.out -Iinclude -Ilib -lpthread
	
run:
	./build/rt.out
