.PHONY: force

all: squee-new-database squee-create-table squee-add-row squee-read-database squeectl

clean:
	rm -f squee-new-database file.db squee-structures.o unit/test-squee-structures squeectl squee-add-row squee-create-table squee-read-database
	rm -fr *.dSYM

squee-structures.o: force
	cc -g -c squee-structures.c

squeectl: force squee-structures.o
	cc $@.c -g squee-structures.o -o $@

squee-read-database: force squee-structures.o
	cc $@.c -g squee-structures.o -o $@

squee-add-row: force squee-structures.o
	cc $@.c -g squee-structures.o -o $@

squee-new-database: force squee-structures.o
	cc $@.c -g squee-structures.o -o $@

squee-create-table: force squee-structures.o
	cc $@.c -g squee-structures.o -o $@

test: squee-new-database squee-create-table squee-add-row squee-read-database
	./squee-new-database file.db
	./squee-create-table Employees First_Name 2 Last_Name 2 Age 0 Hourly_Rate 1 file.db
	#./squee-add-row 1 2 3 4 file.db
	./squee-read-database file.db

unit/test-squee-structures: squee-structures.o
	cc -g -I. $@.c squee-structures.o -o $@

unit: unit/test-squee-structures
	./unit/test-squee-structures
