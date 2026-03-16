#include <stdio.h>

int main() {
  #ifdef HELLO_WORLD
  #if SECOND_NESTING
  #ifndef THIRD_NESTING
  printf("Hello, World!\n");
  #endif
  #endif
  return 0;
  #else
  printf("Goodbye, World!\n");
  return -1;
  #endif
}