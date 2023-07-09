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

int validInput(int *pn, int *c, int ignoreSign) {
  int signCheck = ignoreSign
    ? *c != '+' && *c != '-'
    : 1;
  char *charType = ignoreSign
    ? "non-alpha"
    : "int";
  if (!isdigit(*c) && *c != EOF && signCheck) {
    printf("Please input a valid, %s character, or quit.\n", charType);
    return 0;
  }
  return 1;
}

int getint(int *pn, int *c) {
  printf("%p\n", (void *)pn);
  int sign;

  while (isspace(*c = getch()));
  if (!validInput(pn, c, 1)) return getint(pn, c);
  sign = (*c == '-') ? -1 : 1;
  if (*c == '+' || *c == '-') {
    printf("'+' or '-' alone is not valid.\n");
    printf("Falling through to next in buffer. ");
    printf("If there is no buffer, please provide a valid string of ints.\n");
    printf("Next number(s): ");
    int tmp = *c;
    while(isspace(*c = getch()));
    printf("\n");
    if (!validInput(pn, c, 0)) {
      ungetch(tmp);
      return getint(pn, c);
    }
  }
  for (*pn = 0; isdigit(*c); *c = getch())
    *pn = 10 * *pn + (*c - '0');

  *pn *= sign;
  if (*c != EOF)
    ungetch(*c);
  return *c;
}

// int getch(void) {
//   int charToInt = (bufp > 0) ? buf[--bufp] : 0;
//   return (charToInt > 0) ? charToInt : getchar();
// }

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
  int n, array[SIZE], c;

  /*
    I've solved some of the undefined behavior that this program had via
    recursion.

    I have older comments and what led me to this solution within test-input.c.
    It may not contain the correctly broken getint with some of my observations,
    but if you want to see different behaviors and come across what I've observed,
    just poke around in that file.

    This file's print logic could be cleaned up, possibly with some clever use or
    abuse on memory or other methods.
  */

  for (n = 0; n < SIZE && getint(&array[n], &c) != EOF; n++);
  for (int i = 0; i < n; i++) {
    printf("Recorded input at index %i: %i\n", i, array[i]);
  }

  printfCharArr(buf);
}

int main() {
  swapExample();
  getintExample();
  return 0;
}
