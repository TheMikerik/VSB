##############################################################################
#
# Makefile for multithreaded Socket Server and Client
#
##############################################################################

# Sources
SOURCES_SERVER = server.cpp
SOURCES_CLIENT = client.cpp

# Targets
TARGET_SERVER = server
TARGET_CLIENT = client

# Compiler and Flags
CXX = g++
CXXFLAGS = -g -pthread -std=c++11 -Wall
LDFLAGS = -pthread
LDLIBS = 

.PHONY: all clean

all: $(TARGET_SERVER) $(TARGET_CLIENT)

$(TARGET_SERVER): $(SOURCES_SERVER)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

$(TARGET_CLIENT): $(SOURCES_CLIENT)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -rf *.o $(TARGET_SERVER) $(TARGET_CLIENT)