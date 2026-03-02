int main()
{
#ifdef HELLO_WORLD
#if NESTED
  return 0;
#endif
#else
  return -1;
#endif
}