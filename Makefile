FILE_NAME_PARTIAL := test
FILE_HOME := ./
# Empty assignment for no ext
FILE_EXT :=
FILE_NAME := $(FILE_NAME_PARTIAL)$(FILE_EXT)
FULL_FILE_NAME := $(FILE_HOME)$(FILE_NAME)
GCC_COMMAND_PARTIAL := gcc -o $(FILE_NAME) -std=c17 -pedantic-errors

5.1:
	-$(GCC_COMMAND_PARTIAL) pointers-5.1.c

5.1-and-run:
	$(GCC_COMMAND_PARTIAL) pointers-5.1.c
	$(FULL_FILE_NAME)

5.2:
	-$(GCC_COMMAND_PARTIAL) pointers-5.2.c

5.2-and-run:
	$(GCC_COMMAND_PARTIAL) pointers-5.2.c
	$(FULL_FILE_NAME)

test-input:
	$(GCC_COMMAND_PARTIAL) test-input.c
	$(FULL_FILE_NAME)

clean-files:
	rm $(FULL_FILE_NAME)
