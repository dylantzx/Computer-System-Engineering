#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


// return_type (*function_name)(argument types)

// int sum(int* array, int size); //declaration of a function
// int (*sum_function_pointer)(int*, int) = &sum; 

// Other examples of creating function pointers:
// float multiply(float a, float b);
// float (*multiply_function_pointer)(float,float) = &multiply;
// int* test_function();
// int* (*test_function_pointer)() = &test_function;

// declaration of function
// int sum(int* array, int size);
// int geometric_sum(int* array, int size);
// int min(int* array, int size);
// int max(int* array, int size);
// int stdev(int* array, int size);
// int average(int* array, int size);

// legal declaration and initialization of pointer to function
// int (*function_pointers[])(int*, int) = {
//    &sum, //index 0
//    &geometric_sum, //index 1
//    &min, //index 2
//    &max, //index 3
//    &stdev, // index 4
//    &average //index 5
// };

// declare another function that accepts function pointer and int* array
// void func (int (*f)(int*, int), int* array);

// void pointer to declare a generic type
// void* special_function(int arg);

