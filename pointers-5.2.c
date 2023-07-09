#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 10

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);

void printfCharArr(char arr[]) {
  int i = 0;
  printf("[ ");
  // while (arr[i] != '\0') {
  //   char *suffix = (i == 0) ? "" : ", ";
  //   printf("%s%i", suffix, arr[i]);
  // }
  printf("%s", arr);
  printf(" ]\n");
}

void swap(int *px, int *py) {
  int tmp = *px;
  *px = *py;
  *py = tmp;
}

void swapExample() {
  int x = 3;
  int y = 5;
  printf("x: %i, y: %i\n", x, y);
  swap(&x, &y);
  printf("x: %i, y: %i\n", x, y);
}

int getint(int *pn) {
  printf("%p\n", (void *)pn);
  return 0;
  int c, sign;

  while (isspace(c = getch()));
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    // if (!isalpha(c)) ungetch(c);
    if (isalpha(c))
      ungetch(0);
    else
      ungetch(c);
    printf("%i\n", c);
    printf("%s\n", buf);
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
    c = getch();
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');

  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

void getintExample() {
  const int SIZE = 10;
  int n, array[SIZE];
  // for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++);
  // for (n = 0; n < SIZE; n++) {
  //   int *ap = &array[n];
  //   printf("ptr: %p\n", ap);
  //   getint(ap);
  // };
  for (n = 0; n < sizeof(array) / sizeof(array[0]); n++) {
    printf("Recorded input: %i\n", array[n]);
    printf("Addressed at: %p\n", (void *)&array[n]);
  }
  printf("Address of arr name: %p\n", (void *)&array);
  printfCharArr(buf);
}

int main() {
  swapExample();
  getintExample();
  return 0;
}
