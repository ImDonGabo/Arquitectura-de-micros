/*
 * main.s
 *
 *  Created on: Jan 29, 2025
 *      Author: Gabriel Valle y Katya Torres
 */

/* This assembly file uses GNU syntax */
	.text
	.section .rodata
	.align 2
	.data

	johnson_array: .byte 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80, 0x00
	walk_array: .byte 0x80, 0x40, 0x20, 0x10, 0x8, 0x4, 0x2, 0x1, 0x00

.LC0:
	.text
	.align 2
	.global main
	.type main, %function

// Direcciones de registros (ver manual)
AHBCLKCTRL0  = 0x40000200  	// Table 38. SYSCON (base address = 0x50000000)
MUX_GPIO1    = 0x40001090  	// Table 333. I/O configuration (base address = 0x40001000)
GPIO_DIR     = 0x4008E004  	// Table 344. GPIO port (base address = 0x4008C000)
GPIO_PIN 	 = 0X4008E104

TOGGLE_P1 	 = 0x4008E304 	//Table 344. Register overview: GPIO port (base address 0x4008 C000)
SET_P1    	 = 0x4008E204  	// Table 344. GPIO port (base address = 0x4008C000)
CLEAR_P1 	 = 0x4008E284	// Table 344. GPIO port (base address = 0x4008C000)

// Máscaras (bit values) para configurar registros
IOCON         = 1<<13
GPIO1         = 1<<15
CLOCKS        = (GPIO1 | IOCON)
IOCON_REGISTER= ~(0x000F)   	// Limpia los bits de la configuración de los pines

// Definiciones de pines para los LEDs
GPIO1_PINS = 0xFF
PIN26 = 0x4000000
PIN27 = 0x8000000
PIN2627 = 0xC000000
DELAY = 0xFFFFFF 	// Retardo (ajustar para modificar la velocidad)


main:
	push {r3, lr}
	add r3, sp, #4

	// Init IOCON and GPIO1 Clocks
	ldr r1, = AHBCLKCTRL0
	ldr r3, = CLOCKS
	ldr r2, [r1]
	orr r3, r2
	str r3, [r1]

	ldr r1, = 0X400010E8
	ldr r3, = 1<<8
	ldr r2, [r1]
	orr r3, r2
	str r3, [r1]

	ldr r1, = 0X400010EC
	ldr r3, = 1<<8
	ldr r2, [r1]
	orr r3, r2

	str r3, [r1]

	// Assign Mux as GPIO
	ldr r1, = MUX_GPIO1
	ldr r3, = IOCON_REGISTER
	ldr r2, [r1]
	and r3, r2
	str r3, [r1]

	// GPIO as output
	ldr r1, = GPIO_DIR
	ldr r3, = GPIO1_PINS  // Configurar los pines como salida
	ldr r2, [r1]
	orr r3, r2
	str r3, [r1]
	ldr r2, [r1]
	and r3, r2
	str r3, [r1]

deepswitch:
	ldr r6, = CLEAR_P1
	ldr r4, = GPIO1_PINS
	str r4, [r6]
	ldr r1, = GPIO_PIN
	ldr r2, [r1]
	cmp r2, #0x0
	beq deepswitch
	ldr r1, = GPIO_PIN
	ldr r2, [r1]
	ldr r3, = PIN26
	cmp r2, r3
	beq initcounter
	ldr r1, = GPIO_PIN
	ldr r2, [r1]
	ldr r3, = PIN27
	cmp r2, r3
	beq initwalk
	ldr r1, = GPIO_PIN
	ldr r2, [r1]
	ldr r3, = PIN2627
	cmp r2, r3
	beq initjohnson
	bl [deepswitch]

initcounter:
	//init counter
	mov r7, #0x00
	bl [loop1]

initwalk:
	//set arrays
	ldr r5, = walk_array
	bl [loop2]

initjohnson:
	//set arrays
	ldr r5, = johnson_array
	bl [loop3]

loop1:
	bl [delay]
	bl [cuenta]
	ldr r1, = GPIO_PIN
	ldr r2, [r1] //cargar el valor actual del deepswitch
	cmp r2, r3 //comparar con el registro de la funcion actual
	beq [loop1] //si sigue siendo igual se mantiene en la funcion
	bl [deepswitch] //si cambia sale al menu de deepswitch

cuenta:
	//r7 has the counter
	// Turn off leds
	ldr r6, = CLEAR_P1
	ldr r4, = GPIO1_PINS
	str r4, [r6]
	//8bit Counter
	ldr r6, = SET_P1
	str r7, [r6]
	add r7, #1
	cmp r7, #0xFF
	beq initcounter
	bx lr

loop2:
	bl [delay]
	bl [caminata]
	ldr r1, = GPIO_PIN
	ldr r2, [r1]
	cmp r2, r3
	beq [loop2]
	bl [deepswitch]

caminata:
	ldr r6, = TOGGLE_P1
	ldrb r4, [r5]
	add r5, #1
	str r4, [r6]
	cmp r4, #0
	beq initwalk
	bx lr

loop3:
	bl [delay]
	bl [johnson]
	ldr r1, = GPIO_PIN
	ldr r2, [r1]
	cmp r2, r3
	beq [loop3]
	bl [deepswitch]

johnson:
	ldr r6, = TOGGLE_P1
	ldrb r4, [r5]
	add r5, #1
	str r4, [r6]
	cmp r4, #0
	beq initjohnson
	bx lr


delay:
	ldr r0, = DELAY

counter:
	sub r0, #1
	cmp r0, #0
	bne counter
	bx lr

