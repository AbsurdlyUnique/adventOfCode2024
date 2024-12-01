
#include "distanceCalculator.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to read input file and parse data into two arrays
int parseFile(const char *filename, int **leftArray, int **rightArray,
              size_t *length) {
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("Error opening file");
    return -1;
  }

  size_t capacity = 100;
  *leftArray = (int *)malloc(capacity * sizeof(int));
  *rightArray = (int *)malloc(capacity * sizeof(int));

  if (*leftArray == NULL || *rightArray == NULL) {
    fclose(file);
    free(*leftArray);
    free(*rightArray);
    return -1;
  }

  *length = 0;
  int left, right;
  while (fscanf(file, "%d %d", &left, &right) == 2) {
    if (*length >= capacity) {
      capacity *= 2;
      *leftArray = (int *)realloc(*leftArray, capacity * sizeof(int));
      *rightArray = (int *)realloc(*rightArray, capacity * sizeof(int));

      if (*leftArray == NULL || *rightArray == NULL) {
        fclose(file);
        free(*leftArray);
        free(*rightArray);
        return -1;
      }
    }

    (*leftArray)[*length] = left;
    (*rightArray)[*length] = right;
    (*length)++;
  }

  fclose(file);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <part1|part2> <input_file>\n", argv[0]);
    return 1;
  }

  const char *part = argv[1];
  const char *filename = argv[2];

  int *leftArray = NULL;
  int *rightArray = NULL;
  size_t length = 0;

  if (parseFile(filename, &leftArray, &rightArray, &length) != 0) {
    printf("Failed to parse input file.\n");
    return 1;
  }

  if (strcmp(part, "part1") == 0) {
    int totalDistance = calculateTotalDistance(leftArray, rightArray, length);
    if (totalDistance < 0) {
      printf("Error calculating total distance.\n");
      free(leftArray);
      free(rightArray);
      return 1;
    }
    printf("Part 1: Total distance = %d\n", totalDistance);
  } else if (strcmp(part, "part2") == 0) {
    long similarity =
        calculateSimilarity(leftArray, length, rightArray, length);
    if (similarity < 0) {
      printf("Error calculating similarity score.\n");
      free(leftArray);
      free(rightArray);
      return 1;
    }
    printf("Part 2: Similarity score = %ld\n", similarity);
  } else {
    printf("Invalid part. Use 'part1' or 'part2'.\n");
    free(leftArray);
    free(rightArray);
    return 1;
  }

  free(leftArray);
  free(rightArray);
  return 0;
}
