
#include "safety_check.h"
#include <stdbool.h>
#include <stdlib.h>

// Helper function to check safety after removing one level
static bool is_safe_with_removal(const int *levels, int count) {
  for (int i = 0; i < count; i++) {
    int modifiedLevels[count - 1];
    int idx = 0;

    // Create a new array without the level at index `i`
    for (int j = 0; j < count; j++) {
      if (j != i) {
        modifiedLevels[idx++] = levels[j];
      }
    }

    // Check if the modified report is safe
    if (is_safe_report(modifiedLevels, count - 1)) {
      return true;
    }
  }
  return false;
}

// Function to check if a report is safe
bool is_safe_report(const int *levels, int count) {
  if (count < 2)
    return false; // Reports must have at least two levels

  bool increasing = true, decreasing = true;

  for (int i = 0; i < count - 1; i++) {
    int diff = levels[i + 1] - levels[i];
    if (abs(diff) < 1 || abs(diff) > 3) {
      return false; // Invalid difference
    }
    if (diff > 0)
      decreasing = false;
    if (diff < 0)
      increasing = false;
  }

  return increasing || decreasing;
}

// Function to check if a report is safe or can be made safe by dampener
bool is_safe_with_dampener(const int *levels, int count) {
  if (is_safe_report(levels, count)) {
    return true;
  }
  return is_safe_with_removal(levels, count);
}
