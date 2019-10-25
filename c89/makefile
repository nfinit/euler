# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
#                PROJECT EULER: C89 SOLUTION MAKEFILE               #
# ----------------------------------------------------------------- #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

# COMPILER CONFIGURATION // COMPILER CONFIGURATION // COMPILER CONFIGURATION #
CC         = gcc
CC_VER     = GCC $(shell gcc --version | grep ^gcc | sed 's/^.* //g') # GCC
CFLAGS     = -Wall -Wextra -std=c89 -pedantic -Wmissing-prototypes \
             -Wstrict-prototypes -Wold-style-definition
OFLAGS     = -O2

#  COMPILER FLAGS  //  COMPILER FLAGS // COMPILER FLAGS  //  COMPILER FLAGS  #
CC_OUT     = -o
CC_DEFINE  = -D
CC_LIB     = -l

#  DIRECTORIES // DIRECTORIES // DIRECTORIES // DIRECTORIES // DIRECTORIES  #
BIN_DIR    = ./bin

#   BENCH CONFIGURATION  //  BENCH CONFIGURATION  //  BENCH CONFIGURATION   #
n          = 1000

setup:
	@echo "Setting up directories..."
	@mkdir -p $(BIN_DIR)

clean:
	@echo "Cleaning up environment..."
	@rm -rf $(BIN_DIR)	

#   PROJECT 1  //  PROJECT 1  //  PROJECT 1  //  PROJECT 1  //  PROJECT 1   #

P1_FILE    = ./p1/multisum.c
P1_EXEC    = $(BIN_DIR)/multisum
P1_EXEC_BF = $(BIN_DIR)/brutesum

p1: setup
	@echo "P1: Building solutions..."
	$(CC) $(CFLAGS) $(OFLAGS) $(CC_LIB)m $(P1_FILE) $(CC_OUT) $(P1_EXEC)
	$(CC) $(CFLAGS) $(OFLAGS) $(CC_LIB)m $(CC_DEFINE)_P1_BRUTEFORCE $(P1_FILE) $(CC_OUT) $(P1_EXEC_BF)
	@echo "*** BUILD COMPLETE ***"

validate-p1: p1
	@echo ""
	@echo "P1: Running validation tests..."
	@echo ""
	$(P1_EXEC_BF) 10 3 5
	$(P1_EXEC) 10 3 5
	@echo ""
	$(P1_EXEC_BF) 10 2 4 6
	$(P1_EXEC) 10 2 4 6
	@echo ""
	$(P1_EXEC_BF) 1000 3 5
	$(P1_EXEC) 1000 3 5
	@echo ""
	$(P1_EXEC_BF) 105 3 5 7 11
	$(P1_EXEC) 105 3 5 7 11
	@echo ""
	$(P1_EXEC_BF) 106 3 5 7 11
	$(P1_EXEC) 106 3 5 7 11
	@echo ""
	$(P1_EXEC_BF) 107 3 5 7 11
	$(P1_EXEC) 107 3 5 7 11
	@echo ""
	$(P1_EXEC_BF) 1000 3 5 7 11 13 17 19 23 29
	$(P1_EXEC) 1000 3 5 7 11 13 17 19 23 29
	@echo ""
	@echo "*** VALIDATION TEST COMPLETE ***"

benchmark-p1: p1
	@/usr/bin/env bash -c "clear"
	@echo ""
	@echo "P1: Running benchmark tests..."
	@echo "Compiler: $(CC_VER)"
	@echo "Optimization flags: $(OFLAGS)"
	@echo ""
	@echo "Searching: 3, 5, 7, 11, 13 in range 0 < n < $(n)"
	@echo ""
	@echo "Testing fast summation algorithm..."
	@/usr/bin/env bash -c "time $(P1_EXEC) $(n) 3 5 7 11 13"
	@echo ""
	@echo "Testing brute force algorithm..."
	@/usr/bin/env bash -c "time $(P1_EXEC_BF) $(n) 3 5 7 11 13"
	@echo ""
	@echo "*** TEST COMPLETE***"
