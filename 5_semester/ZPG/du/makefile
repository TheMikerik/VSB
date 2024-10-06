# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -DGL_SILENCE_DEPRECATION

# Include Directories
# - "include" is your project's header files
# - The rest are external libraries installed via Homebrew
INCLUDES = -Iinclude \
           -I/opt/homebrew/opt/glfw/include \
           -I/opt/homebrew/opt/glm/include \
           -I/opt/homebrew/opt/glew/include

# Library Paths and Libraries
# - Adjust the library paths if your Homebrew prefix is different
LIBS = -L/opt/homebrew/lib \
       -lglfw \
       -framework OpenGL \
       -lGLEW

# Executable Name
TARGET = main

# Build directory for object files
BUILD_DIR = build

# Source Files
SRCS = src/main.cpp \
       src/Application.cpp \
       src/Shader.cpp \
       src/Model.cpp

# Object Files: Replace src/ with build/
# This transforms src/main.cpp to build/main.o, etc.
OBJS = $(patsubst src/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Default Target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

# Rule to compile source files into object files in build/
# The pipe '|' ensures that build/ is created before compilation
$(BUILD_DIR)/%.o: src/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Create build directory if it does not exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Clean up build artifacts
clean:
	rm -rf $(TARGET) $(BUILD_DIR)

# Phony Targets
.PHONY: all clean