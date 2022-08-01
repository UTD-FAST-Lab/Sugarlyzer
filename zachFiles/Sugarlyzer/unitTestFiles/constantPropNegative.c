extern void read(void*);
int main () {
  int x; //1
  int y;
  int z;
#ifdef READ_X
  read(&x);
#else
  x = 4; //2
#endif
  read(&y);
  read(&z);
#ifdef INC
  x = x + 4; //3A
#endif
  y = y + x;
  if (y > z) { //4A 3B
    return 2;
  } else { //5A 4B
    #ifndef READ_X
    if (x > 3) { //6A 5B -- not compatible with 2
      return 1;
    }
    #else
    return 1;
    #endif
  }
  return 0;
}
