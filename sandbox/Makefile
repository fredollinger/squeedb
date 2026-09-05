.PHONY: force

CC=clang
CFLAGS += -g -O0 -wError
#CFLAGS += -g -O0 -fsanitize=address -fno-omit-frame-pointer
#LDFLAGS += -fsanitize=address

all: squee-new-database squee-create-table squee-add-row squee-read-database squeectl

clean:
	rm -f squee-new-database file.db file2.db smoke.db squee-structures.o unit/test-squee-structures squeectl squee-add-row squee-create-table squee-read-database smoke/test-squee-database
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
	./squee-create-table Employees First_Name CHAR Last_Name CHAR Age INT Hourly_Rate FLOAT file.db
	./squee-add-row John Doe 42 4.25 file.db
	./squee-read-database file.db

unit/test-squee-structures: squee-structures.o
	${CC} -g -I. $@.c squee-structures.o -o $@

smoke/test-squee-database: squee-structures.o force
	${CC} -g -I. $@.c squee-structures.o -o $@

unit: unit/test-squee-structures
	./unit/test-squee-structures

smoke: smoke/test-squee-database
	#lldb ./smoke/test-squee-database
	./smoke/test-squee-database

lib:
	clang -Wall -Wextra -g -fPIC -c squee-structures.c -o squee-structures.o
	clang -shared -o libsquee.so squee-structures.o
