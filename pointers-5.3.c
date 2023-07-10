#include <stdio.h>

void basicArrPtrRels() {
  int a[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10
  };
  int *pa;
  int *tpa;
  int x;

  pa = &a[0];

  x = *pa;
  tpa = a;

  printf("x: %i\n", x);
  printf("a[0]: %i\n", a[0]);
  printf("*(pa+1): %i\n", *(pa+1));
  printf("tpa: %i\n", *tpa);
  printf("The pointers 'pa' and 'tpa' will have the same behavior if set to zeroth index. ");
  printf("If set at a further index, OOB & negative indexing is possible and need to be ");
  printf("handled as such.\n");
  printf("*(a+1): %i\n", *(a+1));
  printf("&a[1]: %p\n", (void *) &a[1]);
  printf("a + 1: %p\n", (void *) (a + 1));

  /*
    Can do on pointers that point to array names:
      pa = a
      pa++

    Array names are not variables, so the following is not possible:
      a = pa
      a++
  */
}

int strlen(char *s) {
  /*
    As formal params, char *s and char s[]
    are equivalent.char *s is preferred.
  */
  int n;

  for (n = 0; *s != '\0'; s++)
    n++;

  return n;
}

void strlenExamples() {
  char charr[100], *ptr = charr;
  charr[0] = 'd', charr[1] = 'o',
    charr[2] = 'o', charr[3] = 'p';
  int direct = strlen("Hello, World!");
  int charrIn = strlen(charr);
  int charrPtr = strlen(ptr);
  printf("direct: %i\ncharrIn: %i\ncharrPtr: %i\n", direct, charrIn, charrPtr);
}

void arrAccess(int *xp) {
  printf("*xp: %i\n", *xp);
}

void arrAccess2(int xp[]) {
  printf("*xp: %i\n", *xp);
}

void arrPass() {
  int arr[] = {
    1, 2, 3, 4, 5
  };
  arrAccess(&arr[1]);
  arrAccess2(&arr[1]);
  arrAccess(arr + 1);
  arrAccess2(arr + 1);
}

void negIndx() {
  int arr[] = {
    1, 2, 3, 4, 5, 6
  };
  printf("int *ap = &arr[3];\n");
  int *ap = &arr[3];

  printf("arr[3]: %i\n", arr[3]);
  printf("ap[0]: %i\n", ap[0]);
  printf("arr[0]: %i\n", arr[0]);
  printf("ap[-3]: %i\n", ap[-3]);
}

int main() {
  basicArrPtrRels();
  strlenExamples();
  arrPass();
  negIndx();
  return 0;
}
