.PHONY: force

all: squee-new-database squee-create-table squee-add-row squeectl

clean:
	rm -f squee-new-database file.db squee-structures.o unit/test-squee-structures squeectl squee-add-row squee-create-table
	rm -fr *.dSYM

squee-structures.o: force
	cc -g -c squee-structures.c

squeectl: force squee-structures.o
	cc $@.c -g squee-structures.o -o $@

squee-add-row: force squee-structures.o
	cc $@.c -g squee-structures.o -o $@

squee-new-database: force squee-structures.o
	cc $@.c -g squee-structures.o -o $@

squee-create-table: force squee-structures.o
	cc $@.c -g squee-structures.o -o $@

test: squee-new-database squee-create-table
	./squee-new-database file.db
	./squee-create-table table_name column1 column2 column3 column4 file.db
	./squee-add-row 1 2 3 4 file.db
	# lldb -- ./squee-create-table column1 column2 column3 column4 file.db

unit/test-squee-structures: squee-structures.o
	cc -g -I. $@.c squee-structures.o -o $@

unit: unit/test-squee-structures
	./unit/test-squee-structures
