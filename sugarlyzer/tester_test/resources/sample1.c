#include <stdio.h>

int main() {
  #ifdef HELLO_WORLD
  printf("Hello, World!\n");
  return 0;
  #else
  printf("Goodbye, World!\n");
  return -1;
  #endif
}