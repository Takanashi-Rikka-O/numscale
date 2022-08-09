all:numscale

EXECFILE_DIR := src/

numscale:
	cd src;     		\
	make;       		\
	make clean 		
	mv $(EXECFILE_DIR)$@ bin/

.PHONY:numscale-test

numscale-test:
	cd src;			\
	make numscale-test;	\
	make clean		
	mv $(EXECFILE_DIR)$@ bin/
