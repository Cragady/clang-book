/*
  I'm just going to preface this by saying that I follow the ideology that
  'goto' should be used rarely, if ever. We ought to have enough design patterns
  in 'c', or any modern(ish) equiv or higher level anguage that implements 'goto', that it
  shouldn't be necessary. A good example for this is RAII in c++. Having RAII, at
  least in my understanding, eliminates the need for 'goto' statements when it comes
  to memory allocation & management.

  This file is just to see the flow in c & asm. Likely no practical use for having
  this knowledge, except if you're devving in asm.

  The book has a pretty strong stance on the matter, and in the section covering
  'goto' and labels, it opens with this:

  "C provides the infinitely-abusable goto statement, and labels to branch to."

  Lol.

  https://www.cs.uaf.edu/courses/cs301/2014-fall/notes/goto/index.html#:~:text=A%20jump%20instruction%2C%20like%20%22jmp,are%20notconsidered%20shameful%20in%20assembly.

  The program operates as expected, but the ASM output does not have any 'jmp' statements as
  currently written. The ASM instead ordered the code, in the logical flow of the
  goto & label statements, without any jmp's and utilized 'nop' to do nothing,
  falling through to the order specified in the 'C' code. I'd have to test on different
  architectures and compilers to see if this behavior is the same, or similar,
  across each environment.

  One other tidbit for labels & goto's: If you do have to use them, ensure you only move forward,
  never backwards. At least that was a consensus that I've come across that makes sense. If
  you have to use something that is touted to be horrible, minimize the amount of horribleness;
  in other words, using something that can easily create spaghetti without trying, ensure you
  make it as understandable as possible - only jumping forwards does this easily.

  To find some interesting readings regarding this, just google 'should goto be used',
  and click on the first stack-overflow link you come across. Follow links in the commentary.
  It's a rabbit-hole and it's pretty fascinating.
*/

#include <stdio.h>

int main() {
  goto control;

  label_foo:
    printf("I'm in label_foo\n");
    goto fin;
  label_bar:
    printf("I'm in label_bar\n");
    goto label_foo;

  control:
    goto label_bar;

  fin:
    return 0;
}
