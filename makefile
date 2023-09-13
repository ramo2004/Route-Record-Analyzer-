 CC = gcc
CFLAGS = -Wall -Wextra -std=c99
SRCS = main.c route-records.c
OBJS = $(SRCS:.c=.o)
TARGET = program

$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

main.o: main.c route-records.h
    $(CC) $(CFLAGS) -c main.c

route-records.o: route-records.c route-records.h
    $(CC) $(CFLAGS) -c route-records.c

clean:
    rm -f $(OBJS) $(TARGET)