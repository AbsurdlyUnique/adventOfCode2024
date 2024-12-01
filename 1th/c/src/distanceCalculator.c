
#include "distanceCalculator.h"
#include <stdio.h>  // For NULL
#include <stdlib.h> // For qsort, malloc, abs, calloc

// Helper function to compare two integers for qsort
static int compareIntegers(const void *a, const void *b) {
  return (*(int *)a - *(int *)b);
}

// Function to calculate the total distance between two arrays
int calculateTotalDistance(const int *leftArray, const int *rightArray,
                           size_t length) {
  // Allocate memory for sorted copies of the arrays
  int *sortedLeftArray = (int *)malloc(length * sizeof(int));
  int *sortedRightArray = (int *)malloc(length * sizeof(int));

  // Check if memory allocation was successful
  if (sortedLeftArray == NULL || sortedRightArray == NULL) {
    free(sortedLeftArray);
    free(sortedRightArray);
    return -1;
  }

  // Copy the input arrays into the allocated memory
  for (size_t i = 0; i < length; i++) {
    sortedLeftArray[i] = leftArray[i];
    sortedRightArray[i] = rightArray[i];
  }

  // Sort both arrays in ascending order
  qsort(sortedLeftArray, length, sizeof(int), compareIntegers);
  qsort(sortedRightArray, length, sizeof(int), compareIntegers);

  // Calculate the total distance
  int totalDistance = 0;
  for (size_t i = 0; i < length; i++) {
    totalDistance += abs(sortedLeftArray[i] - sortedRightArray[i]);
  }

  // Free the allocated memory
  free(sortedLeftArray);
  free(sortedRightArray);

  // Return the total distance
  return totalDistance;
}

// Function to calculate the similarity between two arrays
long calculateSimilarity(const int *leftArray, size_t leftLength,
                         const int *rightArray, size_t rightLength) {
  // Find the maximum value in the right array to size the frequency table
  int maxValue = 0;
  for (size_t i = 0; i < rightLength; i++) {
    if (rightArray[i] > maxValue) {
      maxValue = rightArray[i];
    }
  }

  // Allocate and initialize a frequency table for the right array
  int *frequency = (int *)calloc(maxValue + 1, sizeof(int));
  if (frequency == NULL) {
    return -1; // Return error code for memory allocation failure
  }

  // Populate the frequency table
  for (size_t i = 0; i < rightLength; i++) {
    frequency[rightArray[i]]++;
  }

  // Calculate the similarity score
  long similarity = 0;
  for (size_t i = 0; i < leftLength; i++) {
    if (leftArray[i] <= maxValue) {
      similarity += leftArray[i] * frequency[leftArray[i]];
    }
  }

  // Free the frequency table
  free(frequency);

  return similarity;
}
