Stack_Size      EQU     0x00004000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp

    THUMB

    AREA    RESET, DATA, READONLY
    EXPORT  __Vectors

__Vectors
    DCD     __initial_sp                   ; Top of Stack
    DCD     Reset_Handler                  ; Reset Handler
    DCD     NMI_Handler                    ; NMI Handler
    DCD     HardFault_Handler              ; Hard Fault Handler

    AREA    |.text|, CODE, READONLY


; nmi handler
NMI_Handler    PROC
    EXPORT  NMI_Handler
    B .
    ENDP


; hardfault handler
HardFault_Handler    PROC
    EXPORT  HardFault_Handler
    B .
    ENDP


; entry function
Reset_Handler    PROC
    EXPORT  Reset_Handler
    ; Edit below this line
	
GPIOA_ODR	      equ (0x50000014)

loop1
    
    LDR r1 ,=GPIOA_ODR
	LDR r3,[r1]

	LDR r2 ,=0x100
                        
	ORRS r3,r3 ,r2
	
	STR r3,[r1]
	
	LDR r1 ,=GPIOA_ODR   ;led KAPANMA
	LDR r3,[r1]
	LDR r2 ,=0x0
    ANDS r3,r3,r2
	STR r3,[r1]
	
	;delay:
	MOVS r0,#100
loop2
	SUBS r0,#1
	BNE loop2


    MOVS r4,#10     ;LED 10 KERE 1 ER SANIYE ARALIKLARLA YANACAKTIR.
	SUBS r4,#1
    BNE loop1
	
    ; Edit above this line
    B .
    ENDP

    END