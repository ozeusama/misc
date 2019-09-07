CC = gcc
CFLAGS = -std=gnu11
DFLAGS = -W -Wall -Wextra -pedantic -Og -DDEBUG
RFLAGS = -O2 -march=native -flto
TARGET = test
LIBS =

SRCS := $(wildcard *.c)
OBJS := $(patsubst %.c,%.o,$(SRCS))

all: release

debug: CFLAGS += $(DFLAGS)
debug: $(TARGET)

release: CFLAGS += $(RFLAGS)
release: $(TARGET)

$(TARGET): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBS)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(TARGET).exe $(TARGET) $(OBJS)
