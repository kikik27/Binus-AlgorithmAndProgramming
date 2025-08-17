
#include <stdio.h>
int main()
{
  // Deklarasi variabel
  int num;
  // Membaca file
  FILE *f = fopen("numbers.txt", "r");
  // Memeriksa apakah file berhasil dibuka
  if (f == NULL)
  {
    perror("Error opening file");
    return 1;
  }
  // Membaca angka dari file
  fscanf(f, "%d", &num);
  // Mengalikan angka dengan 2 dan menampilkannya
  printf("%d", num * 2);
  // Menutup file
  fclose(f);
  return 0;
}