#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEM_SIZE 1000 // Tamaño máximo de la memoria

typedef struct {
    int id;
    int size;
    char signature[50];
    int ref_count;
} MemoryBlock;

typedef struct {
    MemoryBlock* blocks[MAX_MEM_SIZE];
    int memory_in_use;
    int blocks_count;
} GarbageCollector;

GarbageCollector gc; // Variable global para el garbage collector

void initializeGarbageCollector(int total_memory) {
    gc.memory_in_use = 0;
    gc.blocks_count = 0;

    // Inicializar bloques de memoria como nulos
    for (int i = 0; i < MAX_MEM_SIZE; i++) {
        gc.blocks[i] = NULL;
    }
}

int requestMemory(int size, const char* signature) {
    if (gc.memory_in_use + size > MAX_MEM_SIZE) {
        return -1; // Identificador inválido
    }

    MemoryBlock* block = (MemoryBlock*)malloc(sizeof(MemoryBlock));
    block->id = gc.blocks_count + 1;
    block->size = size;
    strcpy(block->signature, signature);
    block->ref_count = 1;

    gc.blocks[gc.blocks_count] = block;
    gc.blocks_count++;
    gc.memory_in_use += size;

    return block->id;
}

int expandMemory(int id, int additional_size) {
    MemoryBlock* block = gc.blocks[id - 1];
    int new_size = block->size + additional_size;

    if (gc.memory_in_use + additional_size > MAX_MEM_SIZE) {
        return -1; // Error al ampliar memoria
    }

    block = (MemoryBlock*)realloc(block, sizeof(MemoryBlock) + new_size);
    block->size = new_size;

    gc.blocks[id - 1] = block;
    gc.memory_in_use += additional_size;

    return 0; // OK
}

void addReference(int id) {
    MemoryBlock* block = gc.blocks[id - 1];
    block->ref_count++;
}

void removeReference(int id) {
    MemoryBlock* block = gc.blocks[id - 1];
    block->ref_count--;

    if (block->ref_count == 0) {
        gc.memory_in_use -= block->size;
        free(block);
        gc.blocks[id - 1] = NULL;
    }
}

void printMemoryStatus() {
    printf("Cantidad de memoria en uso: %d\n", gc.memory_in_use);
    printf("Cantidad de memoria restante: %d\n", MAX_MEM_SIZE - gc.memory_in_use);

    printf("Cantidad de bloques prestados: %d\n", gc.blocks_count);
    for (int i = 0; i < gc.blocks_count; i++) {
        MemoryBlock* block = gc.blocks[i];
        printf("Bloque %d - Tamaño: %d - Referencias: %d\n", block->id, block->size, block->ref_count);
    }
}

void printProcessMemory() {
    for (int i = 0; i < gc.blocks_count; i++) {
        MemoryBlock* block = gc.blocks[i];
        printf("Proceso con firma '%s' - Tamaño de memoria reservada: %d\n", block->signature, block->size);
    }
}

void freeAllMemory() {
    for (int i = 0; i < gc.blocks_count; i++) {
        MemoryBlock* block = gc.blocks[i];
        free(block);
        gc.blocks[i] = NULL;
    }

    gc.memory_in_use = 0;
    gc.blocks_count = 0;
}

int main() {
    initializeGarbageCollector(1000);

    // Caso de prueba
    int id1 = requestMemory(100, "Proceso A");
    int id2 = requestMemory(200, "Proceso B");
    int id3 = requestMemory(300, "Proceso C");

    printf("ID del bloque 1: %d\n", id1);
    printf("ID del bloque 2: %d\n", id2);
    printf("ID del bloque 3: %d\n", id3);

    expandMemory(id1, 50);
    expandMemory(id2, 100);

    addReference(id1);
    addReference(id1);
    addReference(id2);
    addReference(id3);

    printMemoryStatus();
    printProcessMemory();

    removeReference(id1);
    removeReference(id1);
    removeReference(id2);
    removeReference(id3);

    printMemoryStatus();

    freeAllMemory();

    return 0;
}
