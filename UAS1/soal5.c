#include <stdio.h>
#include <string.h>

int main() {
    // Deklarasi variabel
    char str[100];

    // Membaca input string
    printf("Masukkan sebuah string: ");
    fgets(str, sizeof(str), stdin);

    // Menampilkan panjang string
    printf("Panjang string: %lu\n", strlen(str));
    return 0;
}