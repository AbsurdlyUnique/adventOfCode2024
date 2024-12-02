
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

void print_error(const char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}
