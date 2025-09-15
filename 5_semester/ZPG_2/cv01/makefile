# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -DGL_SILENCE_DEPRECATION
.DEFAULT_GOAL := run

# Update include and library paths based on Homebrew prefix
INCLUDES = -I/opt/homebrew/opt/glfw/include -I/opt/homebrew/opt/glm/include

# Libraries
LIBS = -L/opt/homebrew/lib -lglfw -framework OpenGL

# Executable name
TARGET = main

# Source files
SRCS = main.cpp

# Makefile rules
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRCS) -o $(TARGET) $(LIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
