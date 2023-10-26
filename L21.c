
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>



int main () 
{
  printf("%d\n%d\n%d\n%d\n%d\n%d\n",
         getpid(),  
         getppid(),

         getuid(),
         getgid(), 

         geteuid(),
         getegid()
           
  );
}