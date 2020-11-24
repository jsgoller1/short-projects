/*
 * seeds.c - functions that will pre-seed the grid with known
 * Game of Life patterns that have interesting effects.
 *
 * Patterns names and specifications in this file come from
 * https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life#Examples_of_patterns
 */

#include "gol.h"

static int valid_seed_region(const int y, const int x, const int box_size) {
  return IN_RANGE(x, 0, GRID_X) && IN_RANGE(x + box_size, 0, GRID_X) &&
         IN_RANGE(y, 0, GRID_Y) && IN_RANGE(y + box_size, 0, GRID_Y);
}

static void draw_seed(const int y, const int x, const coordinates cells[],
                      const int cells_n) {
  for (int i = 0; i < cells_n; i++) {
    coordinates current = cells[i];
    next_gen[y + current.y][x + current.x] = 'X';
  }
}

/*
 * Still lifes
 */
void seed_block(const int y, const int x) {
  if (!(valid_seed_region(y, x, BOX_SIZE))) {
    return;
  }

  coordinates cells[] = {{1, 1}, {1, 2}, {2, 1}, {2, 2}};
  draw_seed(y, x, cells, 4);
}

void seed_beehive(const int y, const int x) {
  if (!(valid_seed_region(y, x, BOX_SIZE))) {
    return;
  }

  coordinates cells[] = {{1, 2}, {1, 3}, {2, 1}, {2, 4}, {3, 2}, {3, 3}};
  draw_seed(y, x, cells, 6);
}

void seed_loaf(const int y, const int x) {
  if (!(valid_seed_region(y, x, BOX_SIZE))) {
    return;
  }

  coordinates cells[] = {{1, 2}, {1, 3}, {2, 1}, {2, 4},
                         {3, 2}, {3, 4}, {4, 3}};
  draw_seed(y, x, cells, 7);
}

void seed_boat(const int y, const int x) {
  if (!(valid_seed_region(y, x, BOX_SIZE))) {
    return;
  }

  coordinates cells[] = {{1, 1}, {1, 2}, {2, 1}, {2, 3}, {3, 2}};
  draw_seed(y, x, cells, 5);
}

void seed_tub(const int y, const int x) {
  if (!(valid_seed_region(y, x, BOX_SIZE))) {
    return;
  }

  coordinates cells[] = {{1, 3}, {2, 2}, {2, 4}, {3, 3}};
  draw_seed(y, x, cells, 4);
}

/*
 * Oscilators
 */
void seed_blinker(const int y, const int x) {
  if (!(valid_seed_region(y, x, BOX_SIZE))) {
    return;
  }

  coordinates cells[] = {{1, 1}, {2, 1}, {3, 1}};
  draw_seed(y, x, cells, 3);
}

void seed_toad(const int y, const int x) {
  if (!(valid_seed_region(y, x, BOX_SIZE))) {
    return;
  }

  coordinates cells[] = {{2, 2}, {2, 3}, {2, 4}, {3, 1}, {3, 2}, {3, 3}};
  draw_seed(y, x, cells, 6);
}

void seed_beacon(const int y, const int x) {
  if (!(valid_seed_region(y, x, BOX_SIZE))) {
    return;
  }

  coordinates cells[] = {{1, 1}, {1, 2}, {2, 1}, {2, 2},
                         {3, 3}, {3, 4}, {4, 3}, {4, 4}};
  draw_seed(y, x, cells, 8);
}

/*
 * Ships
 */
void seed_glider(const int y, const int x) {
  if (!(valid_seed_region(y, x, BOX_SIZE))) {
    return;
  }

  coordinates cells[] = {{3, 1}, {3, 2}, {3, 3}, {2, 3}, {1, 2}};
  draw_seed(y, x, cells, 5);
}

void seed_lwss(const int y, const int x) {
  if (!(valid_seed_region(y, x, BOX_SIZE))) {
    return;
  }

  coordinates cells[] = {{1, 2}, {3, 2}, {1, 5}, {2, 6}, {3, 6},
                         {4, 6}, {4, 5}, {4, 4}, {4, 3}};
  draw_seed(y, x, cells, 9);
}

/*
 * Big ones
 */
void seed_pulsar(const int y, const int x) {
  if (!(valid_seed_region(y, x, 17))) {
    return;
  }

  coordinates cells[] = {// left horizontals
                         {2, 4},
                         {2, 5},
                         {2, 6},
                         {7, 4},
                         {7, 5},
                         {7, 6},
                         {9, 4},
                         {9, 5},
                         {9, 6},
                         {14, 4},
                         {14, 5},
                         {14, 6},

                         // right horizontals
                         {2, 10},
                         {2, 11},
                         {2, 12},
                         {7, 10},
                         {7, 11},
                         {7, 12},
                         {9, 10},
                         {9, 11},
                         {9, 12},
                         {14, 10},
                         {14, 11},
                         {14, 12},

                         // top verticals
                         {4, 2},
                         {5, 2},
                         {6, 2},
                         {4, 7},
                         {5, 7},
                         {6, 7},
                         {4, 9},
                         {5, 9},
                         {6, 9},
                         {4, 14},
                         {5, 14},
                         {6, 14},

                         // bottom verticals
                         {10, 2},
                         {11, 2},
                         {12, 2},
                         {10, 7},
                         {11, 7},
                         {12, 7},
                         {10, 9},
                         {11, 9},
                         {12, 9},
                         {10, 14},
                         {11, 14},
                         {12, 14}};
  draw_seed(y, x, cells, 4 * 12);
}

void seed_penta(const int y, const int x) {
  if (!(valid_seed_region(y, x, 17))) {
    return;
  }

  coordinates cells[] = {{3, 4},  {3, 5},  {3, 6},  {4, 5},  {5, 5},  {6, 4},
                         {6, 5},  {6, 6},  {8, 4},  {8, 5},  {8, 6},  {9, 4},
                         {9, 5},  {9, 6},  {11, 4}, {11, 5}, {11, 6}, {12, 5},
                         {13, 5}, {14, 4}, {14, 5}, {14, 6}};
  draw_seed(y, x, cells, 6 * 3 + 4);
}

void seed_gosper_unstable(const int y, const int x) {
  /*
   * A derped version of Gosper's gun that explodes
   * in a cool way.
   */
  if (!(valid_seed_region(y, x, 40))) {
    return;
  }

  coordinates cells[] = {// 11 x 38
                         // left block (4)
                         {5, 1},
                         {5, 2},
                         {6, 1},
                         {6, 2},
                         // left ring (16)
                         {3, 13},
                         {3, 14},
                         {4, 12},
                         {4, 16},
                         {5, 11},
                         {5, 17},
                         {6, 11},
                         {6, 15},
                         {6, 17},
                         {6, 18},
                         {7, 11},
                         {7, 17},
                         {8, 12},
                         {8, 16},
                         {9, 13},
                         {9, 14},
                         // right sling (12)
                         {1, 25},
                         {2, 23},
                         {2, 25},
                         {3, 21},
                         {3, 22},
                         {4, 21},
                         {4, 22},
                         {5, 21},
                         {5, 22},
                         {6, 23},
                         {6, 25},
                         {7, 25},
                         // right block (4)
                         {3, 37},
                         {3, 36},
                         {4, 37},
                         {4, 36}};
  draw_seed(y, x, cells, 4 + 16 + 12 + 4);
}

void seed_gosper_stable(const int y, const int x) {
  /*
   * Correct implementation of Gosper's gun.
   */
  if (!(valid_seed_region(y, x, 40))) {
    return;
  }

  coordinates cells[] = {// 11 x 38
                         // left block (4)
                         {5, 1},
                         {5, 2},
                         {6, 1},
                         {6, 2},
                         // left ring (16)
                         {3, 13},
                         {3, 14},
                         {4, 12},
                         {4, 16},
                         {5, 11},
                         {5, 17},
                         {6, 11},
                         {6, 15},
                         {6, 17},
                         {6, 18},
                         {7, 11},
                         {7, 17},
                         {8, 12},
                         {8, 16},
                         {9, 13},
                         {9, 14},
                         // right sling (12)
                         {1, 25},
                         {2, 23},
                         {2, 25},
                         {3, 21},
                         {3, 22},
                         {4, 21},
                         {4, 22},
                         {5, 21},
                         {5, 22},
                         {6, 23},
                         {6, 25},
                         {7, 25},
                         // right block (4)
                         {3, 36},
                         {3, 35},
                         {4, 36},
                         {4, 35}};
  draw_seed(y, x, cells, 4 + 16 + 12 + 4);
}
