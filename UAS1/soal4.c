#include <stdio.h>

int main()
{
  // Deklarasi variabel
  int n, faktorial = 1;

  // Input angka
  printf("Masukkan angka: ");
  scanf("%d", &n);

  // Hitung faktorial
  for (int i = 1; i <= n; i++)
  {
    faktorial *= i;
  }

  // Tampilkan hasil
  printf("Faktorial dari %d adalah %d\n", n, faktorial);

  return 0;
}
