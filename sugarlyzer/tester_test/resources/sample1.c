#include <stdio.h>
#include <stdlib.h>

int main()
{
#ifdef HELLO_WORLD
#if SECOND_NESTING
#ifndef THIRD_NESTING
  int *leak = malloc(sizeof(int));
  printf("Hello, World!\n");
#endif
#endif
  return 0;
#else
  printf("Goodbye, World!\n");
  return -1;
#endif
}