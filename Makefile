LIBS = -lusb-1.0
CC = gcc
CFLAGS = -g -Wall
LFLAGS = -L/usr/local/Cellar/libusb/1.0.9/lib/
INCLUDES = -I/usr/local/include/libusb-1.0/
SRCS = ./src/blinkstick.c
OBJS = $(SRCS:.c=.o)
TARGET = blinkstick

all: $(SRCS) $(TARGET)

$(TARGET): 	$(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(LFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) ./src/*.o *~ $(TARGET)


