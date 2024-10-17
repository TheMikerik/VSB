CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

TARGET = generator
SRCS = generator.cpp

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(TARGET)