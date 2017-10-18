CC = g++-7.1.0
CFLAGS = -Wall -std=c++1z -O2 -DNDEBUG -I..

SRCS = $(wildcard *.cpp)
PROGS = $(patsubst %.cpp,%,$(SRCS))

all: $(PROGS)

%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROGS)
