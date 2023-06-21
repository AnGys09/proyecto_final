#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "garbage.h"
#include <time.h>
int block=0; // Cantidad de bloques
int ** id; // array, donde se van a guardar los id de los bloques
int ** count_reference;
int ** size;
char * block_name;

int * max_memory=NULL;
int available;
int in_use;
int bloquesTotalesCreados = 0;

int init(int maxmem);
int new_block(int size,char* name);

int main(){
	int mem= 1000;
	printf("MEM mide %d\n",sizeof(mem)); // mide 4 bytes
	init(mem);
	int sz=5;
	char * nombrecito = "bloque A";
	new_block(sz, nombrecito);
}

int init(int maxmem){
	int response; 
	void * punterogenerico = malloc(maxmem * sizeof(int));  // devuelve la direccón de memoria de donde comienza el bloque
	if (punterogenerico == NULL){
		response = -1;
	} 
	max_memory= &punterogenerico; // mide 1000 y con ello puedo hacer las restas.
	printf("max memory mide: %n\n",&max_memory); // 1000
	return response;
}

int new_block(int sz,char* name){
	int response;
	// -- debug --
	printf("hay %d bloques\n",block); // 0
	printf("size nuevo es: %d\n y char es: %s\n",sz, name); // 5 y bloque A
	printf("size global es: %n\n",size);
	// -----------------------
	// al bloque debo asignarle la dirección de memoria de max_memory si es el primero y sino correrme hasta el lugar siguiente al size
	// hay que usar un doble puntero, es decir, puntero a puntero
	int block_size = max_memory - (block * sizeof(int) + block * sizeof(char) + block * sizeof(int));
	void *block_memory = (char *)max_memory - block_size; 

	*id = (int *)(max_memory - sizeof(int));
	*count_reference = (int *)(max_memory - sizeof(int) * 2);
	*size = (int *)(max_memory - sizeof(int) * 3);
	**id = block + 1; // Incrementa el ID del bloque
	strcpy(block_name, name); // Asigna un nombre al bloque
	**size = sz; // Asigna un tamaño al bloque (menor a 1000)

	printf("DEBUG NUEVOS---\n ");
	printf("block size: %d\n block memory: %n\n",block_size, block_memory);
	printf("id: %n; name: %s; size: %n;\n",id, name, size);
	printf("los punteros: id = %n; block name = %s, size puntero = %n",*id, block_name, *size);

	

    return 0;



	//printf("global id es: %d\n",id[bloquesTotalesCreados]);
	/* if(size+sz <= max_memory){ // si la variable global SIZE + el length del nuevo bloque son menor o igual al total de memoria
		// armo el bloque
		
		
		id[bloquesTotalesCreados]= bloquesTotalesCreados+1;

		bloquesTotalesCreados= bloquesTotalesCreados+1;
		block=block+1;
		size= size+sz;
		block_name= name;
		response = 0;
		
	}else {
		printf("No se puede asignar bloque. \n");
		response = -1;
	}
	//block= &cant_bloques;
	printf("El bloque es: block= %d, con tamaño %d, con id %d, y el nombre del bloque es %s\n",block,size,id,block_name);
	return response;  */

}