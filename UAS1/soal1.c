#include <stdio.h>

int main()
{
  // Deklarasi variabel
  int num;

  // Input variabel
  printf("Masukkan sebuah angka: ");
  scanf("%d", &num);

  // Cek apakah genap atau ganjil
  if (num % 2 == 0)
  {
    // Jika genap
    printf("Angka %d adalah genap.\n", num);
  }
  else
  {
    // Jika ganjil
    printf("Angka %d adalah ganjil.\n", num);
  }

  return 0;
}