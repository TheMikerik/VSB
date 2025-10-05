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
    src/Scene1.cpp \
    src/DrawableObject.cpp \
    src/ShaderProgram.cpp \
    src/Model.cpp \
    src/Transformation.cpp \
    src/Translate.cpp \
    src/Rotate.cpp \
    src/Scale.cpp

# Object files
OBJS = $(SRCS:src/%.cpp=build/%.o)

# Makefile rules
all: $(TARGET_PATH)
	./$(TARGET_PATH)

$(TARGET_PATH): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET_PATH) $(LIBS)

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TARGET_PATH) $(OBJS)