#include "cclass.h"

void* special_function(int arg){
   if (arg == 0){
       char* c = malloc(sizeof(char));
       c[0] = 'a';
       return c;
   }
   else{
       int* i = malloc(sizeof(int));
       i[0] = 128;
       return i;
   }
}

int main(){
    char* c = (char *)special_function(0);
    int* i = (int *)special_function(1);
    printf("Result of special function with arg 0 : %c \n", *c);
    printf("Result of special function with arg 1 : %d \n", *i);

    free(c);
    free(i);
    return 0;
}