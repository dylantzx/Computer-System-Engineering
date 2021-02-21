#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFERSIZE 1024

float square(float a);

// defining struct
typedef struct Vector_Int
{
   int x;
   int y;
   int z;
   char name[64];
} Vector;

void print_vector(Vector input);
// Pass by value method
// void clear_vector(Vector input);
Vector clear_vector(Vector input);

// Pass by reference method
void clear_vector_byreference(Vector *input);

int* test_malloc(int size_array);
void modify_array(int* array, int array_size);