#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define OK         0
#define ERROR   (-1)

// estructura de la memoria: 
int * memoriatotal = NULL;
void * memoriaenuso = NULL;
void * memoriarestante = NULL;
void * cantidad_bloques = NULL;

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

int main(){
	int mem= 1000;
	printf("MEM mide %lld\n",sizeof(mem)); // mide 4 bytes
	init(mem);
	int sz=5;
	//char * nombrecito = "bloque A";
	int block1= new_block(sz, "bloque A"); 
	resize(1,400);
}
int init(int maxmem){
	i = 0;
	//memoriatotal = malloc(maxmem);
	printf("memoria sz: %lld\n",sizeof(memoriatotal)); // dirección de memoria

	// se inicializan las variables dandoles memoria a cada una
	identificador = (int *)malloc(sizeof(int));
	cont_referencias =(int *)malloc(sizeof(int));
	tamanio = (int *)malloc(sizeof(int));
	nombre = (char**)malloc(sizeof(char*));
	
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
        }
    }

    *memoriatotal -= size;
    printf("memoria ahora no es 1000, es %d\n", *memoriatotal);
	
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
		int* punteroPrueba = (int *) realloc(tamanio[position],sz);
		
		if(punteroPrueba==NULL){
			return ERROR;
		} else {
			*tamanio[position]=sz;
			*memoriatotal= (*memoriatotal+aux_tamanio)-(*tamanio[position]);
			printf("tamaño ahora es: %d\n",*tamanio[position]);
			printf("memoria total es %d\n", *memoriatotal);
			return OK;
		}

	}
}
int cur_used_memory(void){
	return memoriaenuso;
}
// mem total = 1000;
// mem en uso = mem total - rezise || mem total - bloque nuevo
// mem restante = mem total - mem en uso

