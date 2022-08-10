/*
 ============================================================================
 Name        : Lab5_ED3.c
 Author      : Andy Bonilla
 Carne		 : 19451
 Curso		 : Electrónica Digital 3
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
#include <wiringPi.h>

/* ============================================================================
	Directivas a ejecutar
============================================================================ */
#define LED1 8		//directiva para led 1
#define LED2 9		//directiva para led 2


/* ============================================================================
	main
============================================================================ */

int main(void) {
	wiringPiSetup();			//
	pinMode(LED1, OUTPUT);									//declaracion de primer pin de salida
	pinMode(LED2, OUTPUT);									//declaracion de segundo pin de salida
	
	int tiempo1;			//inicializacion de tiempos aleatorios
	while(1)
	{
		tiempo1 = rand() % (1500000-500000+1) + 500001;		//numero aleatorios entre 0.5s y 1.5s
		digitalWrite(LED1, HIGH);							//encendido de led 1
		digitalWrite(LED2, LOW);							//apagado de led 2
		printf("El numero random 1 es %d\n", tiempo1);		//mensaje para asegurarse
		usleep(tiempo1);									//tiempo de delay random
		digitalWrite(LED1, LOW);							//apagado de led 1
		digitalWrite(LED2, HIGH);							//apagado de led 1
		usleep(tiempo1);									//tiempo de delay random

	}
	return(0);
}








