
#ifndef SAFETY_CHECK_H
#define SAFETY_CHECK_H

#include <stdbool.h>

// Checks if a report is safe
bool is_safe_report(const int *levels, int count);

// Checks if a report can be made safe using the dampener
bool is_safe_with_dampener(const int *levels, int count);

#endif
