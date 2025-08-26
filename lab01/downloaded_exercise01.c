#include <stdio.h>
#include <unistd.h>

int main() {
  char hostname[100];
  int ncpus;

  gethostname(hostname, 100);
  ncpus = sysconf(_SC_NPROCESSORS_ONLN);
  printf("Hello World, I am running on host %s with %d logical cpus\n", hostname, ncpus);
  return 0;
}
