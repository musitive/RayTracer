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
$(OBJECTS_DIR)/AbstractObject.cpp $(OBJECTS_DIR)/Sphere.cpp $(OBJECTS_DIR)/Triangle.cpp $(CAMERA_DIR)/Frame.cpp \
$(CAMERA_DIR)/RayTracer.cpp $(CAMERA_DIR)/Intersection.cpp $(CAMERA_DIR)/Camera.cpp $(CAMERA_DIR)/AntiAliasCam.cpp \
$(SCENE_DIR)/Scene.cpp $(FILE_MANAGEMENT_DIR)/SceneLoader.cpp $(FILE_MANAGEMENT_DIR)/PPM.cpp $(SRC_DIR)/main.cpp

# Object files
OBJFILES = $(SRCFILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Compiler
CXX = g++
CXXFLAGS = -O3 --std=c++17 -g -I$(MATH_DIR) -I$(MATERIALS_DIR) -I$(OBJECTS_DIR) -I$(SRC_DIR) -I$(CAMERA_DIR) -I$(SCENE_DIR) -I$(FILE_MANAGEMENT_DIR)
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
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -f $(OBJFILES) $(TARGET) *~

# Test
small_test:
	./raytracer tests/test_01_192x144p.env outputs/test_01_192x144p.ppm

large_test:
	./raytracer tests/test_02_1920x1080p.env outputs/test_02_1920x1080p.ppm