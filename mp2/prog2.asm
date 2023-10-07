;Stanley Auyeung
;To create the stack calculator we first had to determine what character was the input. To do this, we implemented the usage of GETC and OUT to read an input from the keyboard and 
;then echo it to the screen. We then had to perform different actions for each character depending on what type of character it was. The types of characters that we had to check 
;for were numbers 0-9, the equal sign, a 'space,' or if it was an operator. We pushed numeric values onto the stack, pulled a final value for equal sign, and had to push two values 
;then pop for each operand. If at any point our program finds the expression to be invalid, then it will print "Invalid Expression". We also had to convert the final value that resulted 
;from the performing the calculations to a hexadecimal number that is to be printed after hitting the equal sign. At the start of the MP, we decided to look over the flowchart given to 
;us and started to implement each step. After we completed writing the program, we spent some time testing and debugging each part of the code that went wrong by going step-by-step with 
;the test cases found on the ECE220 wiki page. Once our program was fully functional, we finalized our comments and finished the MP.
;partners: sauye2, cgwang3

; Register Table:
; R0: Used as a register that stores an input from the keyboard that will be printed using the OUT trap.
; R1: Used to hold the difference between the character read and the additive inverse to determine which specific character was typed
; R2: Used as a temporary register that held the additive inverse of the characters that had to be checked
; R3: Used as a temporary register as well as the holder of one of the operands in the expression
; R4: Used as a temporary register as well as the holder of one of the operands in the expression
; R5: Used to hold the final value that was computed by performing the operations received by the inputs as well as a temporary register
; R6: Used as a temporary register as well as the digit counter for printing hexadecimal.
; R7: Used as the PC storage for the usage of the trap RET

.ORIG x3000
	
;your code goes here
READC GETC	                  ;Put character hex in R0
OUT                               ;Print character stored in R0

;Check if character is “=” 61 or x3D
LD R2,NEG61                       ;Load -61 to R2
ADD R1,R0,R2                      ;Subtract 61 from R0
BRz IFEQL		          ;Branches to IFEQL if R1 is zero

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Check is character is “sp” 32 or x20
LD R2,NEG32                       ;Load -32 to R2
ADD R1,R0,R2                      ;Subtract 32 from R0
BRz READC                         ;Branch to READC

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Check if character is “0” is 48
LD R2,NEG48			;Load -48 to R2
ADD R1,R0,R2                    ;Subtract 32 from R0
BRz IFNUM                       ;Branch to IFNUM

;Check if character is “1” is 49
LD R2,NEG49                     ;Load -49 to R2
ADD R1,R0,R2                    ;Subtract 49 from R0
BRz IFNUM                       ;Branch to IFNUM

;Check if character is “2” is 50
LD R2,NEG50                     ;Load -50 to R2
ADD R1,R0,R2                    ;Subtract 50 from R0
BRz IFNUM                       ;Branch to IFNUM

;Check if character is “3” is 51
LD R2,NEG51                     ;Load -51 to R2
ADD R1,R0,R2                    ;Subtract 51 from R0
BRz IFNUM                       ;Branch to IFNUM
  
;Check if character is “4” is 52
LD R2,NEG52                     ;Load -52 to R2
ADD R1,R0,R2                    ;Subtract 52 from R0
BRz IFNUM                       ;Branch to IFNUM

;Check if character is “5” is 53
LD R2,NEG53                     ;Load -53 to R2
ADD R1,R0,R2                    ;Subtract 53 from R0
BRz IFNUM                       ;Branch to IFNUM

;Check if character is “6” is 54
LD R2,NEG54                     ;Load -54 to R2
ADD R1,R0,R2                    ;Subtract 54 from R0
BRz IFNUM                       ;Branch to IFNUM

;Check if character is “7” is 55
LD R2,NEG55                     ;Load -55 to R2
ADD R1,R0,R2                    ;Subtract 55 from R0
BRz IFNUM                       ;Branch to IFNUM

;Check if character is “8” is 56
LD R2,NEG56                     ;Load -56 to R2
ADD R1,R0,R2                    ;Subtract 56 from R0
BRz IFNUM                       ;Branch to IFNUM

;Check if character is “9” is 57
LD R2,NEG57                     ;Load -57 to R2
ADD R1,R0,R2                    ;Subtract 57 from R0
BRz IFNUM                       ;Branch to IFNUM

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;Check if character is “*,+,-,/,^” — 
;Check if character is “*” is 42
LD R2,NEG42                     ;Load -42 to R2
ADD R1,R0,R2                    ;Subtract 42 from R0
BRz IFOPM                       ;Branch to IFOPM

;Check if character is “+” is 43
LD R2,NEG43                     ;Load -43 to R2
ADD R1,R0,R2                    ;Subtract 43 from R0
BRz IFOPP                       ;Branch to IFOPP

;Check if character is “-” is 45
LD R2,NEG45                     ;Load -45 to R2
ADD R1,R0,R2                    ;Subtract 45 from R0
BRz IFOPS                       ;Branch to IFOPS



;Check if character is “/” is 47
LD R2,NEG47                     ;Load -57 to R2
ADD R1,R0,R2                    ;Subtract 57 from R0
BRz IFOPD                       ;Branch to IFOPD

;Check if character is “^” is 94
LD R2,NEG94                     ;Load -94 to R2
ADD R1,R0,R2                    ;Subtract 94 from R0
BRz IFOPE                       ;Branch to IOPE
BRnzp PRINTINVALID   ;Print invalid if not operator

NEG61 .FILL xFFC3               ;Fill address with “-61”
NEG32 .FILL xFFE0               ;Fill address with “-32”
NEG48 .FILL xFFD0               ;Fill address with “-48”
NEG49 .FILL xFFCF               ;Fill address with “-49”
NEG50 .FILL xFFCE               ;Fill address with “-32”
NEG51 .FILL xFFCD               ;Fill address with “-32”
NEG52 .FILL xFFCC               ;Fill address with “-32”
NEG53 .FILL xFFCB               ;Fill address with “-32”
NEG54 .FILL xFFCA               ;Fill address with “-54”
NEG55 .FILL xFFC9               ;Fill address with “-55”
NEG56 .FILL xFFC8               ;Fill address with “-56”
NEG57 .FILL xFFC7               ;Fill address with “-57”
NEG42 .FILL xFFD6               ;Fill address with “-42”
NEG43 .FILL xFFD5               ;Fill address with “-43”
NEG45 .FILL xFFD3               ;Fill address with “-45”
NEG47 .FILL xFFD1               ;Fill address with “-47”
NEG94 .FILL xFFA2               ;Fill address with “-94”

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R3- value to print in hexadecimal
PRINT_HEX

ST R2,SAVER2                    ;Store value of R2
ST R7,SAVER7                    ;Store value of R7
	
AND R6,R6,#0     	        ; Initialize R6 to 0
	ADD R6,R6,#4            ; Add #4 to R6
DIGCHK  ADD R6,R6,#0            ; Check the value of R6
	BRnz RESTR2             ; Branch to RESTR2 if R6 is negative or zero
	AND R3,R3,#0            ; Initialize R3 to 0
	AND R4,R4,#0            ; Initialize R4 to 0
	ADD R4,R4,#4            ; Add #4 to R4
BITCHK  ADD R4,R4,#0            ; Check the value of R4
	BRnz DIG9               ; Branch to DIG9 if value is negative or zero
	ADD R3,R3,R3            ; Left shift R3
	ADD R2,R2,#0            ; Check the value of R2
	BRn NEG                 ; Branch to NEG if value is negative
	ADD R3,R3,#0            ; Add #0 to R3
	BRnzp SHIFT2            ; Branch to SHIFT2
NEG	ADD R3,R3,#1            ; Add #1 to R3
SHIFT2	ADD R2,R2,R2            ; Left shift R2
	ADD R4,R4,#-1           ; Decrement R4 by 1
	BRnzp BITCHK            ; Branch to BITCHK

DIG9	ST R6,R6_VALUE          ; Save value of R6
	ADD R6,R3,#-9           ; Subtract R3 and 9 and store value into R6
	BRnz ADDZ               ; Branch to ADDZ if value is negative or zero
	LD R0, AASCII           ; Load hexadecimal for "A" in R0
	ADD R0,R0,#-10          ; Subtract R0 and 10
	ADD R0,R0,R3            ; Add R0 and R3
	BRnzp OUTT              ; Branch to OUTT
ADDZ	LD R0,ZASCII            ; Load hexadecimal for "0" in R0
	ADD R0,R0,R3            ; Add R0 and R3
OUTT	OUT                     ; Print character
	LD R6,R6_VALUE          ; Restore value of R6
	ADD R6,R6,#-1           ; Decrement R6 by 1
	BRnzp DIGCHK            ; Branch to DIGCHK

RESTR2 LD R2,SAVER2             ;Restore value of R2
LD R7,SAVER7                    ;Restore value of R7
RET    			        ;Return to PC in R7


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE

;your code goes here

IFEQL                           ;Perform if equal sign
LD R3,STACK_START               ;Check if there is only one item in stack, if so pop, print and store 
LD R4,STACK_TOP                 ;If not one item in stack, print invalid
NOT R4,R4
ADD R4,R4,#1
ADD R3,R3,R4
ADD R3,R3,#-1
BRnp PRINTINVALID
JSR POP
LDI R2,STACK_START
ADD R5,R2,#0
JSR PRINT_HEX
BRnzp DONE

IFNUM 
LD R2,NEG48                     ;Load R2 with additive inverse of ASCII “0”
ADD R0,R0,R2                    ;”Subtract “0””
JSR PUSH                        ;Push value onto stack
BRnzp READC                     ;Branch to READC

IFOPM 		                ;If multiply, check if there are two operands, if so pop values, perform calculation
LD R3,STACK_START               ;push value to stack and read next character
LD R4,STACK_TOP
NOT R4,R4
ADD R4,R4,#1
ADD R3,R3,R4
ADD R3,R3,#-2
BRn PRINTINVALID
JSR POP
ADD R3,R0,#0
JSR POP
ADD R4,R0,#0
JSR MUL
JSR PUSH
BRnzp READC

IFOPP			        ;If plus, check if there are two operands, if so pop values, perform calculation
LD R3,STACK_START               ;push value to stack and read next character
LD R4,STACK_TOP
NOT R4,R4
ADD R4,R4,#1
ADD R3,R3,R4
ADD R3,R3,#-2
BRn PRINTINVALID
JSR POP
ADD R3,R0,#0
JSR POP
ADD R4,R0,#0
JSR PLUS
JSR PUSH
BRnzp READC

IFOPS			        ;If minus, check if there are two operands, if so pop values, perform calculation
LD R3,STACK_START               ;push value to stack and read next character
LD R4,STACK_TOP
NOT R4,R4
ADD R4,R4,#1
ADD R3,R3,R4
ADD R3,R3,#-2
BRn PRINTINVALID
JSR POP
ADD R3,R0,#0
JSR POP
ADD R4,R0,#0
JSR MIN
JSR PUSH
BRnzp READC

IFOPD			        ;If divide, check if there are two operands, if so pop values, perform calculation
LD R3,STACK_START               ;push value to stack and read next character
LD R4,STACK_TOP
NOT R4,R4
ADD R4,R4,#1
ADD R3,R3,R4
ADD R3,R3,#-2
BRn PRINTINVALID
JSR POP
ADD R3,R0,#0
JSR POP
ADD R4,R0,#0
JSR DIV
JSR PUSH
BRnzp READC

IFOPE			        ;If exponent, check if there are two operands, if so pop values, perform calculation
LD R3,STACK_START               ;push value to stack and read next character
LD R4,STACK_TOP
NOT R4,R4
ADD R4,R4,#1
ADD R3,R3,R4
ADD R3,R3,#-2
BRn PRINTINVALID
JSR POP
ADD R3,R0,#0
JSR POP
ADD R4,R0,#0
JSR EXP
JSR PUSH
BRnzp READC


PRINTINVALID	                ;Print the “Invalid Expression” message
LEA R0,MSG
PUTS
LD R0,SPACE
OUT
LEA R0,MSG2
PUTS
BRnzp DONE

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
PLUS				;Addition subroutine
;your code goes here
ADD R0,R3,R4	                
RET	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MIN				;Subtraction subroutine
;your code goes here
NOT R3,R3                      
ADD R3,R3,#1
ADD R0,R4,R3
RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
MUL				;Multiplication subroutine
;your code goes here
AND R0,R0,#0	     
ADD R4,R4,#0
BRn MULTIPLYNEG

MULTIPLY ADD R0,R0,R3
ADD R4,R4,#-1
BRp MULTIPLY
BRnzp RETURN

MULTIPLYNEG ADD R0,R0,R3
ADD R4,R4,#1
BRn MULTIPLYNEG
BRnzp FLIP

FLIP NOT R0,R0
ADD R0,R0,#1
BRnzp RETURN


RETURN RET	

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
DIV				;Division subroutine
;your code goes here

AND R0,R0,#0	       
NOT R3,R3
ADD R3,R3,#1

DivLOOP ADD R0,R0,#1
ADD R4,R4,R3
BRzp DivLOOP
ADD R0,R0,#-1
RET


	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP				;Exponent subroutine

ADD R5,R3,#0	      
AND R3,R3,#0
ADD R3,R3,#1

EXPO ADD R5,R5,#-1
BRn DONEEX
ST R4,EXP_SAVER4
ST R7,EXP_SAVER7
JSR MUL
LD R4,EXP_SAVER4
LD R7,EXP_SAVER7
ADD R3,R0,#0
BRnzp EXPO

DONEEX ADD R0,R3,#0
RET


;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP     	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET

POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;
SAVER2 .BLKW #1                 ;Save an address to store R2 value
R6_VALUE        .BLKW #1        ;Save an address to store R6 value
AASCII          .FILL x0041     ;Letter A in ascii
ZASCII          .FILL x0030     ;Value of "0" character in ascii
MSG .STRINGZ "Invalid"          ;The string for “Invalid”
SPACE .FILL x0020               ;ASCII value of “space”
MSG2 .STRINGZ "Expression"      ;The string for “Expression”
STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;
EXP_SAVER4 .BLKW #1             ;Save an address to store R4 value
EXP_SAVER7 .BLKW #1             ;Save an address to store R7 value
SAVER7 .BLKW #1                 ;Save an address to store R7 value
DONE HALT                       ;End of program


.END
