# Directories
SRC_DIR = src
OBJ_DIR = obj
MATH_DIR = $(SRC_DIR)/3D_Math
INTERSECT_DIR = $(SRC_DIR)/Intersections
MATERIALS_DIR = $(SRC_DIR)/Materials
OBJECTS_DIR = $(SRC_DIR)/Objects
CAMERA_DIR = $(SRC_DIR)/Camera
SCENE_DIR = $(SRC_DIR)/Scene
FILE_MANAGEMENT_DIR = $(SRC_DIR)/FileManagement
KD_TREE_DIR = $(SRC_DIR)/KDTree

# Source files
MATH_SRCFILES = $(MATH_DIR)/Direction.cpp $(MATH_DIR)/Ray.cpp
INTERSECT_SRCFILES = $(INTERSECT_DIR)/AbstractIntersect.cpp $(INTERSECT_DIR)/AbstractIntersect.cpp $(INTERSECT_DIR)/DiffuseIntersect.cpp \
$(INTERSECT_DIR)/ReflectionIntersect.cpp $(INTERSECT_DIR)/MissedIntersect.cpp
MATERIALS_SRCFILES = $(MATERIALS_DIR)/Diffuse.cpp $(MATERIALS_DIR)/Reflective.cpp
OBJECTS_SRCFILES = $(OBJECTS_DIR)/AbstractObject.cpp $(OBJECTS_DIR)/Sphere.cpp $(OBJECTS_DIR)/Triangle.cpp
CAMERA_SRCFILES = $(CAMERA_DIR)/Frame.cpp $(CAMERA_DIR)/RayTracer.cpp $(CAMERA_DIR)/Camera.cpp $(CAMERA_DIR)/AntiAliasCam.cpp
SCENE_SRCFILES = $(SCENE_DIR)/Scene.cpp
FILE_MANAGEMENT_SRCFILES = $(FILE_MANAGEMENT_DIR)/SceneBuilder.cpp $(FILE_MANAGEMENT_DIR)/PPM.cpp
KD_TREE_SRCFILES = $(KD_TREE_DIR)/KDTree.cpp $(KD_TREE_DIR)/BoundingBox.cpp $(KD_TREE_DIR)/IntersectionFactory.cpp

SRCFILES = $(MATH_SRCFILES) $(INTERSECT_SRCFILES) $(MATERIALS_SRCFILES) $(OBJECTS_SRCFILES) $(KD_TREE_SRCFILES) $(CAMERA_SRCFILES) \
$(SCENE_SRCFILES) $(FILE_MANAGEMENT_SRCFILES) $(SRC_DIR)/main.cpp

# Object files
OBJFILES = $(SRCFILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Compiler
CXX = g++
CXXFLAGS = -O3 --std=c++17 -g
SRCFLAGS = -I$(MATH_DIR) -I$(INTERSECT_DIR) -I$(MATERIALS_DIR) -I$(OBJECTS_DIR) -I$(SRC_DIR) -I$(CAMERA_DIR) -I$(SCENE_DIR) -I$(FILE_MANAGEMENT_DIR) -I src/KDTree
LDFLAGS =

# Program
TARGET = raytracer

# Rules
all: $(TARGET)

# Dependencies
$(TARGET): $(OBJFILES)
	$(CXX) $(LDFLAGS) -o $@ $^

# Pattern rule
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(SRCFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJFILES) $(TARGET) *~

# Test
test_01:
	./raytracer tests/test_01.env outputs/test_01.ppm

test_02:
	./raytracer tests/test_02.env outputs/test_02.ppm

test_03:
	./raytracer tests/test_03.env outputs/test_03.ppm

test_04:
	./raytracer tests/test_04.env outputs/test_04.ppm