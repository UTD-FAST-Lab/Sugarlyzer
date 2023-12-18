#ifdef X_A
int x = 20;
#else
int x = 10;
#endif

#ifdef B
int y = 2;
#else
int y = 1;
#endif

int main() {
  return x + y;
}
