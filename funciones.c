#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "garbage.h"
#include <time.h>
//#include "estructuras.h"
#define OK         0
#define ERROR   (-1)


typedef struct
{
	int *id;						// identificador
	int count_reference;		// contador de referencias
	char *name;				// nombre del bloque
	int size;					// tamaño del bloque
} block;
block new_block2;

//Inicializacion del GC. Se indica cantidad de memoria.

int init_gc(int max_mem){
	//TODO : reserva la memoria del tamaño que tiene max_mem
	
	void* init_gc=(int*)malloc(sizeof(max_mem));
	if(init_gc == NULL){
		printf("Error: La memoria está llena /n");
	} 	
	return 0;
	
}
int* Random() {
    int* numRandom = malloc(3 * sizeof(int));
    if (numRandom == NULL) {
        printf("Error: No se puede asignar memoria para numRandom.\n");
        return NULL;
    }

    srand(time(NULL));
    for (int i = 0; i <= 2; i++) {
        numRandom[i] = rand() % 8;
        printf("%d", numRandom[i]);
    }

    return numRandom;
}
//Creacion de un nuevo bloque de memoria.
int new_block (int size, char *name) {
    block new_block = (block)malloc(sizeof(block));
    
    if (new_block == NULL) {
        printf("Error: No se puede asignar memoria para el nuevo bloque.\n");
        return -1;
    }
    
    new_block->size = size;
    new_block->name = name;
    new_block->id = Random(); // Podemos asignar un valor específico al id o dejarlo en 0
	printf("New block: %d/n   , %s /n  ",new_block->size,new_block->name);

    return 0;
}
int main() {
	init_gc(1000);
    new_block(10, "Block 1");

    return 0;
}