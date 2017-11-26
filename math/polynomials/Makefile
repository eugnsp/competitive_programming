CC = g++-7.1.0
CFLAGS = -Wall -std=c++1z -O2 -DNDEBUG -I../..
#CFLAGS = -Wall -std=c++1z -O0 -ggdb -D_DEBUG -I../..

SRCS = $(wildcard *.cpp)
PROGS = $(patsubst %.cpp,%,$(SRCS))

all: $(PROGS)

%: %.cpp ../../base.hpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROGS)
