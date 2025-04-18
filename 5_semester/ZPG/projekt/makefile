# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -g -DGL_SILENCE_DEPRECATION

# Update include and library paths based on Homebrew prefix and project structure
INCLUDES = \
    -Iinclude \
    -Iinclude/stb \
    -I/opt/homebrew/opt/glfw/include \
    -I/opt/homebrew/opt/glm/include \
    -I/opt/homebrew/opt/glew/include \
    -I/opt/homebrew/opt/assimp/include

# Libraries
LIBS = \
    -L/opt/homebrew/opt/glfw/lib \
    -L/opt/homebrew/opt/glew/lib \
    -L/opt/homebrew/opt/assimp/lib \
    -lglfw \
    -lGLEW \
    -lassimp \
    -framework OpenGL

# Executable name
TARGET = main
TARGET_PATH = build/$(TARGET)

# Source files
SRCS = \
    src/main.cpp \
    src/Core/Application.cpp \
    src/Core/Controller.cpp \
    src/Core/Model.cpp \
    src/Core/Object.cpp \
    src/Core/ObjectModel.cpp \
    src/Core/Material.cpp \
    src/Core/MaterialManager.cpp \
    src/Core/Transformation.cpp \
    src/Core/Skybox.cpp \
    src/Core/SkyboxModel.cpp \
    src/Core/Texture.cpp \
    src/Graphics/Camera.cpp \
    src/Graphics/DrawableObject.cpp \
    src/Graphics/Drawable3DObject.cpp \
    src/Graphics/Light.cpp \
    src/Graphics/Spotlight.cpp \
    src/Graphics/stb_image.cpp \
    src/Shaders/ShaderLoader.cpp \
    src/Shaders/ShaderProgram.cpp \
    src/Scenes/Scene.cpp \
    src/Scenes/Scene1.cpp \
    src/Scenes/Scene3.cpp \
    src/Scenes/Scene5.cpp \
    src/Scenes/Scene6.cpp \
    src/Scenes/Scene7.cpp \
    src/Scenes/Scene8.cpp


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