                .ORIG x3000         
Main            
                LD R6, Stack        ; Initialize stack pointer
                LD R5, Stack        ; Initialize frame pointer
                LD R0, ParamValue   ;
                PUSH R0             ;                                
                JSR ProcessHexData  ; call ProcessHexData
                ADD R6, R6, #1      ; clean up stack, 1 empty return value, no prams                    
                HALT
ProcessHexData
                ADD R6, R6, #-1     ; allocate space for return value
                PUSH R7             ; push return address
                PUSH R5             ; push previous frame pointer
                ADD R5, R6, #-1     ; setup new frame pointer
;################################## ; buffer size can be changed
                ADD R6, R6, #-1     ; allocate space for local buffer of size 2
;################################## 
                ADD R0, R6, #0      ; R0: address of first buffer entry
                TRAP x28            ; call GETH system routine
                TRAP x27            ; move output to next line
                ; Do something interesting with binary data in local buffer
                LD R0, RetValue     ;
                STR R0, R5, #3      ; save return value on stack
;################################## ; if buffer size above is changed this value also needs
                                    ; to be changed
                ADD R6, R6, #1      ; remove local buffer from stack
;##################################
                POP R5              ; restore previous frame pointer
                POP R7              ; restore return address
                                    ; could these values have been modified by GETH?
                RET 
                                
PrivateFunction                
                ADD R6, R6, #-1     ; allocate space for return value
                PUSH R7             ; push return address
                PUSH R5             ; push previous frame pointer
                ADD R5, R6, #-1     ; setup new frame pointer
                ADD R6, R6, #-5     ; allocate space for local buffer of size 5
                LEA R0, Message     ; R0: address of first char of Message
                PUTS                ; display Message
                ADD R6, R6, #5      ; remove local buffer from stack
                POP R5              ; restore previous frame pointer
                POP R7              ; restore return address                   
                RET

; Constants
;################################## ; this can be changed
Stack           .FILL x3037         ; starting address of the stack
;##################################
ParamValue      .FILL #-1           ; used for locating param on stack
RetValue        .FILL xBBBB         ; used for locating return value on stack
Message         .STRINGZ "@#$%&@"   ; overflow message, short so stack can be close to data
                                    ; for easy viewing

               .END                


