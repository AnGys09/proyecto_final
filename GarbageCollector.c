#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "garbage.h"

//Declarar las variables del módulo
// Cada bloque será una estructura con 4 datos: 
typedef struct
{
	int id;						// identificador
	int count_reference;		// contador de referencias
	char name[];				// nombre del bloque
	int size;					// tamaño del bloque
} block;

// Cada garbage colector será una estructura con 3 datos: 
typedef struct 
{
	int memory;			// Cantidad de memoria a reservar
	int available;		// Cantidad de memoria disponible 
	int block; 			// Cantidad de bloques
} garbageCollector;

/********************************************************************/

int init_gc(int max_mem)
{
	//TODO : reserva la memoria del tamaño que tiene max_mem
	void* init_gc = malloc(sizeof(max_mem));
	if(init_gc == NULL){
		printf("Error: La memoria está llena");
	} 
	return init_gc;
	
}

int new_block(int sz,char* name)
{
    //TODO: recibe el size de la memoria que necesita y el nombre del bloque, esa es la referencia?

	// ESta funcion es para inicializar un bloque. Esta función retorna un Integer. La idea es que cuando pueda incializarlo, debido a que la memoria que necestia el bloque
	// es menor a la memoria total, en ese caso vos retornes un Integer que sea un identificador del bloque. Y si no se puede inicializar, en ese caso tenes que devolver un identificador
	// inválido ( acá podes definir vos qué número va a corresponder a un ID invalido, por ejemplo, podría ser 0 o -1 , sería lo más común)
	int block; //puede ser un puntero a la memoria y que el identificador sea la dirección de momoria;

	return block;
}

int* mem_ptr(int block)
{
    //TODO: puntero a la memoria total, modifica su valor a medida que se agregan bloques 
}

int resize(int block, int sz)
{
    //TODO: recibe un block, y modifica su size, por ejemplo si el size de block2 es 300, el nuevo size debe ser 400. Devuelve OK  (con un CERO) o ERROR ( sería un -1)
}

int add_reference(int block)
{
    //TODO: es el contador de referencias, cada vez que se carga una variable a este bloque o que se asigna el identificador a una nueva varible 
}

int remove_reference(int block)
{
    //TODO
	// si el contador de referencias de un bloque llega a 0, entonces, tengo que liberar la memoria de ese bloque. Y eso lo tengo que hacer acá, tal vez podes crear otra función que haga eso
	// e invocarla acá
}

int cur_used_memory(void)
{
    //TODO: cantidad de memoria utilizada, suma de los bloques 
}

int cur_available_memory(void)
{
    //TODO: cantidad de memoria disponible, memoria total - memoria utilizada
}


int destroy_agent()
{
    //TODO: si todos los bloques están con referencias en 0, se libera el total de la memoria 
}