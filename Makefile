TESTS := $(wildcard test_*.c)
PATHBD := build
PATHBN := bin
PATHUN := unity/src
PATHRT := build/results
UNITY := $(PATHUN)/unity.c
RUNNER := runner
CFLAGS := -I$(PATHUN) -ggdb3 -O0
CC := gcc
EXE := i.sh
PATHS := $(PATHBD) $(PATHBN) $(PATHRT)

.PHONY: setup all clean check

all: $(PATHBN)/$(EXE)

check: $(PATHBN)/$(RUNNER)
	./$(PATHBN)/$(RUNNER)

$(PATHBN)/$(EXE): main.c ish.h
	@mkdir -p $(PATHBN)
	$(CC) $(CFLAGS) $< -o $@

$(PATHBN)/$(RUNNER): main.c $(TESTS) $(UNITY)
	@mkdir -p $(PATHBN)
	$(CC) $(CFLAGS) -DTEST $^ -o $@

setup:
	mkdir -p $(PATHS)

clean:
	rm -rf $(PATHBN)/* $(PATHBD)/*.o $(PATHRT)/*
