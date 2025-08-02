#include <stdio.h>
#include <stdlib.h>

int main()
{
  int jumlah, i;
  float *nilai, total = 0.0, rata;

  printf("Masukkan jumlah siswa: ");
  scanf("%d", &jumlah);

  nilai = (float *)malloc(jumlah * sizeof(float));
  if (nilai == NULL)
  {
    printf("Gagal mengalokasikan memori.\n");
    return 1;
  }

  for (i = 0; i < jumlah; i++)
  {
    printf("Masukkan nilai siswa ke-%d: ", i + 1);
    scanf("%f", &nilai[i]);
    total += nilai[i];
  }

  rata = total / jumlah;
  printf("Rata-rata nilai siswa: %.2f\n", rata);

  free(nilai);
  return 0;
}
