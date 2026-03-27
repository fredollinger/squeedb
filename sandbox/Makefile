.PHONY: force

all: squee-new

clean:
	rm -f squee-new file.db squee-structures.o unit/test-squee-structures

squee-structures.o:
	cc -c squee-structures.c

squee-new: force squee-structures.o
	cc squee-new.c squee-structures.o -o squee-new

test: squee-new
	./squee-new column1 column2 column3 file.db

unit/test-squee-structures: squee-structures.o
	cc -I. unit/test-squee-structures.c squee-structures.o -o unit/test-squee-structures

unit: unit/test-squee-structures
	./unit/test-squee-structures
