.PHONY: force

CC=clang

all: squee-new-database squee-create-table squee-add-row squee-read-database squeectl

clean:
	rm -f squee-new-database file.db squee-structures.o unit/test-squee-structures squeectl squee-add-row squee-create-table squee-read-database smoke/test-squee-database
	rm -fr *.dSYM
	cd smoke && rm -fr *.dSYM

squee-structures.o: force
	${CC} -g -c squee-structures.c

squeectl: force squee-structures.o
	${CC} $@.c -g squee-structures.o -o $@

squee-read-database: force squee-structures.o
	${CC} $@.c -g squee-structures.o -o $@

squee-add-row: force squee-structures.o
	${CC} $@.c -g squee-structures.o -o $@

squee-new-database: force squee-structures.o
	${CC} $@.c -g squee-structures.o -o $@

squee-create-table: force squee-structures.o
	${CC} $@.c -g squee-structures.o -o $@

row: squee-add-row
	./squee-add-row John Doe 42 4.25 file.db

print: squee-read-database
	./squee-read-database file.db

test: squee-new-database squee-create-table squee-add-row squee-read-database
	./squee-new-database file.db
	./squee-create-table Employees First_Name 2 Last_Name 2 Age 0 Hourly_Rate 1 file.db
	./squee-add-row John Doe 42 4.25 file.db
	./squee-read-database file.db

unit/test-squee-structures: squee-structures.o
	${CC} -g -I. $@.c squee-structures.o -o $@

smoke/test-squee-database: squee-structures.o force
	${CC} -g -I. $@.c squee-structures.o -o $@

unit: unit/test-squee-structures
	./unit/test-squee-structures

smoke: smoke/test-squee-database
	lldb ./smoke/test-squee-database
	#./smoke/test-squee-database
