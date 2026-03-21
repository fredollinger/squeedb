.PHONY: force

all: squee-new

clean:
	rm -f squee-new file.db

squee-new: force
	cc squee-new.c -o squee-new

test: squee-new
	./squee-new column1 column2 file.db
