; partners: sauye2
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop

; This is the program that I created in order to print a histogram. At the start of the mp, I decided to first work on the part
; of the code where you print out a hexadecimal. In order to do so, I followed the flowchart provided by lab 1 and was able to
; correctly implement the function of printing out in hexadecimal notation given a value in hexadecimal after hours of testing
; and debugging. After I figured this portion out, I had to write the code to print the histogram. In order to do this, I first
; broke the task of first printing the ascii character, and then transitioning into the printing of the hexadecimal up by writing
; comments that could potentially be the correct way of doing things. After thinking about what works and what doesn't work, I 
; finalized my comments and then coded the comments into instructions. Once my program was done, I spent some more time testing and
; debugging each part of the code that went wrong by going step-by-step. In the end, I was able to complete the lab.

; Register Table:
; R0: Used as a temporary register as well as the register that held the values to be printed using the OUT trap.
; R1: Used to hold the hexadecimal values of the characters that had to be printed prior to the hexadecimal notation being printed.
; R2: Used to hold the number of characters counted in each histogram bin in hexadecimal.
; R3: Used as the "digit" register that recorded the number that should be printed.
; R4: Used as a bit counter for the printing a hexadecimal part of the code.
; R5: Used to hold the address of each bin in the histogram to load the number count of characters.
; R6: Used as a temporary register as well as the digit counter.
; R7: Used as a histogram bin counter to let the program know when it should stop after going through all 27 bins.

PRINT_HIST
        AND R7,R7,#0        ; Initialize R7 to 0
        LD R6,NUM_BINS      ; Load the number #27 into R6
        ADD R7,R7,R6        ; Add #27 into R7
        LD R1,NA_ASCII      ; Load the non-alphabet character @ to R1
        LD R5,HIST_ADDR     ; Load the histogram starting address to R5
LOOP    ST R1,R1_VALUE      ; Save the value of R1
        ST R7,SAVE_R7       ; Save the value of R7
	ST R5,R5_VALUE      ; Save the value of R5
	LDI R2,R5_VALUE     ; Load the contents within the contents of memory address R5_VALUE
	LD R0,R1_VALUE      ; Restore the value of R1 in R0
	OUT                 ; Print character
	LD R0,SPACE         ; Load the hexadecimal value for space in R0
	OUT                 ; Print character

	AND R6,R6,#0        ; Initialize R6 to 0
	ADD R6,R6,#4        ; Add #4 to R6
DIGCHK  ADD R6,R6,#0        ; Check the value of R6
	BRnz LFASCII        ; Branch to LFASCII if R6 is negative or zero
	AND R3,R3,#0        ; Initialize R3 to 0
	AND R4,R4,#0        ; Initialize R4 to 0
	ADD R4,R4,#4        ; Add #4 to R4
BITCHK  ADD R4,R4,#0        ; Check th evalue of R4
	BRnz DIG9           ; Branch to DIG9 if value is negative or zero
	ADD R3,R3,R3        ; Left shift R3
	ADD R2,R2,#0        ; Check the value of R2
	BRn NEG             ; Branch to NEG if value is negative
	ADD R3,R3,#0        ; Add #0 to R3
	BRnzp SHIFT2        ; Branch to SHIFT2
NEG	ADD R3,R3,#1        ; Add #1 to R3
SHIFT2	ADD R2,R2,R2        ; Left shift R2
	ADD R4,R4,#-1       ; Decrement R4 by 1
	BRnzp BITCHK        ; Branch to BITCHK

DIG9	ST R6,R6_VALUE      ; Save value of R6
	ADD R6,R3,#-9       ; Subtract R3 and 9 and store value into R6
	BRnz ADDZ           ; Branch to ADDZ if value is negative or zero
	LD R0,AASCII        ; Load hexadecimal for "A" in R0
	ADD R0,R0,#-10      ; Subtract R0 and 10
	ADD R0,R0,R3        ; Add R0 and R3
	BRnzp OUTT          ; Branch to OUTT
ADDZ	LD R0,ZASCII        ; Load hexadecimal for "0" in R0
	ADD R0,R0,R3        ; Add R0 and R3
OUTT	OUT                 ; Print character
	LD R6,R6_VALUE      ; Restore value of R6
	ADD R6,R6,#-1       ; Decrement R6 by 1
	BRnzp DIGCHK        ; Branch to DIGCHK

LFASCII LD R0,LF_ASCII      ; Load line feed character to R0
	OUT                 ; Print character
	ADD R1,R1,#1        ; Increment R1
	ADD R5,R5,#1        ; Increment R5
	LD R7,SAVE_R7       ; Restore value of R7
	ADD R7,R7,#-1       ; Decrement bin counter
	BRp LOOP            ; Branch to loop if positive


; you will need to insert your code to print the histogram here

; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE	HALT			; Otherwise, done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
NA_ASCII        .FILL x0040     ; @ character in ascii
ASCII           .FILL x0030     ; number 0 in ascii
AASCII          .FILL x0041     ; letter A in ascii
ZASCII          .FILL x0030     ; 0 character in ascii
LF_ASCII        .FILL x000A     ; Line feed hex in ascii
R1_VALUE        .BLKW #1        ; Save an address to store R1 value
SAVE_R7         .BLKW #1        ; Save an address to store R7 value
SPACE           .FILL x0020     ; Space character in ascii
R5_VALUE        .BLKW #1        ; Save an address to store R5 value
R6_VALUE        .BLKW #1        ; Save an address to store R6 value

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
