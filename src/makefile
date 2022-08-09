all:numscale

vpath %.h ../inc:./
CC := g++
CXXFLAGS := -std=gnu++2a -g -Wall -I../inc -I./

%.o:%.cc
	$(CC) $(CXXFLAGS) -o $@ -c $<

numscale:numscale.o
	$(CC) $(CXXFLAGS) -o $@ $<

.PHONY:numsabs-test clean

numsabs-test:numsabs-test.o
	$(CC) $(CCFLAGS) -o $@ $<

numsabs-test.o:numsabs-test.cc numsabs.tcc

clean:
	@rm -f *.o


