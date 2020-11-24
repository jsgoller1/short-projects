/*
 * grid.c - functions to manage the grid that is eventually drawn to screen
 */

#include <ncurses.h>
#include <string.h>

#include "gol.h"

static coordinates neighbor_cells[] = {
    {1, 0},    // U
    {1, 1},    // UR
    {0, 1},    // R
    {-1, 1},   // DR
    {-1, 0},   // D
    {-1, -1},  // DL
    {0, -1},   // L
    {1, -1}    // UL
};

int count_neighbors(const int y, const int x) {
  int live_neighbors = 0;

  for (int i = 0; i < 8; i++) {
    coordinates current = neighbor_cells[i];
    int neighbor_x = x + current.x;
    int neighbor_y = y + current.y;
    // validate neighbor is within grid boundary
    if (IN_RANGE(neighbor_x, 0, GRID_X) && IN_RANGE(neighbor_y, 0, GRID_Y) &&
        (current_gen[neighbor_y][neighbor_x] == 'X')) {
      live_neighbors++;
    }
  }

  return live_neighbors;
}

void clear_grid() { memset(next_gen, '.', sizeof(char) * GRID_X * GRID_Y); }

void update_grid() {
  memcpy(current_gen, next_gen, sizeof(char) * GRID_X * GRID_Y);
  for (int y = 0; y < GRID_Y; y++) {
    for (int x = 0; x < GRID_X; x++) {
      int live_neighbors = count_neighbors(y, x);
      if (live_neighbors == 3) {
        next_gen[y][x] = 'X';
      } else if (live_neighbors == 2 && current_gen[y][x] == 'X') {
        next_gen[y][x] = 'X';
      } else {
        next_gen[y][x] = '.';
      }
    }
  }
}

void print_grid() {
  for (int y = 0; y < GRID_Y; y++) {
    for (int x = 0; x < GRID_X * 2; x++) {
      if (x % 2 == 0) {
        mvprintw(y, x, "%c", next_gen[y][x / 2]);
      } else {
        mvprintw(y, x, " ", next_gen[y][x]);
      }
    }
  }
}
