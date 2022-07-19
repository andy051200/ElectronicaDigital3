/*
 ============================================================================
 Name        : Lab2_ED3.c
 Author      : Andy Bonilla
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int var1 = 0; 				//variable inic
	for (var1;var1<21;var1++) 	//ciclo for pedido en la guia
		{
			printf("El valor del contador es: %d\n",var1); //salida en consola del valor del contador
			sleep(1);
		}
	printf("Muchas gracias por el tiempo, feliz dia\n");
	return 0;
}
