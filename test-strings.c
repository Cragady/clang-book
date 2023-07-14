#include <stdio.h>
#include <string.h>

void sanityChecking() {
  int equal = strncmp("hello", "hello", 5);
  int less = strncmp("hel", "hello", 5);
  int more = strncmp("hello", "hell", 5);
  printf("sanity: %i\n", equal);
  printf("less: %i\n", less);
  printf("more: %i\n", more);
}

int main() {
  sanityChecking();
  return 0;
}
