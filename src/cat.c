#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char buf[512];

void cat(int fd) {
  size_t n;

  while ((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(1, buf, n) != n) {
      fprintf((FILE *) 2, "cat: write error\n");
      exit(1);
    }
  }
  if (n < 0) {
    fprintf((FILE *) 2, "cat: read error\n");
    exit(1);
  }
}

int main(int argc, char *argv[]) {
  int fd, i;

  if (argc < 1) {
    cat(0);
    exit(0);
  }

  for (i = 0; i < argc; i++) {
    if ((fd = open(argv[i], 0)) < 0) {
      fprintf((FILE *) 2, "cat: cannot read %s\n", argv[i]);
      exit(1);
    }
    cat(fd);
    close(fd);
  }
  exit(0);
}
