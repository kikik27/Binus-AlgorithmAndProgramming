Apa output program ini ?
#include <stdio.h>
                       int
                       square(int x)
{
  return x * x;
}
int main()
{
  int (*ptr)(int) = square;
  printf("%d", ptr(5));
  return 0;
}