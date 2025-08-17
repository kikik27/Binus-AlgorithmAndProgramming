#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100 // Maksimum jumlah data buku & history

// Struktur untuk menyimpan data buku
typedef struct
{
  char kode[10];
  char nama[100];
  char jenis[50];
  int harga;
} Buku;

// Struktur untuk menyimpan history penjualan
typedef struct
{
  char kodeBuku[10];
  char namaBuku[100];
  int jumlah;
  int totalHarga;
} History;

// Deklarasi variabel global
Buku daftarBuku[MAX];       // Array buku
History daftarHistory[MAX]; // Array history penjualan
int jumlahBuku = 0;         // Counter jumlah buku
int jumlahHistory = 0;      // Counter jumlah history

// Fungsi untuk membaca data buku dari file
void loadBuku()
{
  FILE *file = fopen("databuku.txt", "r");
  if (file == NULL)
    return; // Jika file tidak ada, lewati

  while (fscanf(file, "%s \"%[^\"]\" \"%[^\"]\" %d",
                daftarBuku[jumlahBuku].kode,
                daftarBuku[jumlahBuku].nama,
                daftarBuku[jumlahBuku].jenis,
                &daftarBuku[jumlahBuku].harga) == 4)
  {
    jumlahBuku++;
  }
  fclose(file);
}

// Fungsi untuk menyimpan data buku ke file
void simpanBuku()
{
  FILE *file = fopen("databuku.txt", "w");
  for (int i = 0; i < jumlahBuku; i++)
  {
    fprintf(file, "%s \"%s\" \"%s\" %d\n",
            daftarBuku[i].kode,
            daftarBuku[i].nama,
            daftarBuku[i].jenis,
            daftarBuku[i].harga);
  }
  fclose(file);
}

// Fungsi untuk membuat kode buku otomatis (B001, B002, dst)
void generateKodeBuku(char *kode)
{
  sprintf(kode, "B%03d", jumlahBuku + 1);
}

// Fungsi menampilkan semua buku
void viewBuku()
{
  if (jumlahBuku == 0)
  {
    printf("Tidak ada data buku.\n");
    return;
  }
  for (int i = 0; i < jumlahBuku; i++)
  {
    printf("%d. %s | %s | %s | Rp%d\n", i + 1,
           daftarBuku[i].kode,
           daftarBuku[i].nama,
           daftarBuku[i].jenis,
           daftarBuku[i].harga);
  }
}

// Fungsi menampilkan semua history penjualan
void viewHistory()
{
  if (jumlahHistory == 0)
  {
    printf("Belum ada history penjualan.\n");
    return;
  }
  for (int i = 0; i < jumlahHistory; i++)
  {
    printf("%d. %s - %s | Jumlah: %d | Total: Rp%d\n", i + 1,
           daftarHistory[i].kodeBuku,
           daftarHistory[i].namaBuku,
           daftarHistory[i].jumlah,
           daftarHistory[i].totalHarga);
  }
}

// Fungsi input data buku baru
void inputBukuBaru()
{
  Buku b;
  generateKodeBuku(b.kode); // Generate kode otomatis

  getchar(); // Bersihkan buffer
  printf("Masukkan nama buku: ");
  fgets(b.nama, sizeof(b.nama), stdin);
  b.nama[strcspn(b.nama, "\n")] = '\0';

  printf("Masukkan jenis buku: ");
  fgets(b.jenis, sizeof(b.jenis), stdin);
  b.jenis[strcspn(b.jenis, "\n")] = '\0';

  printf("Masukkan harga: ");
  scanf("%d", &b.harga);

  daftarBuku[jumlahBuku++] = b;
  printf("Buku berhasil ditambahkan dengan kode %s.\n", b.kode);
}

// Fungsi untuk melakukan transaksi penjualan
void inputTransaksi()
{
  if (jumlahBuku == 0)
  {
    printf("Tidak ada buku untuk dijual.\n");
    return;
  }
  viewBuku();
  int index, jumlah;
  printf("Masukkan index buku yang dibeli: ");
  scanf("%d", &index);

  if (index < 1 || index > jumlahBuku)
  {
    printf("Index tidak valid.\n");
    return;
  }

  printf("Masukkan jumlah beli: ");
  scanf("%d", &jumlah);

  // Simpan ke history
  History h;
  strcpy(h.kodeBuku, daftarBuku[index - 1].kode);
  strcpy(h.namaBuku, daftarBuku[index - 1].nama);
  h.jumlah = jumlah;
  h.totalHarga = jumlah * daftarBuku[index - 1].harga;
  daftarHistory[jumlahHistory++] = h;

  printf("Transaksi berhasil dicatat.\n");
}

// Fungsi hapus history
void deleteHistory()
{
  viewHistory();
  if (jumlahHistory == 0)
    return;

  int index;
  printf("Masukkan index yang ingin dihapus: ");
  scanf("%d", &index);
  if (index < 1 || index > jumlahHistory)
  {
    printf("Index tidak valid.\n");
    return;
  }

  for (int i = index - 1; i < jumlahHistory - 1; i++)
    daftarHistory[i] = daftarHistory[i + 1];
  jumlahHistory--;
  printf("Data history berhasil dihapus.\n");
}

// Fungsi hapus buku
void deleteBuku()
{
  viewBuku();
  if (jumlahBuku == 0)
    return;

  int index;
  printf("Masukkan index buku yang ingin dihapus: ");
  scanf("%d", &index);
  if (index < 1 || index > jumlahBuku)
  {
    printf("Index tidak valid.\n");
    return;
  }

  for (int i = index - 1; i < jumlahBuku - 1; i++)
    daftarBuku[i] = daftarBuku[i + 1];
  jumlahBuku--;
  printf("Data buku berhasil dihapus.\n");
}

// Main program
int main()
{
  int pilihan;
  loadBuku(); // Baca data dari file saat awal program

  do
  {
    printf("\n=== MENU TOKO BUKU ===\n");
    printf("1. Input Transaksi Penjualan\n");
    printf("2. View History Penjualan\n");
    printf("3. View Data Buku\n");
    printf("4. Delete History\n");
    printf("5. Delete Buku\n");
    printf("6. Tambah Buku Baru\n");
    printf("7. Exit\n");
    printf("Pilihan: ");
    scanf("%d", &pilihan);

    switch (pilihan)
    {
    case 1:
      inputTransaksi();
      break;
    case 2:
      viewHistory();
      break;
    case 3:
      viewBuku();
      break;
    case 4:
      deleteHistory();
      break;
    case 5:
      deleteBuku();
      break;
    case 6:
      inputBukuBaru();
      break;
    case 7:
      simpanBuku();
      printf("Data disimpan. Program selesai.\n");
      break;
    default:
      printf("Pilihan tidak valid.\n");
    }
  } while (pilihan != 7);

  return 0;
}
