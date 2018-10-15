
compile:
	g++ source/Image.cpp source/Sphere.cpp source/Ray.cpp source/Vector3.cpp source/main.cpp -o build/rt.out -Iinclude -Ilib
	
run:
	./build/rt.out
