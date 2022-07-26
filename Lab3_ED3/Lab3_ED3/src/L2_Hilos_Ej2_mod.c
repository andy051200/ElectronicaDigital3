/*
 ============================================================================
 Nombre: L2_Hilos_Ej2.c
 Autor:  Luis Alberto Rivera
 Modificado para laboratario 3 parte 3
 Andy Bonilla
 Carné 19451
 Electronica digital 3
 Laboratorio 3
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

/* ============================================================================
					Código a ejecutar por el segundo hilo
 ============================================================================ */
void My_Thread2(void *ptr)
{
	char *message;				// puntero, para la cadena de caracteres (string)
	message = (char *)ptr; 		// recupera la información pasada a este hilo

	while(1)
	{
		printf("%s", message);
		fflush(stdout);
		usleep(1100000);
	}
	pthread_exit(0);			// Para salir correctamente del hilo
}

/* ============================================================================
					Código a ejecutar por el tercer hilo
 ============================================================================ */
void My_Thread3(void *ptr)
{
	char *message;					// puntero, para la cadena de caracteres (string)
		message = (char *)ptr; 		// recupera la información pasada a este hilo

	while(1)
	{
		printf("%s", message);
		fflush(stdout);
		usleep(1100000);
	}
	pthread_exit(0);
}

/* ============================================================================
					Código a ejecutar por el cuarto hilo
 ============================================================================ */
void My_Thread4(void *ptr)
{
	while(1)
	{
		sleep(5);
		printf("Mensaje Cualquiera :)\n");
	}
}

/*void My_Thread4(void *ptr)
{
	while(1)
	{
		printf("Electronica digital 3, Andy Bonilla\n");
		fflush(stdout);
		sleep(5);
	}
	pthread_exit(0);
}*/

/* ============================================================================
					Función principal (primer hilo de ejecución)
 ============================================================================ */
int main(void)
{
	pthread_t mis_hilos[3];	// variable para identificar el 2do hilo que se creará
	// Los siguientes son dos strings
	char *message1 = "Hello\n";
	char *message2 = "world\n";
	char *message3 = "llamo\n";

	// La siguiente función crea un POSIX thread (pthread), que es un hilo del
	// estándar POSIX. Los argumentos de entrada son: la variable tipo pthread,
	// configuraciones (NULL para usar las default), la función a ejecutar por
	// el hilo, y un puntero para la información que se quiere pasar al nuevo
	// hilo (NULL si no se quiere pasar nada).

	pthread_create(&mis_hilos[0], NULL, (void*)&My_Thread2, (void*)message2);	//creacion del segundo hilo
	pthread_create(&mis_hilos[1], NULL, (void*)&My_Thread2, (void*)message3);	//creacion del tercer hilo
	//pthread_create(&mis_hilos[2], NULL, (void*)&My_Thread4, NULL);				//creacion del cuarto hilo
	pthread_create(&mis_hilos[3], NULL, (void*)&My_Thread4, NULL);


	while(1)
	{
		printf("%s", message1);
		fflush(stdout);
		usleep(1000000);
	}

	return(0);
}
