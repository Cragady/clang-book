/*
  Skipping 5.4 for now - it may crop up later though.

  5.4 mainly talks about address arithmetics and how that relates
  between pointers and arrays, along with how alloc and afree operate.
  'malloc' and 'free' don't have the constraint of stack order; last-in
  first-out.

  It also touches on NULL (stdio), and how '\0' is null - you can see this in the
  ascii table.

  Other items of importance includes what's valid on pointer arithmetics,
  comparisons, and casts. In pointer arithmetics, pointer manipulations
  take into account the size of the object pointed to.

  5.5 starts touching on string constants, string arrs vs string pointers.
  Basically don't expect to change the value of a str ptr, only its address.
  You can't assign a value to a string arr outside of initialization or
  modifying the values on the indices in the array.

  I will from this point use 'string(s)' and 'string array(s)' interchangeably.

  Null-terminated strings are touted as being the single most catastrophic design
  bug in the history of computing, which C "inherits". Pretty funny. We can take
  advantage of this, and we can see some weird behaviors because of this. Null
  terminated strings can cause unfortunate security issues if not treated with
  care.

  I've mentioned the heartbleed bug, which I know really nothing about. The main
  gist seems to be that a lot of crypto keys were no longer secure? Or you could
  work around null-terminators to get more info from servers/other than should've
  been available. I don't know. That's not the point of this repo, but it is an
  interesting topic to look into later. A simple google search is telling me the
  main affected software is in some outdated versions of OpenSSL. That's pretty
  bad. The logo for heartbleed is pretty sick.
*/

// I'll be including strlen's and other string ops that the book provides
// strlen from 5.4 -can probs just be brought in w/string.h

#include <stdio.h>

int mstrlen(char *s) {
  // pointer arithmetics and pointer manips!
  char *p = s;

  while (*p != '\0')
    p++;

  return p - s;
}

void astrcpy(char *s, char *t) {
  int i;

  while((s[i] = t[i]) != '\0')
    i++;
}

void pstrcpy(char *s, char *t) {
  while ((*s = *t) != '\0') {
    s++;
    t++;
  }
}

void strcpy0(char *s, char *t) {
  while ((*s++ = *t++) != '\0');
}

void mstrcpy(char *s, char *t) {
  while (*s++ = *t++);
}

// strcmp arr
int astrcmp(char *s, char *t) {
  int i;

  for (i = 0; s[i] == t[i]; i++)
    if (s[i] == '\0')
      return 0;

  return s[i] - t[i];
}

// strcmp ptr
int pstrcmp(char *s, char *t) {
  for (; *s == *t; s++, t++)
    if (*s == '\0')
      return 0;

  return *s - *t;
}

void astrcat(char s[], char t[]) {
  int i, j;

  i = j = 0;

  while (s[i] != '\0')
    i++;
  while((s[i++] = t[j++]) != '\0');
}

void pstrcat(char *s, char *t) {
  while(*s++ != '\0');
  *--s;
  while((*s++ = *t++) != '\0');
}

void pushChar(char *s, char val) {
  *s++ = val;
}

char popChar(char *s) {
  return *--s;
}

int strend(char *s, char *t) {
  // TODO: see if there's a better way and/or tersify this
  int i = 0;
  for(; *s != '\0'; i++, s++) {
    // if (t[i] != *s || t[i] == '\0') i = -1; // may need this in some cases
    if (*(t + i) != *s) i = -1;
  }
  return i > 0 && *(t + i) == '\0';
}

char *mstrncpyold(char *s, char *ct, int n) {
  /*
    Copy at most ncharacters of string ct
    to s; return s. Pad with '\0''s (NULL)
    if t has fewer than n characters.
  */
  int ctLen = mstrlen(ct);
  while(n--) {
    *s++ = ctLen > 0
      ? *ct++
      : '\0';
    ctLen--;
  };
  if (*s != '\0' || ctLen == 0) *s++ = '\0';
  return s;
}

char *mstrncpy(char *s, char *ct, int n) {
  while(*ct && n--) {
    *s++ = *ct++;
  }
  // only pad once.
  *s = '\0';
  return s;
}

char *mstrncat(char *s, char *ct, int n) {
  /*
    Concatenate at most n characters of
    string ct to string s, terminate s with
    '\0'; return s
  */
  while(*s++ != '\0');
  *s--;
  while(n-- && (*s++ = *ct++) != '\0');
  *s = '\0';
  return s;
}

int mstrncmp(char *cs, char *ct, int n) {
  /*
    Compare at most n characters of string
    cs to string ct; return < 0 if cs<ct,
    0 if cs==ct, or >0 if cs>ct.
  */
  for(; n-- && *cs == *ct; cs++, ct++) {
    if (*cs == '\0') return 0;
  }
  return *cs - *ct;
}

int getline(char *s, int lim) {
  // TODO: pointerize
  // int c, i;

  // i = 0;
  // while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
  //   s[i++] = c;
  // if (c == '\n')
  //   s[i++] = c;
  // s[i] = '\0';
  // return i;
  return -1;
}

void stringOps() {
  char amessage[] = "heyoo";
  char *pmessage = amessage;
  // char p2message[4];
  char p2message[5];

  p2message[0] = 'd';
  p2message[1] = 'o';
  p2message[2] = 'o';
  p2message[3] = 'p';
  // If you want to see something cool, initialize p2message with length of 4, and
  // comment out the following null assignment. Since the string arr does not have a null
  // terminator defined, printf does not know how to end the string. From what I know
  // of the heartbleed bug, which is mostly coming in from an xkcd comic, behaviors
  // that result from missing a null-terminator, or working your way around a
  // null-terminator, similarly as shown in this comment, is essentially how the
  // heartbleed bug exposes more info than intended. Don't know, could be wrong, but
  // this seems to make sense. More reading on this bug would be necessary to understand
  // the core of the issue. That, and sandboxing a server with the affected technologies
  // implemented and playing around with it.
  p2message[4] = '\0';
  printf("%s\n", pmessage);
  printf("%s\n", p2message); // withouut p2message[4] null assignment, the output is:
  // "doopheyoo". At least on what I've been compiling.

  int amesLen =mstrlen(amessage);
  int p2Len = mstrlen(p2message);
  printf("%i\n", amesLen);
  printf("%i\n", p2Len);
}

void doopDerp() {
  char *doop = "doop";
  char *derp = "derp";

  int acmp = astrcmp(doop, derp);
  int pcmp = pstrcmp(doop, derp);
  int samesies1 = astrcmp(doop, doop);
  int samesies2 = pstrcmp(derp, derp);
  printf("%i %i\n", acmp, pcmp);
  printf("%i %i\n", samesies1, samesies2);
  printf("%s\n%s\n", doop, derp);
}

void stringOps2() {
  char test[50];
  char works[50];

  char *testVal = "This test: ";
  char *worksVal = "works! :D:D";

  pstrcpy(test, testVal);
  pstrcpy(works, worksVal);

  pstrcat(test, works);

  printf("%s\n", test);
  int testLen = mstrlen(test);
  int worksLen = mstrlen(works);
  printf("%i\n", testLen);
  printf("%i\n", worksLen);

  int testEnd = strend(test, works);

  printf("testEnd: %i\n", testEnd);
  printf("%s\n", test);
  pushChar(test + testLen, '<');

  testEnd = strend(test, works);

  printf("testEnd: %i\n", testEnd);
  printf("%s\n", test);
}

void stringOps3() {
  int charLen = 50;
  int targetNum = 18;
  char source[charLen];
  char *target = "Heyoooooo, world <3";

  mstrncpy(source, target, targetNum);
  printf("source: %s\n", source);
  // check to see if NULL filled
  // if there are target - targetNum nulls after values
  // filling worked. Actual output in above print
  // re-ded strncpy to not fill with n values,
  // just one. Also, possible to be one more than length of buffer,
  // ¯\_(ツ)_/¯ it's ok. At least here.
  for (int i = 0; i < targetNum + 1; i++) {
    if (source[i] == '\0') printf("(nil), ");
    else printf("%c, ", source[i]);
  }
  printf("\n%p\n", (void *) 's');
  mstrncat(source, target, targetNum);
  printf("%s\n", source);

  int equal = mstrncmp("hello", "hello", 5);
  int less = mstrncmp("hel", "hello", 5);
  int more = mstrncmp("hello", "hell", 5);
  printf("sanity: %i\n", equal);
  printf("less: %i\n", less);
  printf("more: %i\n", more);
}

int main() {
  stringOps();
  doopDerp();
  stringOps2();
  stringOps3();
  return 0;
}
