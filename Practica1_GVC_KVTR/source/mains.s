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

	array_source: .byte 0x31, 0x32, 0x33, 0x34, 0x00
	array_destination: .byte 0x30, 0x32, 0x33, 0x34, 0x00
	array_size = 0x4
	array_flag = 0x0

.LC0:
	.text
	.align 2
	.global main
	.type main function

main:
	push {r3, lr}
	add r3, sp, #4

	/* Cargar parámetros para MemCopy */
	ldr r0, =array_source      /* r0 = puntero fuente */
	ldr r1, =array_destination /* r1 = puntero destino */
	mov r2, #array_size        /* r2 = tamaño a copiar (4 bytes) */
	mov r4, #array_flag			/* r4 = 0x0, la usamos como bandera */

	//bl MemCopy                 /* llamar a MemCopy */
	//bl Strcmp					/*llamar a Strcmp */
	bl Strlen            		/* llamar a Strlen */

	mov r0, #0                 /* valor de retorno 0 */
	pop {r3, pc}               /* restaurar registros y retornar */

	/* your code goes here */

MemCopy:
/*Copia datos del apuntador fuente al apuntador destino. Esta función recibe 3
parámetros; 2 apuntadores, fuente y destino, y la cantidad de datos a copiar.*/
	cmp r2, #0                 /* verificar si el tamaño es cero */
	beq out                     /* si es cero, salir BRANCH IF EQUAL OUT */
	ldrb r3, [r0]   /* Cargar byte desde fuente */
	add r0, #1  	/* Incrementar puntero fuente */
	strb r3, [r1]  	/* Almacenar byte en destino */
	add r1, #1  	/* Incrementar puntero destino */
	sub r2, #1 		/* Decrementar contador */
	b MemCopy       /* repetir si no es cero BRANCH IF NOT EQUAL loop */

out:
	bx lr

Strcmp:
/* Compara dos cadenas de caracteres, regresa un 0 si son iguales, un 1 si son diferentes.
La función recibe dos parámetros, que son los apuntadores de las cadenas a comparar. Regresa
el resultado de la operación.*/
	cmp r2, #0			/* compara el registro dos con 0*/
	beq loopsalida		/* BRANCH IF EQUAL a loopsalida */
	ldrb r3, [r0]		/* carga byte del arreglo fuente */
	add r0, #1			/* se mueve al siguiente byte del arreglo fuente*/
	ldrb r5, [r1]		/* carga byte del arreglo destino*/
	add r1, #1			/* se mueve al siguiente byte del arreglo destino*/
	cmp r3, r5			/* compara los bytes de los arr	eglos fuente y destino*/
	bne not_equal		/* si no son iguales, salir BRANCH IF NOT EQUAL not_equal*/
	sub r2, #1			/* Decrementa tamaño de tamaño de arreglo*/
	b Strcmp			/* repite loop */

not_equal:
	add r4, #1			/* Hace al registro 4 = 1*/
	b loopsalida		/* SALIR */

loopsalida:
	bx lr				/* SALIR */

Strlen:
/* Calcula el tamaño de una cadena de caracteres (sin incluir el carácter nulo). Recibe de
parámetro un apuntador. Regresa la cantidad de caracteres. */
	ldrb r3, [r0]		/* Carga en el registro 3 el primer objeto del arreglo */
	cmp r3, #0x00		/* Compara el registro 3 con 0 */
	beq loopout			/* BRANCH IF EQUAL => loopout */
	add r4, #1			/* Suma 1 al contador */
	add r0, #1			/* Se mueve de posicion en el arreglo */
	b Strlen			/* Repite loop */

loopout:
	bx lr				/* SALIR */





