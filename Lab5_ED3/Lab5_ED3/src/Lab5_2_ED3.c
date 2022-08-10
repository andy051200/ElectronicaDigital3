/*
 ============================================================================
 Name        : Lab5_ED3.c
 Author      : Andy Bonilla
 Version     : Para ejercicio 2, parte 3
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
#include <string.h>

/* ============================================================================
	Directivas a ejecutar
============================================================================ */
#define boton 7				//directiva pin de boton
#define bocina 9			//directiva pin de bocina

/* ============================================================================
	struct para variables a implementar
============================================================================ */
struct variables{
		int contador;		//para poder encender la bocina
		char1[1];			//para los valores a ingresar del teclado
	};
struct variables vars;
/* ============================================================================
	Funcion para segundo hilo
============================================================================ */

void hilo2(void *ptr)
{
	/* =======================================================================
		Loop secundario de hilo 2
	========================================================================= */
	while(1)
	{
		printf("Ingrese los comandos: p-pausa, r-reanudar, s-salir:\n");
		scanf("%9s", vars.char1); 						//se toma la entrada char
		if (strcmp(vars.char1, "p")==0)					//condicion si se pone p->pausa
		{
			printf("Pausar sonido\n");
			vars.contador=0;							//hace que en el main loop no suene
		}
		else if (strcmp(vars.char1, "r")==0)			//condicion si se pone r->renaudar
		{
			vars.contador=5;
			printf("Reanudar sonido\n");				//reanuda en el main loop
		}
		else if (strcmp(vars.char1, "s")==0)			//condicion si se pone s->salir
		{
			printf("Salir del programa\n");
			exit (-1);									//se sale del programa
		}
		else
			printf("Caracter no valido\n");				//condicion si se ingrese algun otro caracter
	}		
}
/* ============================================================================
	main
============================================================================ */
//----------------------struct con variables gloables a usar
int main(void)
{
	//----------------------configuracion de raspi
	wiringPiSetup();									//se incluye directiva por defecto
	pinMode(bocina, OUTPUT);							//declaracion pin de salida para bocina
	pinMode(boton, INPUT);								//declaracion pin de entrada para boton
	//----------------------inicializacion de variables a usar
	vars.contador=0;									//inicializacion para variable de contador
	//----------------------inicializacion de segundo hilo
	pthread_t variable_hilo2;							//variable para identificar el segundo hilo
	pthread_create(&variable_hilo2, NULL, (void*)&hilo2, NULL);
	/* =======================================================================
		Loop principal
	========================================================================= */
	while(1)
	{
			//----------------------llamado de funciones
			if (digitalRead(boton)==0 )
			{
				vars.contador++;
			}
			if (vars.contador>0)
			{
				digitalWrite(bocina,1);		//encendido
				usleep(1000);				//delay de 1ms
				digitalWrite(bocina,0);		//apagado
				usleep(1000);
			}
			else if (vars.contador==0)
			{
				digitalWrite(bocina,0);		//apagado
			}
	}
	return(0);
}