all: tracer

tracer:
	g++ -g -std=c++17 Vec.cpp Object.cpp Sphere.cpp Triangle.cpp Environment.cpp FileManager.cpp RayTracer.cpp JitterTracer.cpp Scene.cpp main.cpp -o $@

small_test:
	./tracer tests/test.env outputs/test.ppm

test:
	./tracer tests/test.env outputs/test.ppm &
	./tracer tests/SceneII.env outputs/SceneII.ppm &
	./tracer tests/diffuse.env outputs/diffuse.ppm &
	./tracer tests/test2.env outputs/test2.ppm &

handin:
	tar -czf raytracer.tar *.cpp *.h diffuse.ppm test.ppm SceneII.ppm

clean:
	rm -f tracer