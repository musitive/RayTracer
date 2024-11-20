# test:
# 	./tracer tests/test.env outputs/test.ppm &
# 	./tracer tests/SceneII.env outputs/SceneII.ppm &
# 	./tracer tests/diffuse.env outputs/diffuse.ppm &
# 	./tracer tests/test2.env outputs/test2.ppm &

# handin:
# 	tar -czf raytracer.tar *.cpp *.h diffuse.ppm test.ppm SceneII.ppm

# Directories
SRC_DIR = src
OBJ_DIR = obj
MATH_DIR = $(SRC_DIR)/3D_Math
MATERIALS_DIR = $(SRC_DIR)/Materials
OBJECTS_DIR = $(SRC_DIR)/Objects
CAMERA_DIR = $(SRC_DIR)/Camera
SCENE_DIR = $(SRC_DIR)/Scene
FILE_MANAGEMENT_DIR = $(SRC_DIR)/FileManagement

# Source files
SRCFILES = $(MATH_DIR)/Vec.cpp $(MATH_DIR)/Ray.cpp $(MATERIALS_DIR)/Diffuse.cpp $(MATERIALS_DIR)/Reflective.cpp \
$(OBJECTS_DIR)/Object.cpp $(OBJECTS_DIR)/Sphere.cpp $(OBJECTS_DIR)/Triangle.cpp $(MATH_DIR)/Intersection.cpp \
$(CAMERA_DIR)/Frame.cpp $(SCENE_DIR)/Environment.cpp $(CAMERA_DIR)/RayTracer.cpp $(CAMERA_DIR)/Camera.cpp \
$(SCENE_DIR)/Scene.cpp $(FILE_MANAGEMENT_DIR)/FileManager.cpp $(SRC_DIR)/main.cpp

# Object files
OBJFILES = $(SRCFILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Compiler
CXX = g++
CXXFLAGS = -O3 --std=c++17 -g -I$(MATH_DIR) -I$(MATERIALS_DIR) -I$(OBJECTS_DIR) -I$(SRC_DIR) -I$(CAMERA_DIR) -I$(SCENE_DIR) -I$(FILE_MANAGEMENT_DIR)
LDFLAGS =

# Program
TARGET = raytracer

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CXX) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJFILES) $(TARGET) *~

small_test:
	./raytracer tests/test.env outputs/test.ppm