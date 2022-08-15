/** @file logic.c
 *  @brief Implementation of the logic.h interface
 *  @details This is a implementation of the interface that you will write
 *  for the assignment.
 *  <p>
 *  @author <b>your name here</b>
 */

#include "lc3.h"
#include "hardware.h"
#include "logic.h"

static int not_implemented() {
  return (! OK);
}

LC3_WORD logic_read_reg (int regNum) {
  return hardware_get_REG(regNum);
}

/** @todo implement this function */
void logic_write_reg (int regNum, LC3_WORD val) {
}

/* What might this method do, and who might use it? Study the LC3 instructions.
 * and implement it if you find it useful. As its name implies it sets the
 * destination register and ...? Since it is static, it can not be 
 * used outside of this file, so if you don't implement it, no problems
 * will occur.
 */
static void write_DR (instruction_t* inst, LC3_WORD value) {
}

LC3_WORD logic_read_memory (LC3_WORD addr) {
  lc3_BUS = &addr;                /* put addr on BUS   */
  hardware_load_MAR();            /* load MAR from BUS */
  hardware_memory_enable(0);      /* read memory       */
  hardware_gate_MDR();            /* put MDR on bus    */
  LC3_WORD val = *lc3_BUS;        /* value is on BUS   */
  return val;
}

/** @todo implement this function */
void logic_write_memory (LC3_WORD addr, LC3_WORD value) {
}

/** @todo implement this function */
void logic_fetch_instruction (instruction_t* inst) {
}

/** @todo implement this function */
int logic_decode_instruction (instruction_t* inst) {
  return (! OK);
}

static int execute_ADD (instruction_t* inst) {
  return not_implemented();
}

/** @todo implement this function */
int logic_execute_instruction (instruction_t* inst) {
  switch (inst->opcode) {
    case OP_ADD: return execute_ADD(inst);

    default:     return not_implemented();
  }

  return (! OK);
}

/** @todo implement this function */
LC3_WORD logic_MARMUX (instruction_t* inst, int ADDRMUX1sel, int ADDRMUX2sel) {
  return 0;
}
