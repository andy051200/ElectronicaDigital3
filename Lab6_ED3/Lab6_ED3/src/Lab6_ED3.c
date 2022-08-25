/*
 ============================================================================
 Name        : Lab6_ED3_rec.c
 Author      : Andy Bonilla (19451)
 Version     :
 Copyright   : Electronica Digital 3
 Description : Programa para reconstruir dos archivos de texto separados
 	 	 	   segun sus lineas pares e impares
 ============================================================================
 */

/* ============================================================================
 	 Inclusion de librerias
============================================================================ */
#include <string.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sched.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/timerfd.h>
#include <time.h>
/* ============================================================================
	Directivas a ejecutar
============================================================================ */
#define MAX_LETRAS 100
#define MAX_CADENAS 60
#define milis_nanos 1000000
#define arch_impares "Lab6_primero.txt"
#define arch_pares "Lab6_segundo.txt"
#define arch_juntos "Lab6_reconstruido.txt"

/* ============================================================================
	Prototipos de funciones
============================================================================ */
void espera(int tiempo);		//un tipo delay con los timers
/* ============================================================================
	variables globales a implementar
============================================================================ */
struct variables {
	char StringArray[MAX_CADENAS][MAX_LETRAS+1]; 	//arreglo de cadenas;
	int cont1;										//contador para jalar lineas impares
	int cont2;										//contador para jalar lineas pares
};
struct variables vars;


/* ============================================================================
	Funcion para segundo hilo, leer Lab6_primero.txt
============================================================================ */
void hilo_impares(void *ptr)
{
	//----------------------declaracion de variables
	vars.cont1=0;
	//----------------------para jalar el valor del buffer
	char *buffer_cadenas;
	buffer_cadenas = (char*)ptr;
	//----------------------definicion de prioridades
	struct sched_param param;
	param.sched_priority = 20;
	//si el file descriptor es negativo, tira error
	if (sched_setscheduler(0,SCHED_FIFO,&param)==-1)
	{
		perror("Error al agendar prioridad.\n");
		exit(0);
	}
	//----------------------abrir archivo de texto
	FILE *impares = fopen("Lab6_primero.txt", "r");
	//si el file descriptor es cero, tira error
	if(impares == NULL)
	{
		perror("Error al abrir el archivo.\n");
		exit(0);
	}
	
	//----------------------configuracion y arranque de timer
	int timer_fd1 = timerfd_create(CLOCK_MONOTONIC, 0);
	struct itimerspec itval;
	itval.it_interval.tv_sec = 0;
	itval.it_interval.tv_nsec = 20000000;		//20ms
	itval.it_value.tv_sec = 0;
	itval.it_value.tv_nsec = 1000000;			//1ms
	if(	timerfd_settime(timer_fd1, 0, &itval, NULL) == 1)
	{
		perror("Error al hacer el timer.\n");
		exit(0);
	}
	
	espera(timer_fd1);
	
	//----------------------se leen valores y se guardan en buffer
	while(fgets(buffer_cadenas, MAX_LETRAS, impares) != NULL)	//se guarda en el buffer
	{
		fflush(stdout);
		espera(timer_fd1);
		vars.cont1++;											//para cambiar de linea
	}	
	//----------------------se cierra archivo y se sale de hilo
	fclose(impares);
	pthread_exit(0);



}
/* ============================================================================
	Funcion para tercer hilo, leer Lab6_segundo.txt
============================================================================ */
void hilo_pares(void *ptr)
{
	//----------------------declaracion de variables
	vars.cont2=0;
	//----------------------para jalar el valor del buffer
	char *buffer_cadenas;
	buffer_cadenas = (char*)ptr;
	//----------------------definicion de prioridades
	struct sched_param param;
	param.sched_priority = 20;
	//si el file descriptor es negativo, tira error
	if (sched_setscheduler(0,SCHED_FIFO,&param)==-1)
	{
		perror("Error al agendar prioridad.\n");
		exit(0);
	}
	//----------------------abrir archivo de texto
	FILE *pares = fopen("Lab6_segundo.txt", "r");
	//si el file descriptor es cero, tira error
	if(pares == NULL)
	{
		perror("Error al abrir el archivo.\n");
		exit(0);
	}
	//espera(timer_fd2);
	//----------------------configuracion y arranque de timer
	int timer_fd2 = timerfd_create(CLOCK_MONOTONIC, 0);
	struct itimerspec itval;
	itval.it_interval.tv_sec = 0;
	itval.it_interval.tv_nsec = 20000000;		//20 ms
	itval.it_value.tv_sec = 0;
	itval.it_value.tv_nsec = 3000000;
	if(	timerfd_settime(timer_fd2, 0, &itval, NULL) == 1)
	{
		perror("Error al hacer el timer.\n");
		exit(0);
	}
	espera(timer_fd2);
	//----------------------se leen valores y se guardan en buffer
	while(fgets(buffer_cadenas, MAX_LETRAS, pares) != NULL)	//se guarda en el buffer
	{
		fflush(stdout);
		espera(timer_fd2);
		vars.cont2++;											//para cambiar de linea
	}	
	//----------------------se cierra archivo y se sale de hilo
	fclose(pares);
	pthread_exit(0);


}
/* ============================================================================
	Funcion para cuarto hilo, juntar Lab6_primero.txt y Lab6_segundo.txt
============================================================================ */
void hilo_juntar(void *ptr)
{
	//----------------------para jalar el valor del buffer
	char *buffer_cadenas;	// puntero, para la cadena de buffer
	buffer_cadenas = (char*)ptr;
	//----------------------definicion de prioridades
	struct sched_param param;
	param.sched_priority = 20;
	//si el file descriptor es negativo, tira error
	if (sched_setscheduler(0,SCHED_FIFO,&param)==-1)
	{
		perror("Error al agendar prioridad.\n");
		exit(0);
	}
	
	//----------------------configuracion y arranque de timer
	int timer_fd3 = timerfd_create(CLOCK_MONOTONIC, 0);
	struct  itimerspec itval;
	itval.it_interval.tv_sec = 0;
	itval.it_interval.tv_nsec = 10000000;	//10ms
	itval.it_value.tv_sec = 0;
	itval.it_value.tv_nsec = 2000000;
	if (timerfd_settime(timer_fd3, 0, &itval, NULL) == 1){
		perror("Error al hacer el timer.\n");
		exit(0);
	}
	espera(timer_fd3);
	//----------------------for para juntar ambos textos desde el buffer
	int i=0;
	for(i = 0; i < 59 ; i++)
	{
		strcpy(vars.StringArray[i], buffer_cadenas);
		espera(timer_fd3);
		//puts(vars.StringArray[i]);
	}
	//----------------------se sale del hilo
	pthread_exit(0);
}
/* ============================================================================
	main
============================================================================ */
int main(void) 
{
	//----------------------mensaje inicial
	puts("Programa para reconstruir dos textos separados según sus lineas pares e impares\n");
	//----------------------inicializacion de variables para hilos
	char *buffer[MAX_LETRAS];					//buffer comun para los hilos
	pthread_t var_hilo2, var_hilo3, var_hilo4;
	//----------------------inicializacion de hilos
	pthread_create(&var_hilo2, NULL, (void*)&hilo_impares, (void*)buffer);
	pthread_create(&var_hilo3, NULL, (void*)&hilo_pares, (void*)buffer);
	pthread_create(&var_hilo4, NULL, (void*)&hilo_juntar, (void*)buffer);
	//----------------------pedazo para unir los textos
	pthread_join(var_hilo2,NULL);	//espera a terminar impares
	pthread_join(var_hilo3,NULL);		//espera a terminar pares
	pthread_join(var_hilo4,NULL);		//espera a juntar ambos
	//----------------------creacion y union de lineas impares y pares
	FILE *juntos = fopen(arch_juntos, "w");
	//----------------------almacenamiento en archivo nuevo
	int i=0;
	for(i = 0; i < 59 ; i++)
	{
		fputs(vars.StringArray[i], juntos);
		puts(vars.StringArray[i]);
	}
	fclose(juntos);		//se cierra el nuevo archivo
	

	printf("\nNúmero total de líneas leídas: %d\n", vars.cont1+vars.cont2);
	printf("\nReconstruicción Completa\n");
	return 0;
}

/* ============================================================================
	Funciones
============================================================================ */

//----------------------funcion para tiempo de espera
void espera(int tiempo)
{
	uint64_t periodos=0;

	if(read(tiempo,&periodos,sizeof(periodos))==-1)
	{
		perror("Error al leer el timer");
		exit(1);
	}
	if (periodos>1)
	{
		puts("Se pasó el tiempo");
		exit(1);
	}
}
