#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "garbage.h"
#include <time.h>
int block=0; // Cantidad de bloques
int id[]; // array, donde se van a guardar los id de los bloques
int * count_reference= 0;
int size;
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
	void * punterogenerico = malloc(maxmem * sizeof(int)); 
	if (punterogenerico == NULL){
		response = -1;
	} else {
		punterogenerico = NULL;
		response=0;
	}
	max_memory= maxmem; // mide 1000 y con ello puedo hacer las restas.
	return response;
}

int new_block(int sz,char* name){
	int response;
	// -- debug --
	printf("max memory mide: %d\n",max_memory);
	printf("global id es: %d\n",id[bloquesTotalesCreados]);
	printf("hay %d bloques\n",block);
	printf("size es: %d\n y char es: %s\n",sz, name);
	// -----------------------

	if(size+sz <= max_memory){ // si la variable global SIZE + el length del nuevo bloque son menor o igual al total de memoria
		// armo el bloque
		printf("es mas chico\n");
		// id [0] = 0 +1 
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
	return response; 

}