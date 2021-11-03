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


.equ RCC_BASE,         (0x40021000)          // RCC base address
.equ RCC_IOPENR,       (RCC_BASE   + (0x34)) // RCC IOPENR address=0x34 page174 IO Port clock enable register RCC_IOPENR

.equ GPIOA_BASE,       (0x50000000)          // GPIOC base address
.equ GPIOA_MODER,      (GPIOA_BASE + (0x00)) // GPIOC MODER register offset
.equ GPIOA_ODR,        (GPIOA_BASE + (0x14)) // GPIOC ODR register offset


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
	/* enable GPIOA clock, bit2 on IOPENR */
 	ldr r6, =RCC_IOPENR
	ldr r5, [r6] //r5 HOLDS RCC_IOPENR REGISTER DATA
	/* movs expects imm8, so this should be fine */
	movs r4, 0x1 // r4 holds  0001
	orrs r5, r5, r4 // orr 0100 to make second bit of RCC_IOPENR
	str r5, [r6] //store r5 reg data to address r6

	/* setup PC6 for led 01 for bits 12-13 in MODER */
	ldr r6, =GPIOA_MODER //r6 holds the GPIOA_MODER ADDRESS
	ldr r5, [r6] //r5 holds GPIOA_MODER DATA
	/* cannot do with movs, so use pc relative */
	movs r4, 0x3 // r4 holds 0011
	bics r5, r5, r4 //bitclear
	movs r4, 0x1 // r4 holds 0001
	orrs r5, r5, r4 // orr with r5
	str r5, [r6] // store r5 data to GPIOA_MODER

	ldr r6, =GPIOA_ODR // r6 holds GPIOA_ODR address
	ldr r5, [r6] //r5 holds GPIOA_ODR data
led_loop: //branch
  	movs r4, 0x1 // r4 holds 0001
	orrs r5, r5, r4 // orr with r5
	str r5, [r6] //r5 holds GPIOA_ODR data

	ldr r2,=0x28B0AA //r2 holds decimal 2666666 (for 1 sn blinking)
led_on:  //branch
	subs r2,r2, #1 //decrease 1 from r2
	bne led_on //go to led_on branch (if branch not equal)

	movs r4, 0x0 //r4 holds 0000
	ands r5, r5, r4 // and with r5
	str r5, [r6] //r5 holds GPIOA_ODR data (data reset)

	ldr r2,=0x28B0AA //r2 holds decimal 2666666 (for 1 sn blinking)
led_off:  //branch
	subs r2,r2, #1 //decrease 1 from r2 
	bne led_off //go to led_off branch (if branch not equal)

	b led_loop //go to led_loop branch
	
	/* for(;;); */
	b .

	/* this should never get executed */
	nop

