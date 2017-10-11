CC = g++
CFLAGS = -Wall -std=c++1z -O2

SRCS = $(wildcard *.cpp)
PROGS = $(patsubst %.cpp,%,$(SRCS))

all: $(PROGS)

%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROGS)
