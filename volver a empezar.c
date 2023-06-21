#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK         0
#define ERROR   (-1)

// estructura de la memoria: 
int * memoriatotal = NULL; // acá va la memoria total que pide el usuario
int * memoriaenuso = NULL; // memoria que se está utilizando
int * memoriarestante = NULL; //  memoria disponible para utilizar
int cantidad_bloques; //

// estructura de los bloques: 
int ** block= NULL; 
int ** identificador = NULL;
int ** cont_referencias = NULL;
char ** nombre = NULL;
int ** tamanio = NULL;
// posición en los array
int i;
int max_mem;

// funciones: 
int init(int maxmem);
int new_block(int size,char* name);
int resize(int block, int sz);
//Se agrega una referencia a un bloque de memoria existente.
int add_reference(int block);
//Se elimina una referencia a un bloque de memoria.
int remove_reference(int block);
int cur_used_memory(void);
int cur_available_memory(void);


int main(){
	int mem= 1000;
	printf("MEM mide %lld\n",sizeof(mem)); // mide 4 bytes
	init(mem);
	int sz=5;
	//char * nombrecito = "bloque A";
	int block1= new_block(sz, "bloque A"); 
	resize(1,400);
	int used_mem = cur_used_memory();
	printf("Used memory: %d\n", used_mem);
	// Prueba de available_memory
	int available_mem = cur_available_memory();
	printf("Available memory: %d\n", available_mem);
	return 0;
}
int init(int maxmem){
	i = 0;

	// se inicializan las variables dandoles memoria a cada una
	identificador = (int *)malloc(sizeof(int));
	cont_referencias =(int *)malloc(sizeof(int));
	tamanio = (int *)malloc(sizeof(int));
	nombre = (char**)malloc(sizeof(char*));
	memoriaenuso=(int *)malloc(sizeof(int));
	*memoriaenuso=0;
	memoriarestante=(int *)malloc(sizeof(int));

	// se inicializa la variable para contabilizar bloques
	cantidad_bloques =0;
	
	max_mem= maxmem; // vale 1000, puedo hacer las restas
	memoriatotal=&max_mem;

	if (memoriatotal == NULL){
		printf("No se puede asignar memoria. \n");
		return ERROR;
	} else {
		return OK;
	}	
}
int new_block(int size,char* name){
	printf("memoria total en NB: %d\n", *memoriatotal);
    printf("El valor de size es: %d\n", size);
    printf("El valor de name es: %s\n", name);
    printf("i vale %d\n", i);

    block = (int**)malloc(sizeof(int*));
    nombre[i] = (char*)malloc(sizeof(char) * (strlen(name) + 1));

    if (block != NULL && nombre[i] != NULL) {
        *block = (int*)malloc(size * sizeof(int));

        if (*block != NULL) {
            *identificador = (int*)malloc(sizeof(int));
            *cont_referencias = (int*)malloc(sizeof(int));
            *tamanio = (int*)malloc(sizeof(int));

            strcpy(nombre[i], name);
            printf("nombre: %s\n", nombre[i]);

            *identificador[i] = i + 1;
            printf("El bloque tiene id = %d\n", *identificador[i]);
            *cont_referencias[i] = 0;
            printf("El contador de referencias está iniciado en %d\n", *cont_referencias[i]);
            *tamanio[i] = size;
            printf("El tamaño es %d\n", *tamanio[i]);
			cantidad_bloques+=1;
			printf("cantidad de bloques: %d\n",cantidad_bloques);
        }
    }
	
	printf("memoria en uso: %d\n",*memoriaenuso);
   	*memoriarestante= *memoriatotal - size;
	*memoriaenuso= (*memoriaenuso) + size;
	printf("memoria en uso: %d\n",*memoriaenuso);
	printf("memoria restante: %d\n",*memoriarestante);
    printf("memoria sigue siendo %d\n", *memoriatotal);
	
    i++;
  

    return i;
}
int resize(int block, int sz){
	printf("id del bloque: %d\n",block);
	printf("size para reasignar: %d\n",sz);
	printf("memoria total es %d\n", *memoriatotal);

	if(sz < *memoriatotal){
		int position = -1;  // Inicializamos la posición como -1 para indicar que no se encontró ninguna coincidencia

		for (int j = 0; j < sizeof(**identificador); j++) {
			if (*identificador[j] == block) {
				position = j;
				break;  // Se encontró la coincidencia, se sale del bucle
			}
		}
	
		printf("La posición coincidente es: %d\n", position);
		int aux_tamanio= *tamanio[position];
		int* nuevo_tamanio = (int *) realloc(tamanio[position],sz);
		
		if(nuevo_tamanio==NULL){
			return ERROR;
		} else {
			*tamanio[position]=sz;
			//memoria en uso: 5
			//memoria restante: 995
			*memoriarestante= (*memoriarestante+aux_tamanio)-(*tamanio[position]);
			*memoriaenuso=(*memoriaenuso-aux_tamanio)+(*tamanio[position]);
			printf("tamaño ahora es: %d\n",*tamanio[position]);
			printf("memoria en uso: %d\n",*memoriaenuso);
			printf("memoria restante: %d\n",*memoriarestante);
    		printf("memoria sigue siendo %d\n", *memoriatotal);
			
			return OK;
		}

	}
}
//Se agrega una referencia a un bloque de memoria existente.
int add_reference(int block){
	int position = -1;  // Inicializamos la posición como -1 para indicar que no se encontró ninguna coincidencia

	for (int j = 0; j < sizeof(**identificador); j++) {
		if (*identificador[j] == block) {
			position = j;
			break;	// Se encontró la coincidencia, se sale del bucle
		}
	}
	
	return 0;
}

//Se elimina una referencia a un bloque de memoria.
int remove_reference(int block){
	return 0;
}
int cur_used_memory(void){
	printf("memoria en uso: %d\n",*memoriaenuso);
	return *memoriaenuso;
}
// mem total = 1000;
// mem en uso = mem total - rezise || mem total - bloque nuevo
// mem restante = mem total - mem en uso
int cur_available_memory(void){
	printf("memoria restante: %d\n",*memoriarestante);
	return *memoriarestante;
}
int destroy_agent(){
	// recorrer el array de bloques y liberar aquellos que están en 0 o null 
}