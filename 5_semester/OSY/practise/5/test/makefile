CC = g++
CFLAGS = -Wall -std=c++17
TARGET = cv05

all: $(TARGET)

$(TARGET): cv05.o
	$(CC) $(CFLAGS) -o $(TARGET) cv05.o

cv05.o: cv05.cpp
	$(CC) $(CFLAGS) -c cv05.cpp

clear:
	rm -f $(TARGET) cv05.o