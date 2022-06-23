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
	
GPIOA_ODR	      equ 0x50000014
GPIOB_ODR	      equ 0x50000414
    
    LDR r0 ,=GPIOA_ODR
	LDR r3,[r0]
	LDR r1 ,=0x800                
	ORRS r3,r3 ,r1
	STR r3,[r0]
	
	LDR r2 ,=GPIOA_ODR
	LDR r3,[r2]
	LDR r1 ,=0x1000               
	ORRS r3,r3 ,r1
	STR r3,[r2]
	
	LDR r5 ,=GPIOB_ODR
	LDR r3,[r5]
	LDR r1 ,=0x10               
	ORRS r3,r3 ,r1
	STR r3,[r5]
	
	LDR r6 ,=GPIOB_ODR
	LDR r3,[r6]
	LDR r1 ,=0x20                 
	ORRS r3,r3 ,r1
	STR r3,[r6]
	
	
    ; Edit above this line
    B .
    ENDP

    END