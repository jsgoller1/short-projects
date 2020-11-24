#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "gol.h"

static char helpstring[] =
    "patterns can be individually added with the below switches:\n"
    "still lifes: --block, --beehive, --loaf, --boat --tub\n"
    "oscillators: --blinker, --toad, --beacon\n"
    "spaceships: --glider --lwss\n"
    "big: --penta --pulsar\n"
    "guns: --gosper-stable --gosper-unstable\n";

useconds_t parse_input(const int argc, char *const *const argv) {
  int y = 0;
  int x = 0;
  if (argc == 1) {
    printf("%s\n", helpstring);
    return 0;
  }

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--help") == 0) {
      printf("%s\n", helpstring);
      return 0;
    } else if (strcmp(argv[i], "--block") == 0) {
      seed_block(y, x);
    } else if (strcmp(argv[i], "--beehive") == 0) {
      seed_beehive(y, x);
    } else if (strcmp(argv[i], "--loaf") == 0) {
      seed_loaf(y, x);
    } else if (strcmp(argv[i], "--boat") == 0) {
      seed_boat(y, x);
    } else if (strcmp(argv[i], "--tub") == 0) {
      seed_tub(y, x);
    } else if (strcmp(argv[i], "--blinker") == 0) {
      seed_blinker(y, x);
    } else if (strcmp(argv[i], "--toad") == 0) {
      seed_toad(y, x);
    } else if (strcmp(argv[i], "--beacon") == 0) {
      seed_beacon(y, x);
    } else if (strcmp(argv[i], "--glider") == 0) {
      seed_glider(y, x);
    } else if (strcmp(argv[i], "--lwss") == 0) {
      seed_lwss(y, x);
    } else if (strcmp(argv[i], "--gosper-unstable") == 0) {
      clear_grid();
      y = 0;
      x = 0;
      seed_gosper_unstable(y, x);
      return 100000;
    } else if (strcmp(argv[i], "--gosper-stable") == 0) {
      clear_grid();
      y = 0;
      x = 0;
      seed_gosper_stable(y, x);
      return 100000;
    } else if (strcmp(argv[i], "--pulsar") == 0) {
      clear_grid();
      y = 0;
      x = 0;
      seed_pulsar(y, x);
      return 100000;
    } else if (strcmp(argv[i], "--penta") == 0) {
      clear_grid();
      y = 0;
      x = 0;
      seed_penta(y, x);
      return 100000;
    } else {
      fprintf(stderr, "Invalid pattern: %s. Quitting...\n", argv[i]);
      return 0;
    }
    x += BOX_SIZE;
    if (x == GRID_X) {
      x = 0;
      y += BOX_SIZE;
    }
    if (y == GRID_Y) {
      fprintf(stderr, "Too many arguments; exiting...\n");
      return 0;
    }
  }

  return 250000;
}
