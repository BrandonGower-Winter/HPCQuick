#HPC Makefile
UNAME_S := $(shell uname -s)

COMPILER = gcc
FILES = $(shell find src/ -name "*.c")
APP_NAME = bin/HPCQuick

all: main

main: $(FILES)
	$(COMPILER) $(FILES) -o $(APP_NAME)

clean:
	rm $(APP_NAME)

