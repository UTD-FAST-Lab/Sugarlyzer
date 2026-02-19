#include <stdio.h>

int main() {
  #if HELLO_WORLD
  printf("Hello, World!\n");
  #else
  printf("Goodbye, World!\n");
  #endif
  return 0;
}