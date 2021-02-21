#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
   pid_t pid[5];

   for (int i = 0; i < 5; i++)
   {
       pid[i] = fork();
       printf("pid: %d\n", pid[i]);

       if (pid[i] < 0)
       {
           fprintf(stderr, "Fork has failed. Exiting now");
           return 1; // exit error
       }
       else if (pid[i] == 0)
       {
           sleep(1); // sleep for x seconds
           return 0;
       }
   }

   // Creating Zombie
   // ps aux | grep "(procreation_zombie)"
   sleep(10);
   return 0;
}