#include "cclass.h"
int main(int argc, char** argv){
  
  int x = 5;
  float y = 3.0;
  char a = 'a';
  char b = 'b';
  char c = 'c';

  printf("Printing integer x: %d \n", x);
  printf("Printing float y: %f \n", y);
  printf("Printing characters abc: %c %c %c \n", a,b,c);
  printf("Printing characters as ASCII: %d %d %d \n", a,b,c);

  printf("Size of int is %d bytes, size of float is %d bytes, size of char is %d bytes\n", sizeof(int), sizeof(float), sizeof(char));
}

