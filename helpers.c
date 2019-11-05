#include "helpers.h"

uint64_t S64(const char *s) {
  uint64_t i;
  char c ;
  int scanned = sscanf(s, "%" SCNu64 "%c", &i, &c);
  if (scanned == 1)
  	return i;
  if (scanned > 1)
    return i;
  return 0;  
}
