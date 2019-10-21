# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                PROJECT EULER: C89 SOLUTION MAKEFILE               #
# ----------------------------------------------------------------- #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

CC     = gcc
CFLAGS = -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes \
         -Wstrict-prototypes -Wold-style-definition
OFLAGS = -O2

CC_OUT = -o

BIN_DIR = ./bin

P1_FILES = ./p1/multisum.c
P1_EXEC  = $(BIN_DIR)/multisum

p1: setup
	@echo "P1: Building solution..."
	$(CC) $(CFLAGS) $(P1_FILES) $(CC_OUT) $(P1_EXEC) 
	@echo "*** Build complete ***"

p1test: setup
	@echo "P1: Building solution for testing..."
	$(CC) $(CFLAGS) $(P1_FILES) $(CC_OUT) $(P1_EXEC) 
	@echo ""
	@echo "*** Test 01: No input ***"
	$(P1_EXEC)
	@echo ""
	@echo "*** Test 02: Multiples of 3 or 5 < 10 ***"
	$(P1_EXEC) 10 3 5
	@echo ""
	@echo "*** Test 03: Multiples of 3 or 5 < 1000 ***"
	$(P1_EXEC) 1000 3 5
	@echo ""
	@echo "*** Test 04: Multiples of 3, 5 or 7 < 10000 ***"
	$(P1_EXEC) 10000 3 5 7
	@echo ""
	@echo "*** Testing completed ***"

p1bench: setup
	@echo "P1: Building solution for benchmarking..."
	$(CC) $(CFLAGS) $(OFLAGS) $(P1_FILES) $(CC_OUT) $(P1_EXEC) 
	@echo ""
	@echo "*** Trial 01: Multiples of 3 < 1000 ***"
	@/usr/bin/env bash -c "time $(P1_EXEC) 1000 3"
	@echo ""
	@echo "*** Trial 02: Multiples of 3 or 5 < 1000 ***"
	@/usr/bin/env bash -c "time $(P1_EXEC) 1000 3 5"
	@echo ""
	@echo "*** Trial 03: Multiples of 3, 5, 7 or 11 < 1000 ***"
	@/usr/bin/env bash -c "time $(P1_EXEC) 1000 3 5 7 11"
	@echo ""
	@echo "*** Trial 04: Multiples of 3 < 1000000 ***"
	@/usr/bin/env bash -c "time $(P1_EXEC) 1000000 3"
	@echo ""
	@echo "*** Trial 05: Multiples of 3 or 5 < 1000000 ***"
	@/usr/bin/env bash -c "time $(P1_EXEC) 1000000 3 5"
	@echo ""
	@echo "*** Trial 06: Multiples of 3, 5, 7 or 11 < 1000000 ***"
	@/usr/bin/env bash -c "time $(P1_EXEC) 1000000 3 5 7 11"
	@echo ""
	@echo "*** Trial 07: Multiples of 3 < 1000000000 ***"
	@/usr/bin/env bash -c "time $(P1_EXEC) 1000000000 3"
	@echo ""
	@echo "*** Trial 08: Multiples of 3 or 5 < 1000000000 ***"
	@/usr/bin/env bash -c "time $(P1_EXEC) 1000000000 3 5"
	@echo ""
	@echo "*** Trial 09: Multiples of 3, 5, 7 or 11 < 1000000000 ***"
	@/usr/bin/env bash -c "time $(P1_EXEC) 1000000000 3 5 7 11"
	@echo ""
	@echo "*** Testing completed ***"

setup:
	@echo "Setting up directories..."
	@mkdir -p $(BIN_DIR)

clean:
	@echo "Cleaning up environment..."
	@rm -rf $(BIN_DIR)
