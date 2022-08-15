#ifndef __LOGIC_H__
#define __LOGIC_H__

/* Copyright (c) 2012-2015 by Fritz Sieker.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written
 * agreement is hereby granted, provided that the above copyright notice
 * and the following two paragraphs appear in all copies of this software,
 * that the files COPYING and NO_WARRANTY are included verbatim with
 * any distribution, and that the contents of the file README are included
 * verbatim as part of a file named README with any distribution.
 *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE TO ANY PARTY FOR DIRECT,
 * INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT
 * OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE AUTHOR
 * HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS ON AN "AS IS"
 * BASIS, AND THE AUTHOR NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT,
 * UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 */

#include "lc3.h"
//#include "hardware.h"

/** @file logic.h
 *  @brief interface to the control logic of the simulator (do not modify)
 *  @details This is the interface to the code  (in logic.c) that simulates the
 *  control logic of the LC3 machine. Students
 *  will typically write the implementation as part of an assignment to
 *  complete an LC3 simulator. The implementation may depend on a previous
 *  assignment where students wrote methods for bit extraction/mainpulation.
 *
 *  @author Fritz Sieker
 */

#define OK 0 /**< value denoting successful operation */

/** This function encapsulates the details of how to get the value of a
 *  register. While it is nothing more than a direct call to a function
 *  described in hardware.h, it means that the programmer need only
 *  understand this set of methods. Only the implementor of this code will
 *  need to deal with the hardware interface.
 */
LC3_WORD logic_read_reg (int regNum);

/** This method encapsulates the details of how a value is put in one of the
 *  LC3 general purpose registers. It deals with the resources described in
 *  hardware.h to perform its work. The clean interface of this method hides
 *  the details from the programmer and only the implementor of this code will
 *  need to deal with the hardware interface. The method does NOT set the
 *  condition codes.
 */
void logic_write_reg (int regNum, LC3_WORD val);

/** This function encapsulates the details of how memory is actually read. 
 *  It must deal with getting the MAR set correctly, peforming the read,
 *  and returning a value. This involve accessing the resources described
 *  in the hardware.h file.
 */
LC3_WORD logic_read_memory (LC3_WORD addr);

/** This method encapsulates the details of how memory is actually written. 
 *  It must deal with getting the MAR and MDR set correctly, and performing
 *  the write. This involves accessing the resources described in hardware.h.
 */
void logic_write_memory (LC3_WORD addr, LC3_WORD value);

/** These aliases let you use the "name" of a field as shown in the LC3 IS.
 *  Thus, you may use DR in the ADD instruction and SR for the ST instruction.
 *  Both refer to the same set of bits in the instruction word.
 */

#define SR         DR
#define BaseR      SR1
#define nzp        DR

/** This structure holds all the fields that occur in an instruction.
 *  Conceptually, all of these fields are computed in parallel in the
 *  combinational logic of the LC3 and the control logic selects the
 *  values to use depending on the actual instruction. In hardware, there
 *  is "no" cost to computing things you might not use. In the implementation,
 *  you may choose to precompute all the fields, or simply get values from
 *  the instruction itself as they are needed. This structure is used as
 *  the parameter for logic_fetch_instruction(), logic_decode_instruction(),
 *  and logic_execute_instruction(), ... .
 */

typedef struct inst_fields {
  LC3_WORD addr;         /**< address of the instruction                   */
  LC3_WORD bits;         /**< 16 bit instruction                           */
  opcode_t opcode;       /**< opcode of instruction                        */
  int      DR;           /**< destination register                         */
  int      SR1;          /**< source register 1                            */
  int      SR2;          /**< source register 2                            */
  int      bit5;         /**< distinguishes immediate from register        */
  int      bit11;        /**< distinguishes JSR/JSRR                       */
  LC3_WORD trapvect8;    /**< value for TRAP                               */
  LC3_WORD imm5;         /**< 5 bit immediate value (signed)               */
  LC3_WORD offset6;      /**< 6 bit register offset (signed)               */
  LC3_WORD PCoffset9;    /**< 9 bit offset from program counter (signed)   */
  LC3_WORD PCoffset11;   /**< 11 bit offset from program counter (signed)  */
  LC3_WORD SR1OUT;       /**< value of SR1                                 */
  LC3_WORD SR2MUX[2];    /**< the two inputs of SR2MUX. The value of bit5
                          *   selects the input to use                     */
  LC3_WORD SR2MUXval;    /**< value of SR2MUX                              */
  LC3_WORD ADDR1MUX[2];  /**< the two inputs of ADDR2MUX. One value is a
                          *   result of adding the BaseR and the offest.
                          *   The other contains the incremented PC.       */
  int      ADDR2MUX[4];  /**< Four inputs of ADDR2MUX. There is a 0 and
                          *   three different sign extended values.        */
} instruction_t;

/** This method encapsulates the details of an instruction fetch. Upon return
 *  the IR contains the instruction and the PC has been incremented, and the
 *  addr and bits fields of the structure have been set appropriately. The addr
 *  field in the structure is the address of the instruction, not the
 *  incremented PC. It must deal with getting the MAR set correctly,
 *  peforming a read, and setting the IR. This involves accessing the resources
 *  described in hardware.h.
 */
void logic_fetch_instruction (instruction_t* inst);

/** This function decodes the instruction. This involves setting fields of the
 *  structure that is the parameter of the method. At a minimum, it must set
 *  the opcode field. Setting the other fields is optional,
 *  but will simplify the code for executing the instruction. The return value
 *  follows the common C pattern of 0 meaning success (i.e. instruction is
 *  valid), and any non-zero value indicating the type of error. For this
 *  implementation, only zero and non-zero are tested.
 *  @param inst - a pointer to the instruction structure.
 */
int logic_decode_instruction (instruction_t* inst);

/** This function executes the instruction. At completion, the state of the
 *  LC3 hardware reflects the result of the instruction. The return value
 *  follows the common C pattern of 0 meaning success (i.e. instruction is
 *  valid), and any non-zero value indicating the type of error. For this
 *  implementation, only zero and non-zero are tested.
 */
int logic_execute_instruction (instruction_t* inst);

#define SelNotUsed 0 /**< selector not used */
#define SelImm     1 /**< SR2MUX selector   */
#define SelReg     0 /**< SR2MUX selector   */
#define SelBaseR   0 /**< ADDR1MUX selector */
#define SelPC      1 /**< ADDR1MUX selector */
#define SelSEXT11  0 /**< ADDR2MUX selector */
#define SelSEXT9   1 /**< ADDR2MUX selector */
#define SelSEXT6   2 /**< ADDR2MUX selector */
#define SelZero    3 /**< ADDR2MUX selector */

/** This recommended helper function should return the value of the
 *  MARMUX. This method is only used internally, but is declared
 *  non-static so the documentation can be in the header file.
 *  @param inst - a pointer to the instruction structure.
 *  @param ADDRMUX1sel- an integer defining which of the two inputs of
 *         the ADDR1MUX to use (see various defines SelXXX).
 *  @param ADDRMUX2sel- an integer defining which of the four inputs of
 *         the ADDR2MUX to use (see various defines SelXXX).
 *  @return If the opcode is a OP_TRAP, return ZEXT. Otherwise, return the
 *          sum from the ADDR1MUX and ADDR2MUX
 */
LC3_WORD logic_MARMUX (instruction_t* inst, int ADDRMUX1sel, int ADDRMUX2sel);

#endif

