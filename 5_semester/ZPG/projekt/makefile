# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -DGL_SILENCE_DEPRECATION

# Update include and library paths based on Homebrew prefix and project structure
INCLUDES = \
    -Iinclude \
    -I/opt/homebrew/opt/glfw/include \
    -I/opt/homebrew/opt/glm/include \
    -I/opt/homebrew/opt/glew/include

# Libraries
LIBS = \
    -L/opt/homebrew/opt/glfw/lib \
    -L/opt/homebrew/opt/glew/lib \
    -lglfw \
    -lGLEW \
    -framework OpenGL

# Executable name
TARGET = main
TARGET_PATH = build/$(TARGET)

# Source files
SRCS = \
    src/main.cpp \
    src/Application.cpp \
    src/Scene.cpp \
    src/DrawableObject.cpp \
    src/ShaderProgram.cpp \
    src/Model.cpp \
    src/Transformation.cpp \
    src/Camera.cpp \
    src/Controller.cpp \
    src/Light.cpp \
    src/Scenes/Scene1.cpp \
    src/Scenes/Scene2.cpp \
    src/Scenes/Scene3.cpp \
    src/Scenes/Scene4.cpp

# Object files
OBJS = $(SRCS:src/%.cpp=build/%.o)

# Default target: build and run the application
all: $(TARGET_PATH)
	@echo "Running the application..."
	./$(TARGET_PATH)

# Linking the executable
$(TARGET_PATH): $(OBJS)
	@echo "Linking..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET_PATH) $(LIBS)

# Compiling source files to object files
build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean up build artifacts
clear:
	@echo "Cleaning up..."
	rm -f $(TARGET_PATH) $(OBJS)