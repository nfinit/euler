# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                PROJECT EULER: C89 SOLUTION MAKEFILE               #
# ----------------------------------------------------------------- #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

CC     = cc
CFLAGS = -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes \
         -Wstrict-prototypes -Wold-style-definition
OFLAGS = -O2

CC_OUT = -o

BIN_DIR = ./bin

P1_FILES = ./p1/multisum.c
P1_EXEC  = $(BIN_DIR)/multisum
p1-test: setup
@echo "P1: Building solution for testing..."
$(CC) $(CFLAGS) $(P1_FILES) $(CC_OUT) $(P1_EXEC) 
@echo "Test 01: No input"
$(P1_EXEC)
@echo "Test 02: Multiples of 3 or 5 < 10"
$(P1_EXEC) 10 3 5
@echo "Test 03: Multiples of 3 or 5 < 1000"
$(P1_EXEC) 1000 3 5
@echo "Testing complete."


setup:
@echo "Setting up directories..."
@mkdir -p $(BIN_DIR)

clean:
@echo "Cleaning up environment..."
@rm -rf $(BIN_DIR)
