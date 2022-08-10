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

/* ============================================================================
	Directivas a ejecutar
============================================================================ */
#define bocina 17		//directiva pin de bocina
#define boton 18		//directiva pin de boton

/* ============================================================================
	Prototipos de funciones
============================================================================ */
void antirrebote(void);	//funcion con antirrebote
void switches(void);	//funcion con el switch de seleccion
void entradas(void);	//funcion con las entradas de teclado
void sonido(void);		//funcion para reproducir el sonido

/* ============================================================================
	variables a implementar
============================================================================ */
struct variables{
		int botonazo;
		int contador;
		int respaldo;
		int t_delay;
		char char1[1];
	};

/* ============================================================================
	main
============================================================================ */
int main(void)
{
	//----------------------configuracion de raspi
	WiringPiSetupGpio();			//
	pinMode(bocina, OUTPUT);			//declaracion pin de salida para bocina
	pinMode(boton, INPUT);				//declaracion pin de entrada para boton
	//----------------------struct con variables a usar
	struct variables vars;
	//----------------------inicializacion de variables a usar
	vars.botonazo=0;		//inicializacion para variable del botonazo
	vars.contador=0;		//inicializacion para variable de contador
	vars.respaldo=0;		//inicializacion para variable de respaldo

	/* =======================================================================
		Loop principal
	========================================================================= */
	while(1)
	{
			//----------------------llamado de funciones
			antirrebote();			//se invoca la funcion con el antirrebote para el boton de seleccion de frecuencias
			switches();				//se invoca la funcion con el switch de seleccionde frecuencias
			entradas();				//se invoca la funcion con las entradas de teclado
			sonido();				//se invoca la funcion para reproducir el sonido en la bocina
	}
	return(0);
}

/* ============================================================================
	Funciones
============================================================================ */

//---------------------- funcion que servira como un antirrebote
void antirrebote()
{
	struct variables vars;
	//----------------------deteccion de botonazo
	if (digitalRead(boton)==0)
	{
		vars.botonazo=1;						//antirrebote
	}
	//----------------------un tipo de antirrebote
	if (digitalRead(boton)==0 && vars.botonazo==1)
	{
		vars.contador++;
	}
}

//---------------------- funcion para switches de seleccion de frecuencias
void switches()
{
	struct variables vars;
	//switch para seleccionar frecuencias
	switch(vars.contador)
	{
		default:
			vars.contador=0;
			break;

		//encendido y apagado de pin para frecuencia 1
		case (1):
				vars.t_delay=3822;		//tiempo para reproducir un do
				break;

		//encendido y apagado de pin para frecuencia 2
		case(2):
				vars.t_delay=3033;		//tiempo para reproducir un mi
				break;

		//encendido y apagado de pin para frecuencia 3
		case(3):
				vars.t_delay=2551;		//tiempo para reproducir un sol
				break;

		//para reiniciar
		case(4):
				vars.contador=0;			//se reinicia contador para seleccionar frecuencia
				break;

	}
}

//----------------------funcion con las entradas de teclado
void entradas()
{
	struct variables vars;
	scanf("%9s", vars.char1); 					//se toma la entrada char
	if (strcmp(vars.char1, "p")==0)				//condicion si se pone p->pausa
	{
		printf("Pausar sonido");
		vars.respaldo=vars.contador;			//se guarda el valor de frecuencia seleccionado
		vars.contador=0;						//
	}
	else if (strcmp(vars.char1, "r")==0)		//condicion si se pone r->renaudar
	{
		vars.contador=vars.respaldo;
		vars.respaldo=0;
		printf("Reanudar sonido");

	}
	else if (strcmp(vars.char1, "s")==0)		//condicion si se pone s->salir
	{
		printf("Salir del programa");
		exit (-1);								//se sale del programa
	}
	else
		printf("Caracter no valido");			//condicion si se ingrese algun otro caracter
}

//----------------------funcion para reproducir
void sonido()
{
	struct variables vars;
	digitalWrite(bocina,1);		//encendido
	usleep(vars.t_delay);		//tiempo de delay para la nota seleccionada
	digitalWrite(bocina,0);		//apagado
}




