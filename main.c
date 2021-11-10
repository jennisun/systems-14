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
    char arr[50] = "Program quit due to SIGINT\n";
    write(file, arr, sizeof(arr));
    exit(0);
  }

}

int main() {
  signal(SIGINT, sighandler);

  int a = 1;
  while (a > 0) {
    printf("PID %d\n", getpid());
    sleep(1);
  }
  return 0;
}
