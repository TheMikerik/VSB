# Makefile for CV02 Project

# Variables
TARGET = main
LIBNAME_INT = input_int
LIBFILE_INT = lib$(LIBNAME_INT).so

LIBNAME_HEX = input_hex
LIBFILE_HEX = lib$(LIBNAME_HEX).so

TYPE ?= input_int

CC = gcc
LDFLAGS = -L.
LDLIBS_INT = -l$(LIBNAME_INT)
LDLIBS_HEX = -l$(LIBNAME_HEX)

all: $(LIBFILE_INT) $(LIBFILE_HEX) $(TARGET)

clean:
	rm -f $(TARGET) $(LIBFILE_INT) $(LIBFILE_HEX) *.o input_int/*.o input_hex/*.o

$(LIBFILE_INT): input_int/input.o
	$(CC) -shared $(LDFLAGS) $^ -o $@

$(LIBFILE_HEX): input_hex/input.o
	$(CC) $(CFLAGS) -shared $(LDFLAGS) $^ -o $@

input_int/input.o: input_int/input.c input.h
	$(CC) $(CFLAGS) -c input_int/input.c -o input_int/input.o

input_hex/input.o: input_hex/input.c input.h
	$(CC) $(CFLAGS) -c input_hex/input.c -o input_hex/input.o

main.o: main.c input.h
	$(CC) $(CFLAGS) -c main.c -o main.o

$(TARGET): main.o
ifeq ($(TYPE),input_hex)
	$(CC) $(CFLAGS) main.o $(LDFLAGS) $(LDLIBS_HEX) -o $(TARGET)
else
	$(CC) $(CFLAGS) main.o $(LDFLAGS) $(LDLIBS_INT) -o $(TARGET)
endif

# Phony targets
.PHONY: all clean