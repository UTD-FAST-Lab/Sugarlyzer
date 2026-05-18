#include <stdlib.h>

int main() {
  void* mod;
  void** hdr;

  mod = malloc(4);
  hdr = (void *) mod;

  free(mod);
}


