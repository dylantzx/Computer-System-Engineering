#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>


/*
A struct creation for example
*/
typedef struct Coordinate{
   int x;
   int y;
   int id;
} Vec2D;

// void *functionForThread(void* args);

