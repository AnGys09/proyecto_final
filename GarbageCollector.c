#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "garbage.h"
#define OK 0
#define ERROR (-1)

// estructura de la memoria:
int *memoriatotal = NULL;	 // memoria total que pide el usuario
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
int add_reference(int block);
int remove_reference(int block);
int cur_used_memory(void);
int cur_available_memory(void);
int destroy_agent();

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
	add_reference(block1); // 0 ->1
	add_reference(block2); // 0 ->1
	add_reference(block2); // Agregar dos referencias al mismo bloque 1 -> 2
	add_reference(block3); // 0->1

	// Prueba de remove_reference
	remove_reference(block2); // 2-> 1
	remove_reference(block2); // Quitar una referencia más al mismo bloque 1-> 0 ---free 300 

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

	max_mem = maxmem; 
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

	if ((size <= *memoriarestante))
	{
		array_block = (int **)realloc(array_block, (i + 1) * sizeof(int *));
		nombre = (char **)realloc(nombre, (i + 1) * sizeof(char *));

		if (array_block != NULL && nombre != NULL)
		{
			array_block[i] = (int *)malloc(size * sizeof(int));
			nombre[i] = (char *)malloc((strlen(name) + 1) * sizeof(char));

			if (array_block[i] != NULL && nombre[i] != NULL)
			{
				identificador = (int *)realloc(identificador, (i + 1) * sizeof(int));
				cont_referencias = (int *)realloc(cont_referencias, (i + 1) * sizeof(int));
				tamanio = (int *)realloc(tamanio, (i + 1) * sizeof(int));

				strcpy(nombre[i], name);

				*(identificador + i) = i + 1;
				*(cont_referencias + i) = 0;
				*(tamanio + i) = size;
				cantidad_bloques += 1;
				
				// Actualizo los bloques de memoria:
				*memoriarestante = (*memoriarestante) - size;
				*memoriaenuso = (*memoriaenuso) + size;
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
	if (sz < *memoriarestante)
	{
		int position = -1; // Inicializamos la posición como -1 para indicar que no se encontró ninguna coincidencia
		for (int j = 0; j < cantidad_bloques; j++)
		{
			if (*(identificador + j) == block)
			{
				position = j;
				break; // Se encontró la coincidencia, se sale del bucle
			}
		}
		if (position == -1)
		{
			printf("ERROR: No existe un bloque con ese id. \n");
			return ERROR;
		}

		int *nuevo_tamanio = (int *)realloc((array_block[position]), sizeof(int) * sz);

		if (nuevo_tamanio == NULL)
		{
			return ERROR;
		}
		else
		{
			int aux_tamanio = (int)*(tamanio + position);
			*(tamanio + position) = sz;
			*memoriarestante = (*memoriarestante + aux_tamanio) - (int)*(tamanio + position);
			*memoriaenuso = (*memoriaenuso - aux_tamanio) + (int)*(tamanio + position); 

			return OK;
		}
	}
}

int add_reference(int block)
{
	int position = -1; // Inicializamos la posición como -1 para indicar que no se encontró ninguna coincidencia
	
	for (int j = 0; j < cantidad_bloques; j++)
	{
		if (*(identificador + j) == block)
		{
			position = j;
			break; // Se encontró la coincidencia, se sale del bucle
		}
	}

	if (position != -1)
	{
		*(cont_referencias + position) = (int)*(cont_referencias + position) + 1; // Aumentamos el valor del contador de referencias en la posición encontrada
		return OK;
	}
	else
	{
		printf("No se encontró el bloque con identificador %d\n", block);
		return ERROR;
	}
}

int remove_reference(int block)
{

	int position = -1; // Inicializamos la posición como -1 para indicar que no se encontró ninguna coincidencia

	for (int j = 0; j < cantidad_bloques; j++)
	{
		if (*(identificador + j) == block)
		{
			position = j;
			break; // Se encontró la coincidencia, se sale del bucle
		}
	}

	if (position != -1)
	{
		*(cont_referencias + position) = (int)*(cont_referencias + position) - 1; // Aumentamos el valor del contador de referencias en la posición encontrada
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
	return *memoriaenuso;
}

int cur_available_memory(void)
{
	return *memoriarestante;
}

int destroy_agent()
{
	
	for (int j = 0; j <= i; j++)
	{
		free(cont_referencias+j);
		free(nombre+j);
		cantidad_bloques -= 1;
		free(tamanio+j);
	}

	if (cantidad_bloques == 0)
	{
		free(array_block);
		free(identificador);
		free(cont_referencias);
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