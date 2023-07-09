#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 1024

char buf[BUFSIZE];
char bufp = 0;

int getch(void) {
  return (bufp > 0) ? buf[--bufp] : getchar();
}

int getch2(void) {
  int charToInt = (bufp > 0) ? buf[--bufp] : 0;
  return (charToInt > 0) ? charToInt : getchar();
}

void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
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

void brokenGetint() {
  /*
    This is an older example that had undefined behavior pending
    certain inputs. I _partially_ fixed it to how I think it should
    run, but I want to keep the original function and comments here to
    document my learnings.
  */

  const int SIZE = 10;
  int n, array[SIZE];
  // getint returned 0, I'll be returning EOF to terminate the program
  // when the array is read with nothing defined, undefined behavior happens.
  // It appears to be an overflow of some point, I'm uncertain if the
  // output has to do with the memory addresses, as the output changes almost
  // randomly with somewhat stable values (almost?). I don't know enough about
  // accessing memory, memory overflowing, how a pointer can return a value
  // in some circumstances when space has been allocated but not defined/initialized,
  // and how to tell what that value can be. Initially, I had assumed that the pointers
  // were returning their own memory addresses and overflowing the 'int' data type,
  // but the math on the conversion + simulated overflow that I had checked both with
  // code and a calculator didn't support that thought process. There are some missing
  // gaps in my knowledge, or this is just "undefined behavior" as the C commmunity
  // coins it.
  for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++);
  // The below provides different output pre-fix, but I still think it may have to do
  // with memory and overflowing. This may be due to different allocation due to the
  // program being compiled differently.
  // for (n = 0; n < SIZE; n++) {
  //   int *ap = &array[n];
  //   printf("ptr: %p\n", ap);
  //   getint(ap);
  // };
  // for (n = 0; n < sizeof(array) / sizeof(array[0]); n++) { // old way - undefined behavior
  for (int i = 0; i < n; i++) { // still undefined behavior
    printf("Recorded input at index %i: %i\n", i, array[i]);
    // printf("Addressed at: %p\n", (void *)&array[i]);
  }
  // printf("Address of arr name: %p\n", (void *)&array);
  printfCharArr(buf);
}

int getintDebug(int *pn, int *c) {
  while(isspace(*c = getch()));
  // str = (char *)charToInt;
  printf("isalpha: %i\n", isalpha(*c));
  printf("c is: %i\n", *c);
  if (isalpha(*c)) return getintDebug(pn, c);
  printf("c is: %i\n", *c);
  printf("%s", buf);
  return *c;
}

int main() {
  int *ip;
  int c;

  while(!getintDebug(ip, &c));

  printf("%i\n", c);
  return 0;
}
