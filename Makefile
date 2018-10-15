
compile:
	g++ source/Image.cpp source/main.cpp -o build/rt.out -Iinclude -Ilib
	
run:
	./build/rt.out
