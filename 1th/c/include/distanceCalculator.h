
#ifndef DISTANCE_CALCULATOR_H
#define DISTANCE_CALCULATOR_H

#include <stddef.h>

// Function to calculate the total distance between two arrays
// Parameters:
// - leftArray: Pointer to the first array (left list)
// - rightArray: Pointer to the second array (right list)
// - length: Number of elements in both arrays (must be the same length)
// Returns:
// - Total distance as an integer
int calculateTotalDistance(const int *leftArray, const int *rightArray,
                           size_t length);

// Function to calculate the similarity between two arrays
// Parameters:
// - leftArray: Pointer to the first array (left list)
// - leftLength: Number of elements in the left array
// - rightArray: Pointer to the second array (right list)
// - rightLength: Number of elements in the right array
// Returns:
// - Similarity score as a long
long calculateSimilarity(const int *leftArray, size_t leftLength,
                         const int *rightArray, size_t rightLength);

#endif // DISTANCE_CALCULATOR_H
