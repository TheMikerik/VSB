CC = gcc

CFLAGS = -Wall -Wextra -std=c11

TARGET = output

SRCS = main.c output.c

OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c output.h
	$(CC) $(CFLAGS) -c main.c

output.o: output.c output.h
	$(CC) $(CFLAGS) -c output.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean