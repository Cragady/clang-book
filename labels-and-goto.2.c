/*
  Cntd. from labels-and-goto.c

  I realize that my stance on 'goto's could potentially be limiting, but without
  seeing proper usage, or seeing a proper need for it, I don't know what proper
  usage looks like. So, with that being said, If Dennis Ritchie does not see a
  huge need for 'goto's, neither do I. For me to comfortably use a 'goto', I
  need to know what it looks like when it's needed, and how to do it cleanly
  (although, I imagine it wouldn't be too difficult, just ensure it's easily
  understandable).

  'jmp's started cropping up when defining and executing recursive function calls.
  This leads me to wonder if having a crazier setup with 'goto's, or other patterns,
  will cause 'jmp's in the asm as well.

  Abandoning searching for other ways to make the asm use 'jmp'. I'll figure that out later.
*/

#include <stdio.h>

void printFoo();
void printBar();
void printBaz();

void secondLevel() {
  printf("I'm in the second level.\n");
}

void topLevel() {
  topSecondLevel:
    secondLevel();
}

int recurseMe(int *xp) {
  // This caused the first non-string and non-comment 'jmp' in the asm
  if (*xp < 2) {
    ++*xp;
    return recurseMe(xp);
  }
  return 1;
}


int ogGoto(int *xp) {
  goto control;

  label_foo:
    printFoo();
    goto fin;
  label_bar:
    printBaz();
    printBar();
    goto label_foo;

  control:
    printBaz();
    goto label_bar;

  fin:
    printf("%i\n", *xp);
    topLevel();
    return 0;
}

void printFoo() {
  printf("I'm in label_foo\n");
}

void printBar() {
  printf("I'm in label_bar\n");
}

void printBaz() {
  printf("Hi, I'm BAZ!!! <3\n");
}

int main() {
  int *xp, x;
  x = 0;
  xp = &x;
  printf("After assignment\n");
  if (recurseMe(xp)) printf("Will 'jmp' happen?\n");
  topLevel();
  ogGoto(xp);
  secondLevel();
  return 0;
}
