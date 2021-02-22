#include "cclass.h"

// int sum(int* array, int size){
//    int sum_value = 0;
//    for (int i = 0; i<size; i++){
//        sum_value += array[i];
//    }
//    return sum_value;
// }

int sum(int* array, int size){
    printf("Points to sum function\n");
    return 0;
}
int geometric_sum(int* array, int size){
    printf("Points to geometric_sum function\n");
    return 0;
}
int min(int* array, int size){
    printf("Points to min function\n");
    return 0;
}
int max(int* array, int size){
    printf("Points to max function\n");
    return 0;
}
int stdev(int* array, int size){
    printf("Points to stdev function\n");
    return 0;
}
int average(int* array, int size){
    printf("Points to average function\n");
    return 0;
}

void func(int (*f)(int *, int), int *array)
{
   printf("return value is : %d \n", (*f)(array, 10));
}

int main (){
    int array[10] = {1,2,3,4,5,6,7,8,9,10};

//    //call the function using pointer
//    int result = sum_function_pointer(array, 10);
//    printf("The result is %d \n", result);

    char input;
    printf("Please enter a number: ");
    scanf("%s", &input);
    // atoi converts string arg to integer
    int user_input = atoi(&input);

    printf("User input is %d \n", user_input);
    // select a function based on user input
    function_pointers[user_input](array, 10);
    func(function_pointers[0], array);
    func(function_pointers[1], array);

    return 0;
}