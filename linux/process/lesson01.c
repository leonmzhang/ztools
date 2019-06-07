#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv)
{
  /**
   * pid_t int  
   *
   */
  pid_t my_pid = getpid();
  pid_t my_ppid = getppid();

  printf("pid: %d\n", my_pid);
  printf("ppid: %d\n", my_ppid);

  return 0;
}
