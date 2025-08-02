#include <stdio.h>
#include <stdlib.h>

int main()
{
  FILE *input, *genap, *ganjil;
  int angka;

  input = fopen("angka.txt", "r");
  if (input == NULL)
  {
    printf("Gagal membuka file angka.txt\n");
    return 1;
  }

  genap = fopen("genap.txt", "w");
  ganjil = fopen("ganjil.txt", "w");

  if (genap == NULL || ganjil == NULL)
  {
    printf("Gagal membuka file output\n");
    fclose(input);
    return 1;
  }

  while (fscanf(input, "%d", &angka) != EOF)
  {
    if (angka % 2 == 0)
      fprintf(genap, "%d\n", angka);
    else
      fprintf(ganjil, "%d\n", angka);
  }

  fclose(input);
  fclose(genap);
  fclose(ganjil);

  printf("Pemrosesan selesai. File 'genap.txt' dan 'ganjil.txt' telah dibuat.\n");
  return 0;
}
