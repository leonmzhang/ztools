#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char **argv)
{
  pid_t pid = fork();
  if(pid != -1)
  {
    if (pid > 0)
      printf("I am a parent process, my pid is %d.\n", getpid());
    else if (pid == 0)
      printf("I am a child process, my pid is %d.\n", getpid());
  }
  else
    printf("Error: %d", errno);
  return 0;
}
