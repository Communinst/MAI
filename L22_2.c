
#include <stdio.h>
#include <unistd.h>



int main () 
{

    fork();
    printf("Hi\n");

    fork();
    printf("Hi\n");

    printf("Total of \"Hi's\" is 6. Why?");

    printf("The thing is the previously stated code will create 1 child, then 2 childs.\n");
    printf("The following diagram will provide clarity:\n");
    printf("        P0      \n      /   \\       \n");
    printf("     P1    P2  \n");
    printf("    /\n   P3\n");
    printf("P0 - parent, P1 - was created by the first fork(), P2, P3 were created by the second fork().\n");
    printf("So, amount of printed \"Hi's\\:\nP0 - 2;\nP1 - 2;\nP2, P3 - 1\n");


    return 0;
}