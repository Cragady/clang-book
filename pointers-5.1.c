#include <stdio.h>

void bustedPrintfFullIntArray(int arr[]) {
  // This cannot know the lenght of the array if passed without length param
  unsigned long length = sizeof(&arr) / sizeof(arr[0]);
  printf("length looks to be: %lu\n", length);
  printf("size of arr: %lu\n", sizeof(&arr));
  printf("size of arr[0]: %lu\n", sizeof(arr[0]));
  printf("last element hard coded: %i\n", arr[9]);
  for (int i = 0; i < length; i++) {
    char *commaSuffix = (i < length - 1) ? ", " : ""; // char commaSuffix[] expected an initializer, not an expression
    // char commaSuffix[] = ", ";
    if (i == 0) printf("[ ");
    printf("%i%s", arr[i], commaSuffix);
    if (i == length - 1) printf(" ]\n");
  }
}

void printfFullIntArray(int arr[], int length) {
  for (int i = 0; i < length; i++) {
    char *commaSuffix = (i < length - 1) ? ", " : "";
    if (i == 0) printf("[ ");
    printf("%i%s", arr[i], commaSuffix);
    if (i == length - 1) printf(" ]\n");
  }
}

void firstChunk() {
  int x = 1, y = 2, z[10];
  int *ip; // pointer to int
  printf("Initial 'ip' address: %p\n\n", (void *)ip);
  // printf("%d\n", *ip); // will cause seg fault on Ubuntu due to *ip not being initialized with a value

  ip = &x; // ip pointing to x
  printf("New 'ip' pointer (to x address): %p\n", (void *)ip);
  printf("Pointer of 'x': %p\nValue of 'x': %i\n", (void *)&x, x);
  printf("Value of 'ip' (x value): %i\n\n", *ip);
  printf("y address: %p y value: %i\n", (void *)&y, y);
  y = *ip; // y = 1
  printf("y address after assignment: %p\n", (void *)&y);
  printf("New 'y' value: %i\n", y);
  y = 3;
  printf("'y' reassignment: %i\n'ip' val: %i\n'ip' pointer: %p\n\n", y, *ip, (void *)ip);
  *ip = 0; // x = 0
  printf("'x val with '*ip = 0' (same address): %i\n\n", x);
  ip = &z[0]; // ip pointing to z[0]
  printf("'z[0]' address: %p\n", (void *)&z[0]);
  printf("'ip' pointing to 'z[0]', address: %p\n", (void *)ip);
  printf("'ip' as 'z', address: %p\n", (void *)&ip[0]);
  // probs don't do the below lol
  // int *test = (int *)0x7fff1ac47fa4;
  // printf("Manual assignment of 'test' pointer to address: 0x7fff1ac47fa4 - %p\n", test);
}

void secondChunk() {
  int x = 1, y = 2,
    z[] = {
      1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };
  unsigned long zLen = sizeof(z) / sizeof(z[0]);
  double *dp, atof(char *); // double ptr & func decl that takes char ptr as arg
  int *ip; // pointer to int
  ip = &z[0];
  // printf("'z' is %i\n", *z);
  printfFullIntArray(z, zLen);
  *ip = *ip + 10;
  y = *ip + 1;
  printf("\nip val: %i\n", *ip);
  printf("y val: %i\n", y);
  *ip += 1;
  printf("ip val: %i, ip ptr: %p\n", *ip, (void *)ip);
  ++*ip;
  (*ip)++;
  printf("ip val (two more than prev): %i\n", *ip);
  int *iq = ip;
  *iq++;
  printf("One address val after ip in arr (in iq): %i\n", *iq);
  printf("Before some ptr arithmetics: %i\n", *iq);
  // This increments what is pointed to before moving the ptr
  (*iq++)++;
  printf("New iq: %i\n", *iq);
  printfFullIntArray(z, zLen);
}

int main () {
  firstChunk();
  secondChunk();
  return 0;
}
