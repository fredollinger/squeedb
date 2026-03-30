.PHONY: force

all: squee-new-database squee-new-table

clean:
	rm -f squee-new-database file.db squee-structures.o unit/test-squee-structures

squee-structures.o:
	cc -c squee-structures.c

squee-new-database: force squee-structures.o
	cc $@.c squee-structures.o -o $@

squee-new-table: force squee-structures.o
	cc $@.c squee-structures.o -o $@

test: squee-new-database squee-new-table
	./squee-new-database file.db
	./squee-new-table column1 column2 column3 column4 file.db

unit/test-squee-structures: squee-structures.o
	cc -I. $@.c squee-structures.o -o $@

unit: unit/test-squee-structures
	./unit/test-squee-structures
