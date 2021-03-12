/*
 * daemonize.c
 * This example daemonizes a process, writes a few log messages,
 * sleeps 60 seconds and terminates afterwards.
 */

// To test compile: gcc Daemonize.c -o summond
// ./summond
// see output at Console : search the log message or process name i.e: summond
// can check using ps aux | grep summond
// for better formatted:  ps -ejf | egrep 'STIME|summond'

#include "shellPrograms.h"

//TODO: change to appropriate path
char *path = "/Users/dylantan/Desktop/Term 5/50.005/ProgrammingAssignment1/PA1/logfile_test.txt";

/*This function summons a daemon process out of the current process*/
static int create_daemon()
{

    /* TASK 7 */
    // Incantation on creating a daemon with fork() twice
    
    // 1. Fork() from the parent process
    // 2. Close parent with exit(1)
    // 3. On child process (this is intermediate process), call setsid() so that the child becomes session leader to lose the controlling TTY
    // 4. Ignore SIGCHLD, SIGHUP
    // 5. Fork() again, parent (the intermediate) process terminates
    // 6. Child process (the daemon) set new file permissions using umask(0). Daemon's PPID at this point is 1 (the init)
    // 7. Change working directory to root
    // 8. Close all open file descriptors using sysconf(_SC_OPEN_MAX) and redirect fd 0,1,2 to /dev/null
    // 9. Return to main
    pid_t pid = fork();
    // error checking
    if (pid < 0)
    {
        perror("Failed to fork.\n");
        exit(1);
    }

    // parent process
    else if (pid > 0)
        exit(1); 

    // child process
    else
    { 
        setsid();
        signal(SIGCHLD, SIG_IGN);
        signal(SIGHUP, SIG_IGN);

        // second fork
        pid = fork();
        
        // error checking
        if (pid < 0)
        {
            perror("Failed to fork.\n");
            exit(1);
        }

        // parent process
        else if (pid > 0)
            exit(0);

        // child process (this will be the daemon)
        else
        {
            // set permissions
            // 0 means that newly created files or dir will have all permissions
            umask(0);
            
            // change dir of daemon to root where it is safe
            chdir("/");

            /* Close all open file descriptors */
            int x, fd0, fd1, fd2;
            for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
            {
                close(x);
            }
            
            /*
            * Attach file descriptors 0, 1, and 2 to /dev/null. */
            fd0 = open("/dev/null", O_RDWR);
            fd1 = dup(0);
            fd2 = dup(0);

        }
    }
    return 1;
}

static int daemon_work()
{

    int num = 0;
    FILE *fptr;

    //write PID of daemon in the beginning
    fptr = fopen(path, "a");
    if (fptr == NULL)
    {
        return EXIT_FAILURE;
    }

    fprintf(fptr, "%d with FD %d\n", getpid(), fileno(fptr));
    fclose(fptr);

    while (1)
    {

        //use appropriate location if you are using MacOS or Linux
        //TODO: Change to appropriate path
        fptr = fopen(path, "a");

        if (fptr == NULL)
        {
            return EXIT_FAILURE;
        }

        fprintf(fptr, "PID %d Daemon writing line %d to the file.  \n", getpid(), num);
        num++;

        fclose(fptr);

        sleep(10);

        if (num == 10)
            break;
    }

    return EXIT_SUCCESS;
}
int main(int argc, char **args)
{
    create_daemon();

    /* Open the log file */
    openlog("customdaemon", LOG_PID, LOG_DAEMON);
    syslog(LOG_NOTICE, "Daemon started.");
    closelog();

    return daemon_work();
}