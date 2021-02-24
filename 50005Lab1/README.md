# 50.005 Lab1

## Flow of main_loop()
1. Open input file and read the task.
2. Ensure that each task has been assigned.
3. Revive terminated processes if any while there are still tasks.
4. Close the input file and proceed with termination of all alive processes.

## Explanation

### Ensuring that every task is assigned
To ensure that every task read from the input file is assigned to a worker process, I created a variable `bool task_taken` and looped on the task as long as it is not assigned. This would also mean that the file will **close once all the tasks are assigned**. 

### Revival process
I simply used a for-loop to loop across all the worker processes if there is a task that has yet to be taken and if there exists a terminated worker process, and immediately revive the worker process.

```
for (int i=0; i<number_of_processes; i++)
{
    int alive = waitpid(children_processes[i], NULL, WNOHANG);
    .
    .
    .
    else if (alive!=0)
    {
        reviveWorker(i);
    }
}
    
```

At this point, is important to note that this method will respawn all terminated worker processes that has received a kill() signal due to the task status 'i'. 

### Dealing with issues caused by revived process
One of the issues would be to ensure that the termination signals **ARE NOT** sent before the worker processes have completed their tasks. To resolve this, I looped around every process as long as the task_status is still 1.

```
while (shmPTR_jobs_buffer[i].task_status ==1);
```

Another issue would be that the order of execution is random and that the job_dispatch() function may not be able to alter the task_status before killing a task with 'i'

```
else
{
    shmPTR_jobs_buffer[i].task_status = 0;
    // printf("%d is gonna crash\n", i);
    kill(getpid(), SIGKILL);
}
```

To counter this, I did another check after the file has been closed and set the task_status to 0 so that it can proceed with the termination of processes

```
if (shmPTR_jobs_buffer[i].task_type =='i')
{
    shmPTR_jobs_buffer[i].task_status = 0;
}
```

