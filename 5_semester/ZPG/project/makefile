# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -g -DGL_SILENCE_DEPRECATION

# Update include and library paths based on Homebrew prefix and project structure
INCLUDES = -Iinclude -I/opt/homebrew/opt/glfw/include -I/opt/homebrew/opt/glm/include -I/opt/homebrew/opt/glew/include

# Libraries
LIBS = -L/opt/homebrew/opt/glfw/lib -L/opt/homebrew/opt/glew/lib -lglfw -lGLEW -framework OpenGL

# Executable name
TARGET = main

# Source files
SRCS = src/main.cpp src/Application.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Makefile rules
all: $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJS)
