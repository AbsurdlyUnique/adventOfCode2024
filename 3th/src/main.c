
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if a string represents a valid 'mul(X,Y)' instruction
int isValidMul(const char *str, long long *num1, long long *num2) {
  // Check if the string starts with "mul("
  const char *prefix = "mul(";
  if (strncmp(str, prefix, 4) != 0) {
    return 0; // Not a valid mul instruction
  }

  // Extract the numbers within the parentheses
  const char *start = str + 4; // Skip "mul("
  char *end;
  *num1 = strtoll(start, &end, 10); // Parse the first number

  // Check for the comma separator
  if (*end != ',') {
    return 0; // Invalid format
  }

  // Parse the second number
  start = end + 1; // Move past the comma
  *num2 = strtoll(start, &end, 10);

  // Check for the closing parenthesis
  if (*end != ')') {
    return 0; // Invalid format
  }

  return 1; // Valid mul instruction
}

// Function to calculate the sum of all valid 'mul(X,Y)' results from a file
long long calculateSumFromFile(const char *fileName) {
  FILE *file = fopen(fileName, "r"); // Open the file in read mode
  if (file == NULL) {
    perror("Error opening file");
    return -1; // Return error code
  }

  long long totalSum = 0; // Stores the sum of valid results
  long long num1, num2;
  int validInstructionCount = 0; // Count of valid mul instructions

  // Read the file line by line
  char *line = NULL;
  size_t len = 0;
  while (getline(&line, &len, file) != -1) {
    const char *current = line;

    // Iterate through the line to find valid mul instructions
    while (*current) {
      if (isValidMul(current, &num1, &num2)) {
        long long result = num1 * num2; // Calculate the multiplication result
        totalSum += result;             // Add the result to the total sum
        validInstructionCount++; // Increment the count of valid instructions

        // Log the valid instruction
        printf(
            "Instruction %d: mul(%lld, %lld) = %lld | Cumulative Sum: %lld\n",
            validInstructionCount, num1, num2, result, totalSum);

        current = strchr(current, ')') + 1; // Move past the current instruction
      } else {
        current++; // Move to the next character
      }
    }
  }

  free(line);   // Free the allocated memory for the line buffer
  fclose(file); // Close the file

  // Log the final results
  printf("\nSummary:\n");
  printf("Total valid mul instructions found: %d\n", validInstructionCount);
  printf("Final cumulative sum: %lld\n", totalSum);

  return totalSum; // Return the final sum
}

int main() {
  const char *inputFileName = "input.txt"; // Input file name

  // Calculate the sum of all valid mul instructions from the file
  long long result = calculateSumFromFile(inputFileName);

  if (result != -1) {
    printf("\nThe total sum of valid mul instructions is: %lld\n", result);
  }

  return 0;
}
