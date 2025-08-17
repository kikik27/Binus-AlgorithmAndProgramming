#include <stdio.h>

void bubbleSort(int arr[], int n)
{
  int i, j, temp;
  for (i = 0; i < n - 1; i++)
  { // cukup sampai n-1
    for (j = 0; j < n - i - 1; j++)
    { // hindari out-of-bounds
      if (arr[j] < arr[j + 1])
      { // ubah jadi '<' untuk descending
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

int main()
{
  int data[] = {5, 2, 9, 1, 5, 6};
  int n = sizeof(data) / sizeof(data[0]);

  bubbleSort(data, n);

  for (int i = 0; i < n; i++)
    printf("%d ", data[i]);

  return 0;
}
