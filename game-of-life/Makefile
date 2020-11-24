### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
ANALYZER:=scan-build

### Uncomment this to do memory leak analysis while running; this makes tests run (slightly) slower
# VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

### Compiler settings
CC:=clang
CFLAGS :=-std=gnu11 -g -lm -lncurses # NOTE: -v shows all paths Clang searches for headers
WARNINGS :=-Weverything -Werror
INCLUDE :=-I gol.h
SRC :=*.c
OUT :=gol
COMPILE:=$(ANALYZER) $(CC) $(CFLAGS) $(WARNINGS) $(INCLUDE) $(SRC) -o $(OUT)

all: gosper-stable

clean:
	-$(RM) $(OUT)
	-$(RM) -r $(OUT)

gol: clean
	reset
	$(COMPILE)

stills: gol
	./$(OUT) --block --beehive --loaf --boat --tub

oscillators: gol
	./$(OUT) --blinker --toad --beacon

ships: gol
	./$(OUT) --glider --lwss

pulsar: gol
	./$(OUT) --pulsar

penta: gol
	./$(OUT) --penta

gosper-unstable: gol
	./$(OUT) --gosper-unstable

gosper-stable: gol
	./$(OUT) --gosper-stable

%.svg:
	termtosvg $@ -t window_frame -g 110x40 -c "./$(OUT) --$*"

deps:
	pip3 install --user termtosvg
