
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if a string represents a valid 'mul(X,Y)' instruction
int isValidMul(const char *str, long long *num1, long long *num2) {
  const char *prefix = "mul(";
  if (strncmp(str, prefix, 4) != 0) {
    return 0; // Not a valid mul instruction
  }

  // Extract the numbers within the parentheses
  const char *start = str + 4;
  char *end;
  *num1 = strtoll(start, &end, 10); // Parse the first number

  if (*end != ',') {
    return 0; // Invalid format
  }

  start = end + 1;
  *num2 = strtoll(start, &end, 10);

  if (*end != ')') {
    return 0; // Invalid format
  }

  return 1; // Valid mul instruction
}

// Function to check for 'do()' and 'don't()' instructions
int isStateChange(const char *str, int *newState) {
  if (strncmp(str, "do()", 4) == 0) {
    *newState = 1; // Enable mul instructions
    return 1;
  } else if (strncmp(str, "don't()", 7) == 0) {
    *newState = 0; // Disable mul instructions
    return 1;
  }
  return 0; // Not a state-changing instruction
}

// Function to calculate the sum of enabled 'mul(X,Y)' instructions
long long calculateSumWithConditions(const char *fileName) {
  FILE *file = fopen(fileName, "r");
  if (file == NULL) {
    perror("Error opening file");
    return -1;
  }

  long long totalSum = 0;
  long long num1, num2;
  int validInstructionCount = 0;
  int currentState = 1; // Start with mul instructions enabled

  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, file) != -1) {
    const char *current = line;

    while (*current) {
      // Check for state change instructions
      int newState;
      if (isStateChange(current, &newState)) {
        currentState = newState; // Update the state
        printf("State change detected: mul instructions are now %s\n",
               currentState ? "ENABLED" : "DISABLED");
        current += (currentState ? 4 : 7); // Move past 'do()' or 'don't()'
      }
      // Check for valid mul instructions only if enabled
      else if (currentState && isValidMul(current, &num1, &num2)) {
        long long result = num1 * num2;
        totalSum += result;
        validInstructionCount++;
        printf(
            "Instruction %d: mul(%lld, %lld) = %lld | Cumulative Sum: %lld\n",
            validInstructionCount, num1, num2, result, totalSum);
        current = strchr(current, ')') + 1;
      } else {
        current++;
      }
    }
  }

  free(line);
  fclose(file);

  printf("\nSummary:\n");
  printf("Total valid mul instructions found: %d\n", validInstructionCount);
  printf("Final cumulative sum: %lld\n", totalSum);

  return totalSum;
}

int main() {
  const char *inputFileName = "input.txt";

  long long result = calculateSumWithConditions(inputFileName);

  if (result != -1) {
    printf("\nThe total sum of enabled mul instructions is: %lld\n", result);
  }

  return 0;
}
