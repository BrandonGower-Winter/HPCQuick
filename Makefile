#HPC Makefile
UNAME_S := $(shell uname -s)

COMPILER = gcc
FLAGS = -fopenmp
FILES = $(shell find src/ -name "*.c")
APP_NAME = bin/quick

all: main

main: $(FILES)
	$(COMPILER) $(FLAGS) $(FILES) -o $(APP_NAME)

clean:
	rm $(APP_NAME)

