# Makefile for LC3 binary distribution of CSU LC3 tools

# Verify before use
# 1. make sure sed is in your path (used in ./fixPath)
# 2. Set GCC to the the C compiler you use

SRC = install.c
OBJ = install.o
SIM = lc3sim
LIB = lc3sim.a

# Compiler command and flags
GCC       = gcc
GCC_FLAGS = -g -std=c11 -Wall -fPIC

# Compile .c files to .o files
.c.o:
	$(GCC) $(GCC_FLAGS) -c $<

# Compile install.c and link to lc3sim.a to produce lc3sim

$(SIM): $(OBJ) $(LIB)
	$(GCC) $(GCC_FLAGS) $(SRC) $(LIB) -o $(SIM)

# Set install directory in install.c and lc3sim-tk
# Assemble the lc3os code (the "operating system")
install.c: install.c.MASTER
	./fixPath install.c lc3sim-tk
	./lc3as lc3os.asm

seeLC3: seeLC3.c $(LIB)
	$(GCC) seeLC3.c $(LIB) -o %<

# Clean up the directory
clean:
	rm -f *.o install.c lc3sim-tk lc3os.obj lc3os.sym *~ $(SIM) seeLC3

