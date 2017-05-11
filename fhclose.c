/*
 * Closes any open file handles above stdin/out/err, then execs its arguments.
 * Useful as a wrapper to processes launched by e.g. php scripts.
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/resource.h>

int main(int argc, char * argv[])
{
  if (argc < 2) {
    // We were not asked to exec anything.
    exit(1);
  }
  int maxfd = 0;
  int currfd = 0;
  DIR *dir = opendir("/proc/self/fd");
  struct dirent *dp;
  while ((dp = readdir(dir)) != NULL) {
    currfd = (atoi(dp->d_name));
    if (currfd > maxfd ) {
      maxfd = currfd;
    }
  }
  closedir(dir);
  for (currfd = 3; currfd <= maxfd; currfd++) {
    close(currfd);
  }

  // Need a null-terminated array of argv[2]..argv[argc]; note argv is not null-terminated.
  // Retain command, then shift down and insert null byte.
  char* command = argv[1];
  int i;
  for (i = 1; i < argc; i++) {
    argv[i - 1] = argv[i];
  }
  char* nullbyte = 0;
  argv[argc - 1] = nullbyte;

  execvp(command, argv);
}
