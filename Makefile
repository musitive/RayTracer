all: tracer

tracer:
	g++ -g -std=c++17 Vec.cpp Object.cpp Sphere.cpp Triangle.cpp Environment.cpp FileManager.cpp RayTracer.cpp main.cpp -o $@

small_test:
	./tracer tests/test.rayTracing outputs/test.ppm

test:
	./tracer tests/test.rayTracing outputs/test.ppm &
	./tracer tests/SceneII.rayTracing outputs/SceneII.ppm &
	./tracer tests/diffuse.rayTracing outputs/diffuse.ppm &
	./tracer tests/test2.rayTracing outputs/test2.ppm &

handin:
	tar -czf raytracer.tar *.cpp *.h diffuse.ppm test.ppm SceneII.ppm

clean:
	rm -f tracer