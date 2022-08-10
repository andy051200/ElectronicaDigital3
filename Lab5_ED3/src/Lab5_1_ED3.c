/*
 ============================================================================
 Name        : Lab5_ED3.c
 Author      : Andy Bonilla
 Version     : Para ejercicio 1, parte 3
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


/* ============================================================================
 	 Inclusion de librerias
============================================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
//#include <wiringPi.h>

/* ============================================================================
	Directivas a ejecutar
============================================================================ */
#define LED1 17		//directiva para led 1
#define LED2 18		//directiva para led 2

/* ============================================================================
	Funcion para segundo hilo
============================================================================ */
void hilo2(void *ptr)
{
	while(1)
	{
		int tiempo2;									//variable local para numeros aleatorios
		tiempo2 = rand() % (1501-500+1) + 501;			//numero aleatorios entre 0.5s y 1.5s
		//digitalWrite(LED2, 1);							//encendido de led 2
		printf("El numero random 2 es %d\n", tiempo2);	//mensaje para asegurarse
		sleep(1);								//tiempo de delay random
		//digitalWrite(LED2, 0);							//apagado de led 2
	}
}

/* ============================================================================
	main
============================================================================ */
int main(void) {
	pthread_t variable_hilo2;				//variable para identificar el segundo hilo
	pthread_create(&variable_hilo2, NULL, (void*)&hilo2, NULL);
	/*WiringPiSetupGpio();			//
	pinMode(LED1, OUTPUT);			//declaracion de primer pin de salida
	pinMode(LED2, OUTPUT);			//declaracion de segundo pin de salida*/

	while(1)
	{
		int tiempo1;									//creacion de variables locales para almacenar numeros aleatorios
		tiempo1 = rand() % (1500-500+1) + 500;			//numero aleatorios entre 0.5s y 1.5s
		//digitalWrite(LED1, 1);						//encendido de led 1
		printf("El numero random 1 es %d\n", tiempo1);	//mensaje para asegurarse
		sleep(1);								//tiempo de delay random
		//digitalWrite(LED1, 0);							//apagado de led 1

	}
	return(0);
}








