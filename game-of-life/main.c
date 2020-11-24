/*
 * main.c - entrypoint for program
 */

#include <ncurses.h>
#include <unistd.h>

#include "gol.h"

char current_gen[GRID_Y][GRID_X] = {{0}};
char next_gen[GRID_Y][GRID_X] = {{0}};

int main(int argc, char** argv) {
  useconds_t sleep_time;
  if ((sleep_time = parse_input(argc, argv)) == 0) {
    return 0;
  }

  // Init ncurses mode, hide cursor
  initscr();
  curs_set(0);

  while (1) {
    update_grid();
    print_grid();
    refresh();
    usleep(sleep_time);
  }

  // End ncurses mode and quit; this never
  // gets accessed, pragma shuts compiler up
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunreachable-code"
  endwin();
  return 0;
#pragma clang diagnostic pop
}
