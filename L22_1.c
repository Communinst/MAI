
#include <stdio.h>
#include <unistd.h>



int main () 
{

    printf("Task 1: \n\n");

    int pid;
    pid = fork();
    printf("%d\n", pid);

    printf("Returned value's an ID of the just created (by fork) process.\n");

    printf("Let's make it a bit clear:");
    //This block will be output twice because two processes are running simultaneously.
    //One for parent, the second is for new one.
    printf("Entry point: my pid is %d, parent pid is %d\n",
           getpid(), getppid());

    if (pid > 0) {
        printf("Parent: my pid is %d, parent pid is %d, my child pid is %d\n",
               getpid(), getppid(), pid);
    }

    else if (pid == 0) {
        printf("Child: my pid is %d, parent pid is %d\n",
               getpid(), getppid());
    }
    
    else {
        printf("Parent: oops! can not create a child (my pid is %d)\n",
               getpid());
    }

    return 0;
}