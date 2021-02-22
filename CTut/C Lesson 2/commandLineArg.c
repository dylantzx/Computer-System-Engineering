#include <stdio.h>

int main (int argc, char** argv){

   if (argc < 2){
       printf("Please supply arguments!\n");
   }

   for (int i = 0; i<argc; i++){
       printf("Argument %d is: %s \n", i, argv[i]);
   }
}