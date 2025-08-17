#include <stdio.h>

int main()
{
  // Deklarasi array & pointer
  int array[5] = {100, 200, 300, 400, 500};
  int *ptr = array;

  // Tampilkan elemen array
  printf("Elemen array: ");
  for (int i = 0; i < 5; i++)
  {
    printf("%d ", *(ptr + i));
  }
  printf("\n");

  return 0;
}
