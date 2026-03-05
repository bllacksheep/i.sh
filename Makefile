PATHBD := build
PATHBN := bin
PATHUN := unity/src
PATHRT := build/results
CFLAGS := -I$(PATHUN) -ggdb3 -O0
CC := gc
EXE := i.sh
PATHS := $(PATHBD) $(PATHBN) $(PATHRT)

.PHONY: setup all clean

all: $(PATHBN)/$(EXE)

$(PATHBN)/$(EXE): main.c
	$(CC) $(CFLAGS) main.c -o $(PATHBN)/$(EXE)

setup:
	mkdir -p $(PATHS)

clean:
	rm -rf $(PATHBN)/* $(PATHBD)/*.o $(PATHRT)/*
