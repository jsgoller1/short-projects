game-of-life
---
Simple implementation of [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) with ncurses:

<p align="center"><img src="https://raw.githubusercontent.com/jsgoller1/dabblings/main/game-of-life/gosper-stable.svg"></p>

### Rules:
In an N x M grid of cells, a cell is "alive" if it contains `X` and "dead" if
it contains `.`. On each iteration of the game, every cell is evaluated simultaneously
according to the following rules (a cell's neighbors are any cells adjacent to it,
including diagonals):
 1. Any live cell with fewer than two live neighbors dies, as if by under population.
 2. Any live cell with two or three live neighbors lives on to the next generation.
 3. Any live cell with more than three live neighbors dies, as if by overpopulation.
 4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

### Running
`make gol`. The following [patterns](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Examples_of_patterns) are supported:
- still lifes:
  - `--block`
  - `--beehive`
  - `--loaf`
  - `--boat`
  - `--tub`
- oscillators:
  - `--blinker`
  - `--toad`
  - `--beacon`
- spaceships:
  - `--glider`
  - `--lwss`
- big:
  - `--penta`
  - `--pulsar`
- guns:
  - `--gosper-stable`
  - `--gosper-unstable`

### Requirements
Must have `ncurses`, `clang` and `clang-tools`. Tested on Ubuntu 20.04.

### Special thanks
- ncurses snippet source from [StackOverflow](https://stackoverflow.com/questions/18458064/how-to-refresh-the-screen-continuously-and-update-it-in-real-time)
- @mmcloughlin for generating the GIF in this readme