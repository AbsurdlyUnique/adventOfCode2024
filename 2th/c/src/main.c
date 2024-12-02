
#include "parse_report.h"
#include "safety_check.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEVELS 100

int main() {
  const char *filePath = "input.txt";
  int safeCountPart1 = 0, safeCountPart2 = 0;

  // Open input file
  FILE *file = fopen(filePath, "r");
  if (!file) {
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  char line[1024];
  int reportIndex = 1; // Keep track of the report number
  while (fgets(line, sizeof(line), file)) {
    int levels[MAX_LEVELS];
    int count = parse_report(line, levels, MAX_LEVELS);

    if (count == -1) {
      fprintf(stderr, "Error: Report %d has invalid input\n", reportIndex);
      reportIndex++;
      continue; // Skip to next report
    }

    // Check if the report is safe
    if (is_safe_report(levels, count)) {
      printf("Report %d: Safe\n", reportIndex);
      safeCountPart1++;
      safeCountPart2++;
    } else if (is_safe_with_dampener(levels, count)) {
      printf("Report %d: Unsafe, but can be made safe\n", reportIndex);
      safeCountPart2++;
    } else {
      printf("Report %d: Unsafe\n", reportIndex);
    }

    reportIndex++;
  }

  fclose(file);

  printf("Part 1: Total Safe Reports: %d\n", safeCountPart1);
  printf("Part 2: Total Safe or Dampened Reports: %d\n", safeCountPart2);
  return EXIT_SUCCESS;
}
