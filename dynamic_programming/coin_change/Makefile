CC = g++
CFLAGS = -Wall -Werror -std=c++1z -O2 -DNDEBUG

SRCS = $(wildcard *.cpp)
PROGS = $(patsubst %.cpp,%,$(SRCS))

all: $(PROGS)

%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROGS)
