
compile:
	g++ source/Image.cpp source/Ray.cpp source/Vector3.cpp source/main.cpp -o build/rt.out -Iinclude -Ilib
	
run:
	./build/rt.out
