.PHONY: force

all: squee-new

clean:
	rm -f squee-new file.db squee-structures.o

squee-structures.o:
	cc -c squee-structures.c

squee-new: force squee-structures.o
	cc squee-new.c squee-structures.o -o squee-new

test: squee-new
	./squee-new column1 column2 column3 file.db
