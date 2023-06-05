CC= gcc  
CFLAGS= -Wall -std=c99 -g -lm -lgsl -lgslcblas
SOURCES=  main.c spread.c read.c utils.c output.c

.PHONY: all
all: basic verbose

.PHONY: basic
basic:
	$(CC) $(SOURCES) $(CFLAGS) -o sir

.PHONY: verbose
verbose:
	$(CC) -DVERBOSE $(SOURCES) $(CFLAGS) -o sir_verbose
