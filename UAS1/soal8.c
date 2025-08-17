#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Struktur untuk menyimpan data mahasiswa
typedef struct
{
  char nim[12];
  char nama[21];
  int nilai;
} Mahasiswa;

// Struktur untuk menyimpan database mahasiswa
typedef struct
{
  Mahasiswa *data;
  int count;
  int capacity;
} Database;

// Kumpulan fungsi untuk mengelola database mahasiswa
Database *initDatabase();
void freeDatabase(Database *db);
int loadFromFile(Database *db, const char *filename);
void saveToFile(Database *db, const char *filename);
void displayData(Database *db);
void displayHeader();
void sortByNimAsc(Database *db);
void sortByNilaiDesc(Database *db);
int addData(Database *db);
int validateNim(const char *nim);
int validateNama(const char *nama);
int validateNilai(int nilai);
void clearInputBuffer();
int resizeDatabase(Database *db);

int main()
{
  Database *db = initDatabase();
  if (!db)
  {
    printf("Error: Gagal menginisialisasi database!\n");
    return 1;
  }

  printf("===========================================\n");
  printf("    SISTEM PENGELOLAAN NILAI MAHASISWA    \n");
  printf("         UNIVERSITAS EKONOMI             \n");
  printf("===========================================\n\n");

  // Load data dari file
  if (loadFromFile(db, "file.txt") == 0)
  {
    printf("Data berhasil dimuat dari file file.txt\n");
  }
  else
  {
    printf("File file.txt tidak ditemukan atau kosong. Memulai dengan database kosong.\n");
  }

  printf("\nData Awal:\n");
  displayData(db);

  int choice;
  do
  {
    printf("\n===========================================\n");
    printf("                MENU UTAMA                \n");
    printf("===========================================\n");
    printf("1. Sorting NIM ASC\n");
    printf("2. Sorting Nilai DESC\n");
    printf("3. Tambah Data\n");
    printf("4. Keluar dan Save ke File\n");
    printf("===========================================\n");
    printf("Masukkan pilihan (1-4): ");

    if (scanf("%d", &choice) != 1)
    {
      clearInputBuffer();
      printf("Input tidak valid! Masukkan angka 1-4.\n");
      continue;
    }
    clearInputBuffer();

    switch (choice)
    {
    case 1:
      printf("\n=== SORTING NIM ASCENDING ===\n");
      sortByNimAsc(db);
      displayData(db);
      break;
    case 2:
      printf("\n=== SORTING NILAI DESCENDING ===\n");
      sortByNilaiDesc(db);
      displayData(db);
      break;
    case 3:
      printf("\n=== TAMBAH DATA MAHASISWA ===\n");
      if (addData(db))
      {
        printf("Data berhasil ditambahkan!\n");
      }
      else
      {
        printf("Gagal menambahkan data!\n");
      }
      break;
    case 4:
      printf("\n=== MENYIMPAN DATA KE FILE ===\n");
      saveToFile(db, "file.txt");
      printf("Data berhasil disimpan ke file file.txt\n");
      printf("Program selesai. Terima kasih!\n");
      break;
    default:
      printf("Pilihan tidak valid! Masukkan angka 1-4.\n");
    }
  } while (choice != 4);

  freeDatabase(db);
  return 0;
}

// Fungsi untuk menginisialisasi database
Database *initDatabase()
{
  Database *db = (Database *)malloc(sizeof(Database));
  if (!db)
    return NULL;

  db->capacity = 10;
  db->count = 0;
  db->data = (Mahasiswa *)malloc(db->capacity * sizeof(Mahasiswa));

  if (!db->data)
  {
    free(db);
    return NULL;
  }

  return db;
}

// Fungsi untuk membebaskan memori database
void freeDatabase(Database *db)
{
  if (db)
  {
    if (db->data)
    {
      free(db->data);
    }
    free(db);
  }
}

// Fungsi untuk memuat data dari file
int loadFromFile(Database *db, const char *filename)
{
  FILE *file = fopen(filename, "r");
  if (!file)
    return -1;

  char line[100];
  while (fgets(line, sizeof(line), file) && db->count < db->capacity)
  {
    char nim[12], nama[21];
    int nilai;

    if (sscanf(line, "%11s %20s %d", nim, nama, &nilai) == 3)
    {
      if (db->count >= db->capacity)
      {
        if (!resizeDatabase(db))
        {
          fclose(file);
          return -1;
        }
      }

      strcpy(db->data[db->count].nim, nim);
      strcpy(db->data[db->count].nama, nama);
      db->data[db->count].nilai = nilai;
      db->count++;
    }
  }

  fclose(file);
  return 0;
}

// Fungsi untuk menyimpan data ke file
void saveToFile(Database *db, const char *filename)
{
  FILE *file = fopen(filename, "w");
  if (!file)
  {
    printf("Error: Tidak dapat membuka file untuk ditulis!\n");
    return;
  }

  for (int i = 0; i < db->count; i++)
  {
    fprintf(file, "%s %s %d\n",
            db->data[i].nim,
            db->data[i].nama,
            db->data[i].nilai);
  }

  fclose(file);
}

// Fungsi untuk menampilkan header tabel
void displayHeader()
{
  printf("===========================================\n");
  printf("| No |    NIM     |      Nama      | Nilai |\n");
  printf("===========================================\n");
}

// Fungsi untuk menampilkan data mahasiswa
void displayData(Database *db)
{
  if (db->count == 0)
  {
    printf("Tidak ada data mahasiswa.\n");
    return;
  }

  displayHeader();
  for (int i = 0; i < db->count; i++)
  {
    printf("| %2d | %10s | %-14s |   %d   |\n",
           i + 1,
           db->data[i].nim,
           db->data[i].nama,
           db->data[i].nilai);
  }
  printf("===========================================\n");
}

// Fungsi untuk mengurutkan data mahasiswa berdasarkan NIM (ascending)
void sortByNimAsc(Database *db)
{
  for (int i = 0; i < db->count - 1; i++)
  {
    for (int j = 0; j < db->count - i - 1; j++)
    {
      if (strcmp(db->data[j].nim, db->data[j + 1].nim) > 0)
      {
        Mahasiswa temp = db->data[j];
        db->data[j] = db->data[j + 1];
        db->data[j + 1] = temp;
      }
    }
  }
}

// Fungsi untuk mengurutkan data mahasiswa berdasarkan nilai (descending)
void sortByNilaiDesc(Database *db)
{
  for (int i = 0; i < db->count - 1; i++)
  {
    for (int j = 0; j < db->count - i - 1; j++)
    {
      if (db->data[j].nilai < db->data[j + 1].nilai)
      {
        Mahasiswa temp = db->data[j];
        db->data[j] = db->data[j + 1];
        db->data[j + 1] = temp;
      }
    }
  }
}

// Fungsi untuk menambahkan data mahasiswa
int addData(Database *db)
{
  if (db->count >= db->capacity)
  {
    if (!resizeDatabase(db))
    {
      return 0;
    }
  }

  Mahasiswa newStudent;

  // Input dan validasi NIM
  do
  {
    printf("Masukkan NIM (10 digit angka): ");
    scanf("%11s", newStudent.nim);
    clearInputBuffer();

    if (!validateNim(newStudent.nim))
    {
      printf("Error: NIM harus 10 digit angka!\n");
    }
  } while (!validateNim(newStudent.nim));

  // Input dan validasi Nama
  do
  {
    printf("Masukkan Nama (3-20 karakter): ");
    fgets(newStudent.nama, sizeof(newStudent.nama), stdin);

    // Hapus newline dari fgets
    size_t len = strlen(newStudent.nama);
    if (len > 0 && newStudent.nama[len - 1] == '\n')
    {
      newStudent.nama[len - 1] = '\0';
    }

    if (!validateNama(newStudent.nama))
    {
      printf("Error: Nama harus 3-20 karakter!\n");
    }
  } while (!validateNama(newStudent.nama));

  // Input dan validasi Nilai
  do
  {
    printf("Masukkan Nilai (0-9): ");
    if (scanf("%d", &newStudent.nilai) != 1)
    {
      printf("Error: Input harus berupa angka!\n");
      clearInputBuffer();
      continue;
    }
    clearInputBuffer();

    if (!validateNilai(newStudent.nilai))
    {
      printf("Error: Nilai harus antara 0-9!\n");
    }
  } while (!validateNilai(newStudent.nilai));

  // Tambahkan data ke database
  db->data[db->count] = newStudent;
  db->count++;

  return 1;
}

// Fungsi untuk memvalidasi NIM
int validateNim(const char *nim)
{
  if (strlen(nim) != 10)
    return 0;

  for (int i = 0; i < 10; i++)
  {
    if (!isdigit(nim[i]))
      return 0;
  }

  return 1;
}

// Fungsi untuk memvalidasi Nama
int validateNama(const char *nama)
{
  size_t len = strlen(nama);
  return (len >= 3 && len <= 20);
}

// Fungsi untuk memvalidasi Nilai
int validateNilai(int nilai)
{
  return (nilai >= 0 && nilai <= 90);
}

// Fungsi untuk membersihkan buffer input
void clearInputBuffer()
{
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Fungsi untuk mengubah ukuran database
int resizeDatabase(Database *db)
{
  int newCapacity = db->capacity * 2;
  Mahasiswa *newData = (Mahasiswa *)realloc(db->data, newCapacity * sizeof(Mahasiswa));

  if (!newData)
  {
    printf("Error: Gagal mengalokasikan memori!\n");
    return 0;
  }

  db->data = newData;
  db->capacity = newCapacity;
  return 1;
}