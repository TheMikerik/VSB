# Makefile for the project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -fPIC

# Directories
MAIN_DIR = main
LIB_INT_DIR = lib_int
LIB_FLOAT_DIR = lib_float

# Output names
MAIN_OUT = $(MAIN_DIR)/main
LIB_INT_OUT = $(LIB_INT_DIR)/libinput.so
LIB_FLOAT_OUT = $(LIB_FLOAT_DIR)/libinput.so

# Default target
all: $(MAIN_OUT) $(LIB_INT_OUT) $(LIB_FLOAT_OUT)

# Main program
$(MAIN_OUT): $(MAIN_DIR)/main.c $(MAIN_DIR)/input.h
	$(CC) $(CFLAGS) -o $@ $< -ldl

# Integer library
$(LIB_INT_OUT): $(LIB_INT_DIR)/input.c $(MAIN_DIR)/input.h
	$(CC) $(CFLAGS) -shared -o $@ $<

# Float library
$(LIB_FLOAT_OUT): $(LIB_FLOAT_DIR)/input.c $(MAIN_DIR)/input.h
	$(CC) $(CFLAGS) -shared -o $@ $<

# Clean target
clean:
	rm -f $(MAIN_OUT) $(LIB_INT_OUT) $(LIB_FLOAT_OUT)

# Phony targets
.PHONY: all clean