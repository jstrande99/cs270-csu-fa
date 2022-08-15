; P5 Assignment
; Author: <Jordan Strande>
; Date:   <10/2/2019>
; Email:  <jstrande@rams.colostate.edu>
; Class:  CS270
;
; Description: Implements the arithmetic, bitwise, and shift operations

;------------------------------------------------------------------------------
; Begin reserved section: do not change ANYTHING in reserved section!

                .ORIG x3000
                BR Main

Functions       .FILL IntAdd         ; Address of IntAdd routine     (option 0)
                .FILL IntSub         ; Address of IntSub routine     (option 1)
                .FILL IntMul         ; Address of IntMul routine     (option 2)
                .FILL BinaryOr       ; Address of BinaryOr routine   (option 3)
                .FILL LeftShift      ; Address of LeftShift routine  (option 4)
                .FILL RightShift     ; Address of RightShift routine (option 5)

Main            LEA R0,Functions     ; The main routine calls one of the 
                LD  R1,Option        ; subroutines below based on the value of
                ADD R0,R0,R1         ; the Option parameter.
                LDR R0,R0,0          ;
                JSRR R0              ;
EndProg         HALT                 ;

; Parameters and return values for all functions
; Try changing the .BLKW 1 to .FILL xNNNN where N is a hexadecimal value or #NNNN
; where N is a decimal value, this can save you time by not having to set these 
; values in the simulator every time you run your code. This is the only change 
; you should make to this section.
Option          .FILL #5             ; Which function to call
Param1          .FILL #9             ; Space to specify first parameter
Param2          .FILL #3              ; Space to specify second parameter
Result          .BLKW 1              ; Space to store result

; End reserved section: do not change ANYTHING in reserved section!
;------------------------------------------------------------------------------

; You may add variables and functions after here as you see fit.

;------------------------------------------------------------------------------
IntAdd                               ; Result is Param1 + Param2
				     ; Your code goes here (~4 lines)
		LD R0, Param1
		LD R1, Param2
		ADD R0, R0, R1       
		ST R0, Result
                RET
;------------------------------------------------------------------------------
IntSub                               ; Result is Param1 - Param2
                                     ; Your code goes here (~6 lines)
		LD R0, Param1
		LD R1, Param2
		NOT R1, R1 
		ADD R1, R1, #1
		ADD R0, R0, R1
		ST R0, Result
                RET
;------------------------------------------------------------------------------
IntMul                               ; Result is Param1 * Param2
                                     ; Your code goes here (~9 lines)
		LD R0, Param1		
		AND R3, R3, #0
		LD R1, Param2

MultLoop	BRnz MultEnd
			ADD R3, R0, R3
			ADD R1, R1, #-1
		BRp MultLoop
MultEnd

		ST R3, Result
                RET
;------------------------------------------------------------------------------
BinaryOr                             ; Result is Param1 | Param2
                                     ; Your code goes here (~7 lines)
		LD R0, Param1
		LD R1, Param2
		NOT R0, R0
		NOT R1, R1
		AND R3, R0, R1
		NOT R3, R3
		ST R3, Result
                RET
;------------------------------------------------------------------------------
LeftShift                            ; Result is Param1 << Param2
                                     ; (Fill vacant positions with 0's)
                                     ; Your code goes here (~7 lines)
		LD R0, Param1
		LD R1, Param2

LeftLoop	BRnz LeftEnd
			ADD R0, R0, R0
			ADD R1, R1, #-1
		BRp LeftLoop
LeftEnd
                RET
;------------------------------------------------------------------------------
RightShift                           ; Result is Param1 >> Param2
                                     ; (Fill vacant positions with 0's)
                                     ; Your code goes here (~16 lines)
		LD R0, Param1		;R0 = val
		LD R1, Param2		;R1 = shift

		AND R3, R3, #0		; Mask 1 - R3
		ADD R3, R3, #1

RightLoop
		BRnz RightEnd
			ADD R3, R3, R3		
			ADD R1, R1, #-1
		BRp RightLoop
RightEnd

		AND R2, R2, #0		; Mask 2 - R2
		ADD R2, R2, #1			
		ADD R1, R1, #0		; R1 = Result CHANGED

RLoop		BRnp REnd
			AND R4, R0, R3

			BRz Skip
                        	ADD R1, R2, R1        
                        Skip

			ADD R3, R3, R3
			ADD R2, R2, R2

		BRnp RLoop
REnd

		ST R1, Result
                RET
;------------------------------------------------------------------------------
                .END
