/* #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "garbage.h"

//Declarar las variables del módulo
int * id=0;
int * count_reference= 0;
int size;
char * name;

int * max_memory=NULL;
int available;
int in_use;
int *block;

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

/*int init_gc(int max_mem)
{
	//TODO : reserva la memoria del tamaño que tiene max_mem
	int response; // será el valor de respuesta en el return: si es OK retorna 0, y si es ERROR, -1
	void * init_gc = malloc(max_mem * sizeof(int));

	//Si hay espacio o no, se devolverá lo que se asigne a response.
	if (init_gc == NULL){
		printf("No se puede asignar memoria. \n");
		response = -1;
	} else {
		init_gc = NULL;
		response=0;
	}

	max_memory= max_mem; // se asigna el valor a la variable global para ser utilizada en otras funciones.
	return response;

}

int new_block(int sz,char* name)
{
	//TODO: recibe el size de la memoria que necesita y el nombre del bloque, esa es la referencia?

	// ESta funcion es para inicializar un bloque.
	//Esta función retorna un Integer. La idea es que cuando pueda incializarlo, debido a que la memoria que necestia el bloque
	// es menor a la memoria total, en ese caso vos retornes un Integer que sea un identificador del bloque.
	//Y si no se puede inicializar, en ese caso tenes que devolver un identificador
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
} */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "garbage.h"
#define OK 0
#define ERROR (-1)

// estructura de la memoria:
int *memoriatotal = NULL;	 // acá va la memoria total que pide el usuario
int *memoriaenuso = NULL;	 // memoria que se está utilizando
int *memoriarestante = NULL; //  memoria disponible para utilizar
int cantidad_bloques;		 //

// estructura de los bloques:
int **array_block = NULL;
int **identificador = NULL;
int **cont_referencias = NULL;
char **nombre = NULL;
int **tamanio = NULL;
// posición en los array
int i;
int max_mem;

// funciones:
int init_gc(int maxmem);
int new_block(int size, char *name);
int resize(int block, int sz);
// Se agrega una referencia a un bloque de memoria existente.
int add_reference(int block);
// Se elimina una referencia a un bloque de memoria.
int remove_reference(int block);
int cur_used_memory(void);
int cur_available_memory(void);
int destroy_agent();

/*int main()
{
	 int mem= 1000;
	printf("MEM mide %lld\n",sizeof(mem)); // mide 4 bytes
	init(mem);
	int sz=5;
	//char * nombrecito = "bloque A";
	int block1= new_block(sz, "bloque A");
	resize(1,400);
	add_reference(block1);
	add_reference(block1);
	remove_reference(block1);
	remove_reference(block1);
	int used_mem = cur_used_memory();
	printf("Used memory: %d\n", used_mem);
	// Prueba de available_memory
	int available_mem = cur_available_memory();
	printf("Available memory: %d\n", available_mem);
	destroy_agent();
	return 0; */
int main()
{
	int max_mem = 1000;
	int block1, block2, block3, block4;

	// Prueba de init_gc
	init_gc(max_mem);

	// Prueba de new_block
	block1 = new_block(200, "Block 1"); // en uso = 200, disponible= 800  id=1
	block2 = new_block(300, "Block 2"); // en uso = 500 , disponible = 500  id=2
	block3 = new_block(150, "Block 3"); // en uso = 650, disponible = 350  id=3
	block4 = new_block(400, "Block 4"); // en uso= 650 , no se puede asignar;  

	// Prueba de resize
	resize(block2, 400);
	resize(block4, 250);

	// Prueba de add_reference
	add_reference(block1);
	add_reference(block2);
	add_reference(block2); // Agregar dos referencias al mismo bloque
	add_reference(block3);

	// Prueba de remove_reference
	remove_reference(block2);
	remove_reference(block2); // Quitar una referencia más al mismo bloque

	// Prueba de used_memory
	int used_mem = cur_used_memory();
	printf("Used memory: %d\n", used_mem);

	// Prueba de available_memory
	int available_mem = cur_available_memory();
	printf("Available memory: %d\n", available_mem);

	// Prueba de destroy_agent
	destroy_agent();
	return 0;
}

int init_gc(int maxmem)
{
	i = 0;

	// se inicializan las variables dandoles memoria a cada una
	identificador = (int *)malloc(sizeof(int));
	cont_referencias = (int *)malloc(sizeof(int));
	tamanio = (int *)malloc(sizeof(int));
	nombre = (char **)malloc(sizeof(char *));
	memoriaenuso = (int *)malloc(sizeof(int));
	*memoriaenuso = 0;
	memoriarestante = (int *)malloc(sizeof(int));

	// se inicializa la variable para contabilizar bloques
	cantidad_bloques = 0;

	max_mem = maxmem; // vale 1000, puedo hacer las restas
	memoriatotal = &max_mem;
	*memoriarestante = *memoriatotal;

	if (memoriatotal == NULL)
	{
		printf("No se puede asignar memoria. \n");
		return ERROR;
	}
	else
	{
		return OK;
	}
}
int new_block(int size, char *name)
{
	printf("memoria total en NB: %d\n", *memoriatotal);
	printf("El valor de size es: %d\n", size);
	printf("El valor de name es: %s\n", name);
	printf("i vale %d\n", i);

	// Primero me fijo si hay memoria disponible:
	printf("memoria en uso: %d\n", *memoriaenuso);

	if ((size <= *memoriarestante))
	{

		array_block = (int **)realloc(array_block, (i + 1) * sizeof(int *));
		nombre = (char **)realloc(nombre, (i + 1) * sizeof(char *));
		printf("i vale %d\n", i);
		/* 	printf("i vale %d\n", i);
			if(block==NULL){
				printf("block es null");
			}
			printf("bloque es: %p\n",block);
			nombre[i] = (char *)malloc(sizeof(char) * (strlen(name) + 1)); */

		// printf("nombre es: %s\n",nombre[i]);

		if (array_block != NULL && nombre != NULL)
		{
			printf("estoy en el primer if\n");
			array_block[i] = (int *)malloc(size * sizeof(int));
			nombre[i] = (char *)malloc((strlen(name) + 1) * sizeof(char));

			if (array_block[i] != NULL && nombre[i] != NULL)
			{
				printf("estoy en el segundo if\n");
				identificador = (int *)realloc(identificador, (i + 1) * sizeof(int));
				cont_referencias = (int *)realloc(cont_referencias, (i + 1) * sizeof(int));
				tamanio = (int *)realloc(tamanio, (i + 1) * sizeof(int));

				strcpy(nombre[i], name);
				printf("nombre: %s\n", nombre[i]);

				*(identificador + i) = i + 1;
				printf("El bloque tiene id = %d\n", *(identificador + i));
				*(cont_referencias + i) = 0;
				printf("El contador de referencias está iniciado en %d\n", *(cont_referencias + i));
				*(tamanio + i) = size;
				printf("El tamaño es %d\n", *(tamanio + i));
				cantidad_bloques += 1;
				printf("cantidad de bloques: %d\n", cantidad_bloques);
				// Actualizo los bloques de memoria:
				*memoriarestante = (*memoriarestante) - size;
				*memoriaenuso = (*memoriaenuso) + size;
				printf("memoria en uso: %d\n", *memoriaenuso);
				printf("memoria restante: %d\n", *memoriarestante);
				printf("memoria sigue siendo %d\n", *memoriatotal);
			}
		}

		i++;
		return i;
	}
	else
	{
		printf("No se puede asignar memoria, elija un tamanio menor\n");
		return ERROR;
		
	}

}
// ------------- resize function -------------------------
int resize(int block, int sz)
{
	printf("id del bloque: %d\n", block);
	printf("size para reasignar: %d\n", sz);
	printf("memoria total es %d\n", *memoriatotal);

	if (sz < *memoriatotal)
	{
		printf("size es menor a la memoria total \n");
		int position = -1; // Inicializamos la posición como -1 para indicar que no se encontró ninguna coincidencia
		printf("identificador mide: %d\n", cantidad_bloques);
		for (int j = 0; j < cantidad_bloques; j++)
		{
			if (*(identificador + j) == block)
			{
				printf("entre al if del for\n");
				position = j;
				break; // Se encontró la coincidencia, se sale del bucle
			}
		}
			if(position == -1) {
				printf("ERROR: No existe un bloque con ese id. \n");
				return ERROR;
			} 

		printf("La posición coincidente es: %d\n", position);
		int *nuevo_tamanio = (int *)realloc((array_block[position]), sizeof(int) * sz);

		if (nuevo_tamanio == NULL)
		{
			return ERROR;
		}
		else
		{
			printf("estoy en el else\n");
			int aux_tamanio = (int)*(tamanio + position);
			printf("aux tamaño es: %d\n", aux_tamanio); // aux es 300 
			*(tamanio + position) = sz;
			// memoria en uso: 5
			// memoria restante: 995
			*memoriarestante = (*memoriarestante + aux_tamanio) - (int)*(tamanio+position);
			printf("----memoria en uso: %d\n", *memoriaenuso);
			*memoriaenuso = (*memoriaenuso - aux_tamanio) + (int)*(tamanio + position); // acá hace cualquiera 
			printf("----memoria en uso: %d\n", *memoriaenuso);
			printf("tamaño ahora es: %d\n", *(tamanio + position));
			printf("memoria restante: %d\n", *memoriarestante);
			printf("memoria sigue siendo %d\n", *memoriatotal);

			return OK;
		}
	}
}
//--------------------------- Se agrega una referencia a un bloque de memoria existente.
int add_reference(int block)
{
	printf("estoy en add reference y el id del bloque es %d\n",block);

	int position = -1; // Inicializamos la posición como -1 para indicar que no se encontró ninguna coincidencia

	for (int j = 0; j < cantidad_bloques; j++)
	{
		if (*(identificador+j) == block)
		{
			position = j;
			break; // Se encontró la coincidencia, se sale del bucle
		}
	}

	if (position != -1)
	{
		*(cont_referencias+position) += 1; // Aumentamos el valor del contador de referencias en la posición encontrada
		printf("El contador de referencias para el bloque %d es: %d\n", block, *cont_referencias+position);
		return OK;
	}
	else
	{
		printf("No se encontró el bloque con identificador %d\n", block);
		return ERROR;
	}
}

// Se elimina una referencia a un bloque de memoria.
int remove_reference(int block)
{
	int position = -1; // Inicializamos la posición como -1 para indicar que no se encontró ninguna coincidencia

	for (int j = 0; j < cantidad_bloques; j++)
	{
		if (*identificador[j] == block)
		{
			position = j;
			break; // Se encontró la coincidencia, se sale del bucle
		}
	}

	if (position != -1)
	{
		*cont_referencias[position] -= 1; // Disminuimos el valor del contador de referencias en la posición encontrada
		printf("El contador de referencias para el bloque %d es: %d\n", block, *cont_referencias[position]);

		return OK;
	}
	else
	{
		printf("No se encontró el bloque con identificador %d\n", block);
		return ERROR;
	}
}
int cur_used_memory(void)
{
	printf("memoria en uso: %d\n", *memoriaenuso);
	return *memoriaenuso;
}
// mem total = 1000;
// mem en uso = mem total - rezise || mem total - bloque nuevo
// mem restante = mem total - mem en uso
int cur_available_memory(void)
{
	printf("memoria restante: %d\n", *memoriarestante);
	return *memoriarestante;
}

int destroy_agent()
{
	int aux_memory = 0;

	for (int j = 0; j < i; j++)
	{
		if (*cont_referencias[j] == 0 || *array_block[j] == 0)
		{
			// El contador de referencias llegó a cero o el bloque es nulo, se puede liberar el bloque de memoria
			free(array_block[j]);
			free(nombre[j]);
			cantidad_bloques -= 1;
			printf("El bloque %d ha sido liberado.\n", *array_block[j]);
			aux_memory += *tamanio[j];
			free(tamanio[j]);
		}
		printf("El total de memoria liberada es: %d\n", aux_memory);
		*memoriarestante += aux_memory;
		printf("Entonces la memoria restante es %d\n", *memoriarestante);
	}
	if (cantidad_bloques == 0)
	{
		free(*array_block);
		free(*identificador);
		free(*cont_referencias);
	}
	if ((*memoriarestante == *memoriatotal) && (cantidad_bloques == 0))
	{
		free(nombre);
		free(memoriaenuso);
		free(memoriarestante);
		free(memoriatotal);
	}

	return OK;
}