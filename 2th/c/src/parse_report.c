
#include "parse_report.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int parse_report(const char *line, int *levels, int maxLevels) {
  int count = 0;
  char *lineCopy = strdup(line);           // Duplicate line for tokenization
  char *token = strtok(lineCopy, " \t\n"); // Tokenize with whitespace

  while (token) {
    if (count >= maxLevels) {
      free(lineCopy);
      return -1; // Too many levels
    }
    char *endptr;
    int value = strtol(token, &endptr, 10);
    if (*endptr != '\0') { // Ensure token is numeric
      free(lineCopy);
      return -1; // Malformed input
    }
    levels[count++] = value;
    token = strtok(NULL, " \t\n");
  }

  free(lineCopy);
  return count > 0 ? count : -1; // Return -1 for empty lines
}
