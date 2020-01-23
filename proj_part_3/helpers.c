#include "helpers.h"
//Convert a string to uint64_t
uint64_t atouint64_t (const char *s) {
// Variables
  uint64_t i = 0;
  int scanned = 0;
  char c;
// Sscanf the string and if its not a number return 0;
  scanned = sscanf(s, "%" SCNu64 "%c", &i, &c);
  if (scanned == 1)
  	return i;
  if (scanned > 1)
    return i;
  return 0;  
}
