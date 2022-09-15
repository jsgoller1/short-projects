typedef struct quadratic_solutions {
  int solutions_n;
  double sol1;
  double sol2;
} quadratic_solutions;

quadratic_solutions get_quadratic_solutions(double a, double b, double c);
