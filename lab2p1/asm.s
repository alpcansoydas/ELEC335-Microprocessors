.syntax unified
.cpu cortex-m0plus
.fpu softvfp
.thumb


/* make linker see this */
.global Reset_Handler

/* get these from linker script */
.word _sdata
.word _edata
.word _sbss
.word _ebss

//LEFT TO RIGHT LEDS 0-1-2-3-4-5-6 => PB0-PB1-PB2-PB3-PB4-PB5-PB6
// BUTTON-PA0
/* define peripheral addresses from RM0444 page 57, Tables 3-4 */
.equ RCC_BASE,         (0x40021000)          // RCC base address
.equ RCC_IOPENR,       (RCC_BASE   + (0x34)) // RCC IOPENR register offset

.equ GPIOA_BASE,       (0x50000000)          // GPIOA base address
.equ GPIOA_MODER,      (GPIOA_BASE + (0x00)) // GPIOA MODER register offset
.equ GPIOA_ODR,        (GPIOA_BASE + (0x14)) // GPIOA ODR register offset
.equ GPIOA_IDR,        (GPIOA_BASE +(0x10)) // GPIOA_IDR register offset

.equ GPIOB_BASE,	   (0x50000400) //GPIOB base address
.equ GPIOB_MODER,      (GPIOB_BASE + (0x00)) //GPIOB MODER REG OFFSET
.equ GPIOB_ODR,        (GPIOB_BASE + (0x14)) //GPIOB_ODR REG OFFSET

.equ DELAY, 		   (0xF4240) //125 ms delay

/* vector table, +1 thumb mode */
.section .vectors
vector_table:
	.word _estack             /*     Stack pointer */
	.word Reset_Handler +1    /*     Reset handler */
	.word Default_Handler +1  /*       NMI handler */
	.word Default_Handler +1  /* HardFault handler */
	/* add rest of them here if needed */


/* reset handler */
.section .text
Reset_Handler:
	/* set stack pointer */
	ldr r0, =_estack
	mov sp, r0

	/* initialize data and bss 
	 * not necessary for rom only code 
	 * */
	bl init_data
	/* call main */
	bl main
	/* trap if returned */
	b .


/* initialize data and bss sections */
.section .text
init_data:

	/* copy rom to ram */
	ldr r0, =_sdata
	ldr r1, =_edata
	ldr r2, =_sidata
	movs r3, #0
	b LoopCopyDataInit

	CopyDataInit:
		ldr r4, [r2, r3]
		str r4, [r0, r3]
		adds r3, r3, #4

	LoopCopyDataInit:
		adds r4, r0, r3
		cmp r4, r1
		bcc CopyDataInit

	/* zero bss */
	ldr r2, =_sbss
	ldr r4, =_ebss
	movs r3, #0
	b LoopFillZerobss

	FillZerobss:
		str  r3, [r2]
		adds r2, r2, #4

	LoopFillZerobss:
		cmp r2, r4
		bcc FillZerobss

	bx lr


/* default handler */
.section .text
Default_Handler:
	b Default_Handler


/* main function */
.section .text
main:
	/* enable GPIOA and GPIOB clock */
	ldr r6, =RCC_IOPENR
	ldr r5, [r6]
	/* movs expects imm8, so this should be fine */
	movs r4, 0x3 //PORT A AND B ACTIVE
	orrs r5, r5, r4
	str r5, [r6]

	/* setup button */
	ldr r6, =GPIOA_MODER
	ldr r5, [r6]

	/* cannot do with movs, so use pc relative */

	movs r4, 0x3
	bics r5, r5, r4
	movs r4, 0x0 // 0x00 PA0 input mode
	orrs r5, r5, r4
	str r5, [r6] // store r5 data to GPIOC_MODER //PA0-Button

	/* setup LEDs */
	ldr r6, =GPIOB_MODER
	ldr r5, [r6]

	/* */
	movs r4, 0xFF //first 4 pin
	bics r5, r5, r4
	lsls r4, #0x6 // last 3 pin
	bics r5, r5, r4
	movs r4, 0x55 // first 4 pin 01010101=>0x55
	orrs r5, r5, r4
	lsls r4, #0x6 // shifting 6 times left to set last 3 pin as output
	orrs r5, r5, r4
	str r5, [r6]


	button: //connected to PA0
		ldr r6, =GPIOA_IDR
		ldr r5, [r6]
		ldr r2, =DELAY
		movs r4, #0x1 //r4=0x1
		ands r5, r5, r4 // GPIOA_IDR and r4
		cmp r5, #0x1 //if GPIOA_IDR[0]==1
		bne one_led

	one_led:
		subs r2, r2, #1
		bne one_led
		ldr r6, =GPIOB_ODR
		ldr r5, [r6]
		movs r4, #0xFF
		bics r5, r5, r4
		movs r4, #0x8
		orrs r5, r5, r4
		str r5, [r6]
		ldr r2, =DELAY
		ldr r6, =GPIOA_IDR
		ldr r5, [r6]
		movs r4, #0x1
		ands r5, r5, r4
		cmp r5, #0x1
		beq one_led
		bne three_led

	three_led:
		subs r2, r2, #1
		bne three_led
		ldr r6, =GPIOB_ODR
		ldr r5, [r6]
		movs r4, #0xFF
		bics r5, r5, r4
		movs r4, #0x1C
		orrs r5, r5, r4
		str r5, [r6]
		ldr r2, =DELAY
		ldr r6, =GPIOA_IDR
		ldr r5, [r6]
		movs r4, #0x1
		ands r5, r5, r4
		cmp r5, #0x1
		beq three_led
		bne five_led

	five_led:
		subs r2, r2, #1
		bne five_led
		ldr r6, =GPIOB_ODR
		ldr r5, [r6]
		movs r4, #0xFF
		bics r5, r5, r4
		movs r4, #0x3E
		orrs r5, r5, r4
		str r5, [r6]
		ldr r2, =DELAY
		ldr r6, =GPIOA_IDR
		ldr r5, [r6]
		movs r4, #0x1
		ands r5, r5, r4
		cmp r5, #0x1
		beq five_led
		bne seven_led

	seven_led:
		subs r2, r2, #1
		bne seven_led
		ldr r6, =GPIOB_ODR
		ldr r5, [r6]
		movs r4, #0xFF
		bics r5, r5, r4
		movs r4, #0x7F
		orrs r5, r5, r4
		str r5, [r6]
		ldr r2, =DELAY
		ldr r6, =GPIOA_IDR
		ldr r5, [r6]
		movs r4, #0x1
		ands r5, r5, r4
		cmp r5, #0x1
		beq seven_led
		bne five2_led

	five2_led:
		subs r2, r2, #1
		bne five2_led
		ldr r6, =GPIOB_ODR
		ldr r5, [r6]
		movs r4, #0xFF
		bics r5, r5, r4
		movs r4, #0x3E
		orrs r5, r5, r4
		str r5, [r6]
		ldr r2, =DELAY
		ldr r6, =GPIOA_IDR
		ldr r5, [r6]
		movs r4, #0x1
		ands r5, r5, r4
		cmp r5, #0x1
		beq five2_led
		bne three2_led

	three2_led:
		subs r2, r2, #1
		bne three2_led
		ldr r6, =GPIOB_ODR
		ldr r5, [r6]
		movs r4, #0xFF
		bics r5, r5, r4
		movs r4, #0x1C
		orrs r5, r5, r4
		str r5, [r6]
		ldr r2, =DELAY
		ldr r6, =GPIOA_IDR
		ldr r5, [r6]
		movs r4, #0x1
		ands r5, r5, r4
		cmp r5, #0x1
		beq three2_led
		bne one2_led

	one2_led:
		subs r2, r2, #1
		bne one2_led
		ldr r6, =GPIOB_ODR
		ldr r5, [r6]
		movs r4, #0xFF
		bics r5, r5, r4
		movs r4, #0x8
		orrs r5, r5, r4
		str r5, [r6]
		ldr r2, =DELAY
		ldr r6, =GPIOA_IDR
		ldr r5, [r6]
		movs r4, #0x1
		ands r5, r5, r4
		cmp r5, #0x1
		beq one2_led
		bne button


	/* this should never get executed */
	nop
