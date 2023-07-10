FILE_NAME_PARTIAL := test
FILE_HOME := ./
# Empty assignment for no ext
FILE_EXT :=
FILE_NAME := $(FILE_NAME_PARTIAL)$(FILE_EXT)
FULL_FILE_NAME := $(FILE_HOME)$(FILE_NAME)
OUT_OPTION := -o $(FILE_NAME)
GCC_COMMAND_PARTIAL := gcc -std=c17 -pedantic-errors
GCC_TO_C := $(GCC_COMMAND_PARTIAL) $(OUT_OPTION)
GCC_TO_ASM := $(GCC_COMMAND_PARTIAL) -S -fverbose-asm $(OUT_OPTION).s

5.1:
	-$(GCC_TO_C) pointers-5.1.c

5.1-asm:
	-$(GCC_TO_ASM) pointers-5.1.c

5.1-and-run:
	$(GCC_TO_C) pointers-5.1.c
	$(FULL_FILE_NAME)

5.2:
	-$(GCC_TO_C) pointers-5.2.c -lm

5.2-asm:
	-$(GCC_TO_ASM) pointers-5.2.c -lm

5.2-and-run:
	$(GCC_TO_C) pointers-5.2.c -lm
	$(FULL_FILE_NAME)

test-input:
	-$(GCC_TO_C) test-input.c

test-input-asm:
	-$(GCC_TO_ASM) test-input.c

test-input-and-run:
	$(GCC_TO_C) test-input.c
	$(FULL_FILE_NAME)

labels-and-goto:
	-$(GCC_TO_C) labels-and-goto.c

labels-and-goto-asm:
	-$(GCC_TO_ASM) labels-and-goto.c

labels-and-goto-and-run:
	$(GCC_TO_C) labels-and-goto.c
	$(FULL_FILE_NAME)

labels-and-goto.2:
	-$(GCC_TO_C) labels-and-goto.2.c

labels-and-goto.2-asm:
	-$(GCC_TO_ASM) labels-and-goto.2.c

labels-and-goto.2-and-run:
	$(GCC_TO_C) labels-and-goto.2.c
	$(FULL_FILE_NAME)

clean-files:
	rm $(FULL_FILE_NAME)
