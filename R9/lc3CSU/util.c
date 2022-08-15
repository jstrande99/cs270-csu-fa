#include <strings.h>
#include <stdlib.h>
#include <ctype.h>

#include "Debug.h"
#include "util.h"

/** @file util.c
 *  @brief You will modify this file and implement the util.h interface
 *  @details This is a implementation of the interface that you will write
 *  for the assignment.
 *  <p>
 *  @author <b>your name here</b>
 */

/**  @todo complete the initializtion of this data structure
 *  A sorted list of all the opcode names the assembler might see. There are
 *  more entries than there are opcodes because some LC3 instructions have
 *  multiple forms. These include JSR/JSRR, RET/JMP, the eight BR instructions
 *  and various pseudo-ops. In other implementations, this might
 *  be a hash table or a BST.
 **/
static name_val_t lc3_instruction_map[] = {
  { ".BLKW",    OP_BLKW },
  { "TRAP",     OP_TRAP }
};

/** @todo initialize this value */
static int numOps = 0;

/** @todo implement this function */
name_val_t* util_bin_search (name_val_t map[], int numNames, const char* name) {
  return 0;
}

/** @todo implement this function */
opcode_t util_get_opcode (const char* name) {
  return OP_INVALID;
}

/** @todo implement this function */
bool util_is_valid_label(const char* s) {
  return false;
}

/** This is an example of how to initialize an array of structs */
static name_val_t register_map[] = {
  { "R0", 0},
  { "R1", 1},
  { "R2", 2},
  { "R3", 3},
  { "R4", 4},
  { "R5", 5},
  { "R6", 6},
  { "R7", 7},
};

/** This is an example of how to let the compiler figure out how many entries
 *  there are.
 */
static int numRegisters = sizeof(register_map) / sizeof(register_map[0]);

/** This is an example of how to use the binary search routine */
int util_get_reg (const char* regStr) {
  name_val_t* nvp = util_bin_search(register_map, numRegisters, regStr);
  return (nvp ? nvp->val : -1);
}

/** @todo implement this function */
int util_parse_cond (const char* condCodeStr) {
  return -1;
}

/** @todo implement this function */
bool util_get_int (const char* token, int* value) {
  return false;
}

