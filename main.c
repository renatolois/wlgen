#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/wlgen.h"

void show_error() {
  printf(
    "wlgen: missing or invalid operand or argument\n"
  );
}

void show_help() {
  printf(
    "Try 'wlgen -h' help\n -l Set word size\n -a Set alphabet\n -b Set buffer size in units of 1024 bytes (default: 1000)\ne.g. wlgen -a abc0123456789@ -l 3 -b 2000\n"
  );
}

int main(int argc, char** argv) {
  int opt;
  int lenght = -1;
  int bufferSize = 1000;
  char* alphabet = NULL;

  while((opt = getopt(argc, argv, "l:a:b:h")) != -1) {
    switch (opt) {
      case 'l':
        lenght = atoi(optarg);
        break;
      case 'a':
        alphabet = optarg;
        break;
      case 'b':
        bufferSize = atoi(optarg);
        break;
      case 'h':
        show_help();
        return 0;
      case '?':
        show_error();
        show_help();
        return 1;
      default:
        show_error();
        show_help();
        return 1;
    }
  }

  if(lenght == -1 || alphabet == NULL || bufferSize <= 0) {
    show_error();
    show_help();
    exit(1);
  }

  return bruteChars(lenght, alphabet, bufferSize * 1024);
}
