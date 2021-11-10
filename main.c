#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

static void sighandler(int signo) {
  if (signo == SIGINT) {
    int file = open("signals.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (file < 0) {
      printf("%s\n", strerror(errno));
      return;
    }

    char arr[50] = "Program quit due to SIGINT\n";
    write(file, arr, sizeof(arr));
    exit(0);
  }
  if (signo == SIGUSR1) printf("Parent process PID: %d\n", getppid());
}

int main() {
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);

  int a = 1;
  while (a > 0) {
    printf("PID: %d\n", getpid());
    sleep(1);
  }
  return 0;
}
