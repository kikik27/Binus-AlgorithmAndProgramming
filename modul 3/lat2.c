#include <stdio.h>

void inputArray(int arr[], int n)
{
  printf("Masukkan %d angka:\n", n);
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &arr[i]);
  }
}

void insertionSort(int arr[], int n)
{
  for (int i = 1; i < n; i++)
  {
    int key = arr[i];
    int j = i - 1;

    while (j >= 0 && arr[j] > key)
    {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

int linearSearch(int arr[], int n, int target)
{
  for (int i = 0; i < n; i++)
  {
    if (arr[i] == target)
      return i;
  }
  return -1;
}

void cetakArray(int arr[], int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("%d ", arr[i]);
  }
  printf("\n");
}

int main()
{
  int arr[100], n, target;

  printf("Masukkan jumlah angka: ");
  scanf("%d", &n);

  inputArray(arr, n);

  insertionSort(arr, n);

  printf("Array setelah diurutkan:\n");
  cetakArray(arr, n);

  printf("Masukkan angka yang ingin dicari: ");
  scanf("%d", &target);

  int hasil = linearSearch(arr, n, target);
  if (hasil != -1)
    printf("Angka %d ditemukan di indeks ke-%d\n", target, hasil);
  else
    printf("Angka %d tidak ditemukan\n", target);

  return 0;
}
