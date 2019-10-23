# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                PROJECT EULER: C89 SOLUTION MAKEFILE               #
# ----------------------------------------------------------------- #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

CC         = gcc
CC_VER     = GCC $(shell gcc --version | grep ^gcc | sed 's/^.* //g') # GCC
CFLAGS     = -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes \
             -Wstrict-prototypes -Wold-style-definition
OFLAGS     = -O2

CC_OUT     = -o
CC_DEFINE  = -D
CC_LIB     = -l

BIN_DIR    = ./bin

n          = 1000

P1_FILES   = ./p1/multisum.c
P1_EXEC    = $(BIN_DIR)/multisum
P1_EXEC_SL = $(P1_EXEC)-bruteforce

setup:
	@echo "Setting up directories..."
	@mkdir -p $(BIN_DIR)

clean:
	@echo "Cleaning up environment..."
	@rm -rf $(BIN_DIR)

p1: setup
	@echo "P1: Building solutions..."
	$(CC) $(CFLAGS) $(OFLAGS) $(CC_LIB)m $(P1_FILES) $(CC_OUT) $(P1_EXEC_SL)
	$(CC) $(CFLAGS) $(OFLAGS) $(CC_LIB)m $(CC_DEFINE)_P1_FAST $(P1_FILES) $(CC_OUT) $(P1_EXEC)
	@echo "*** Build complete ***"

validate-p1: p1
	@echo ""
	@echo "P1: Running validation tests..."
	@echo ""
	@echo "*** BRUTE-FORCE SEARCH"
	$(P1_EXEC_SL) 10 3 5
	$(P1_EXEC_SL) 1000 3 5
	@echo ""
	@echo "*** FAST SUMMATION"
	$(P1_EXEC) 10 3 5
	$(P1_EXEC) 1000 3 5
	@echo ""
	@echo "*** VALIDATION TEST COMPLETE ***"

benchmark-p1: p1
	@echo ""
	@echo "P1: Running benchmark tests..."
	@echo "Compiler: $(CC_VER)"
	@echo "Optimization flags: $(OFLAGS)"
	@echo ""
	@echo "Searching: 3, 5, 7, 11, 13 in range 0 < n < $(n)"
	@echo ""
	@echo "*** FAST SUMMATION"
	@/usr/bin/env bash -c "time $(P1_EXEC) $(n) 3 5 7 11 13"
	@echo ""
	@echo "*** BRUTE-FORCE SEARCH"
	@/usr/bin/env bash -c "time $(P1_EXEC_SL) $(n) 3 5 7 11 13"
	@echo ""
	@echo "*** TEST COMPLETE***"
