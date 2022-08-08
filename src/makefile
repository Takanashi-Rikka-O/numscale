all:numscale.o

vpath %.h ../inc
CC := g++
CXXFLAGS := -std=gnu++2a -g -Wall -I../inc -I./

numscale.o:numscale.cc
	$(CC) $(CXXFLAGS) -o $@ -c $<



.PHONY:numsabs-test clean
numsabs-test:numsabs-test.o
	$(CC) $(CCFLAGS) -o $@ $<

numsabs-test.o:numsabs-test.cc numsabs.tcc
	$(CC) $(CXXFLAGS) -o $@ -c $<

clean:
	@rm -f *.o


