#include <stdio.h>
#include <string.h>

#define MAX 100

struct Produk {
    char nama[50];
    float harga;
    int stok;
};

void inputProduk(struct Produk produk[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nProduk ke-%d\n", i + 1);
        printf("Nama Produk: ");
        scanf(" %[^\n]", produk[i].nama);
        printf("Harga Produk: ");
        scanf("%f", &produk[i].harga);
        printf("Stok Produk: ");
        scanf("%d", &produk[i].stok);
    }
}

int cariProdukHargaTertinggi(struct Produk produk[], int n) {
    int indeksMax = 0;
    for (int i = 1; i < n; i++) {
        if (produk[i].harga > produk[indeksMax].harga) {
            indeksMax = i;
        }
    }
    return indeksMax;
}

void cetakProduk(struct Produk p) {
    printf("Nama: %s\n", p.nama);
    printf("Harga: %.2f\n", p.harga);
    printf("Stok: %d\n", p.stok);
}

int main() {
    struct Produk produk[MAX];
    int n;

    printf("Masukkan jumlah produk: ");
    scanf("%d", &n);

    inputProduk(produk, n);
    int idx = cariProdukHargaTertinggi(produk, n);

    printf("\nProduk dengan harga tertinggi:\n");
    cetakProduk(produk[idx]);

    return 0;
}
