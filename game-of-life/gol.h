#include <unistd.h>

#define BOX_SIZE 6
#define GRID_Y 9 * BOX_SIZE
#define GRID_X 9 * BOX_SIZE

#define IN_RANGE(x, low, high) ((low <= x) && (x < high))

extern char current_gen[GRID_Y][GRID_X];
extern char next_gen[GRID_Y][GRID_X];

typedef struct coordinates {
  int y;
  int x;
} coordinates;

// input.c
useconds_t parse_input(const int argc, char* const* const argv);

// grid.c
int count_neighbors(const int x, const int y);
void update_grid(void);
void print_grid(void);
void clear_grid(void);

// seed.c
void seed_block(const int x, const int y);
void seed_beehive(const int x, const int y);
void seed_loaf(const int x, const int y);
void seed_boat(const int x, const int y);
void seed_tub(const int x, const int y);

void seed_blinker(const int x, const int y);
void seed_toad(const int x, const int y);
void seed_beacon(const int x, const int y);

void seed_glider(const int x, const int y);
void seed_lwss(const int x, const int y);

void seed_pulsar(const int x, const int y);
void seed_penta(const int x, const int y);
void seed_gosper_unstable(const int x, const int y);
void seed_gosper_stable(const int x, const int y);
