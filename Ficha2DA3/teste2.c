#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>

int main ()
{
 int pid1, pid2, pid3, pid4;
 pid1 = getpid (); /* obtain the current PID */
 
 pid2 = fork (); /* fork parent and child */
 wait (NULL); /* parent waits for its child */
 pid3 = fork (); 
 wait (NULL); /* parent waits for its child */
 
 pid4 = getpid ();
 printf ("%4d \t %4d \t %4d \t %4d\n", pid1, pid2, pid3, pid4);
}
