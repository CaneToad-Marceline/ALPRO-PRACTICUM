#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_SIZE 100

struct Mahasiswa {
    char nim[20];
    char nama[MAX_SIZE];
    int tahun_masuk;
    float ipk;
};

char* buatFileCSV() {
    char filename[MAX_SIZE + 4]; 
    FILE *file;
    
    printf("Masukkan nama file CSV: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; // Menghapus karakter newline dari input

    strcat(filename, ".csv");

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error creating file.\n");
        return NULL;
    }
    fclose(file);
    printf("File CSV '%s' created successfully.\n", filename);
    char *result = (char *)malloc(strlen(filename) + 1);
    strcpy(result, filename);
    return result;
}

FILE* bukaFileCSV(char *filename) {
    FILE *file = fopen(filename, "a+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return NULL;
    }
    printf("File CSV '%s' opened successfully.\n", filename);
    return file;
}

void tambahData(FILE *file) {
    if (file == NULL) {
        printf("Error: No file is currently open.\n");
        return;
    }

    int jumlah_data;
    printf("Masukkan jumlah data mahasiswa yang akan dimasukkan: ");
    scanf("%d", &jumlah_data);
    getchar(); // Membersihkan newline karakter dari buffer input

    for (int i = 0; i < jumlah_data; i++) {
        struct Mahasiswa mhs;
        printf("\nData ke-%d:\n", i + 1);
        printf("Masukkan NIM: ");
        fgets(mhs.nim, sizeof(mhs.nim), stdin);
        mhs.nim[strcspn(mhs.nim, "\n")] = '\0'; // Menghapus karakter newline dari input
        printf("Masukkan Nama: ");
        fgets(mhs.nama, sizeof(mhs.nama), stdin);
        mhs.nama[strcspn(mhs.nama, "\n")] = '\0'; // Menghapus karakter newline dari input
        printf("Masukkan Tahun Masuk: ");
        scanf("%d", &mhs.tahun_masuk);
        printf("Masukkan IPK (maksimum 4.00): ");
        scanf("%f", &mhs.ipk);

        while (getchar() != '\n'); // Membersihkan newline karakter dari buffer input

        fprintf(file, "%s,%s,%d,%.2f\n", mhs.nim, mhs.nama, mhs.tahun_masuk, mhs.ipk);
    }
    printf("\nData added to file successfully.\n");
}

void showData(FILE *file) {
    if (file == NULL) {
        printf("Error: No file is currently open.\n");
        return;
    }

    char line[MAX_SIZE];
    printf("Data dalam file CSV:\n");
    printf("| %-20s | %-30s | %-15s | %-4s |\n", "NIM", "Nama", "Tahun Masuk", "IPK");
    printf("|---------------------|--------------------------------|-----------------|------|\n");
    while (fgets(line, sizeof(line), file)) {
        struct Mahasiswa mhs;
        sscanf(line, "%[^,],%[^,],%d,%f", mhs.nim, mhs.nama, &mhs.tahun_masuk, &mhs.ipk);
        printf("| %-20s | %-30s | %-15d | %.2f |\n", mhs.nim, mhs.nama, mhs.tahun_masuk, mhs.ipk);
    }
}

void searchData(FILE *file) {
    if (file == NULL) {
        printf("Error: No file is currently open.\n");
        return;
    }

    char keyword[MAX_SIZE];
    printf("Masukkan keyword (NIM, Nama, Tahun Masuk, atau IPK): ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = '\0'; // Menghapus karakter newline dari input

    char line[MAX_SIZE];
    
    // Mencetak header tabel
    printf("Data dalam file CSV:\n");
    printf("| %-20s | %-30s | %-15s | %-4s |\n", "NIM", "Nama", "Tahun Masuk", "IPK");
    printf("|---------------------|--------------------------------|-----------------|------|\n");

    // Mencari dan mencetak data yang cocok dengan keyword
    while (fgets(line, sizeof(line), file)) {
        struct Mahasiswa mhs;
        sscanf(line, "%[^,],%[^,],%d,%f", mhs.nim, mhs.nama, &mhs.tahun_masuk, &mhs.ipk);

        if (strstr(mhs.nim, keyword) || strstr(mhs.nama, keyword) || strstr(line, keyword)) {
            printf("| %-20s | %-30s | %-15d | %.2f |\n", mhs.nim, mhs.nama, mhs.tahun_masuk, mhs.ipk);
        }
    }
}


void updateData(FILE *file, const char *filename) {
    if (file == NULL) {
        printf("Error: No file is currently open.\n");
        return;
    }

    char nim[MAX_SIZE];
    printf("Masukkan NIM mahasiswa yang ingin diupdate: ");
    fgets(nim, sizeof(nim), stdin);
    nim[strcspn(nim, "\n")] = '\0'; // Menghapus karakter newline dari input

    // Menyiapkan array dinamis untuk menyimpan data sementara
    struct Mahasiswa *mahasiswas = NULL;
    int numMahasiswas = 0;
    int updated = 0;

    // Membaca data dari file dan menyimpannya dalam array dinamis
    char line[MAX_SIZE];
    while (fgets(line, sizeof(line), file)) {
        struct Mahasiswa mhs;
        sscanf(line, "%[^,],%[^,],%d,%f", mhs.nim, mhs.nama, &mhs.tahun_masuk, &mhs.ipk);
        if (strcmp(mhs.nim, nim) == 0) {
            printf("Masukkan Nama baru: ");
            fgets(mhs.nama, sizeof(mhs.nama), stdin);
            mhs.nama[strcspn(mhs.nama, "\n")] = '\0'; // Menghapus karakter newline dari input
            printf("Masukkan Tahun Masuk baru: ");
            scanf("%d", &mhs.tahun_masuk);
            printf("Masukkan IPK baru (maksimum 4.00): ");
            scanf("%f", &mhs.ipk);
            while (getchar() != '\n'); // Membersihkan newline karakter dari buffer input
            mahasiswas = (struct Mahasiswa *) realloc(mahasiswas, (numMahasiswas + 1) * sizeof(struct Mahasiswa));
            if (mahasiswas == NULL) {
                printf("Memory reallocation failed.\n");
                return;
            }
            mahasiswas[numMahasiswas++] = mhs;
            updated = 1;
        } else {
            mahasiswas = (struct Mahasiswa *) realloc(mahasiswas, (numMahasiswas + 1) * sizeof(struct Mahasiswa));
            if (mahasiswas == NULL) {
                printf("Memory reallocation failed.\n");
                return;
            }
            mahasiswas[numMahasiswas++] = mhs;
        }
    }

    if (!updated) {
        printf("Data mahasiswa dengan NIM '%s' tidak ditemukan.\n", nim);
        free(mahasiswas); // Membebaskan memori yang dialokasikan untuk array dinamis
        return;
    } else {
        printf("Data updated successfully.\n");
    }

    // Tutup file CSV
    fclose(file);

    // Buka kembali file CSV dengan mode "w" untuk menulis ulang
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        free(mahasiswas); // Membebaskan memori yang dialokasikan untuk array dinamis
        return;
    }

    // Tulis semua data yang ada dalam array dinamis ke file CSV
    for (int i = 0; i < numMahasiswas; i++) {
        fprintf(file, "%s,%s,%d,%.2f\n", mahasiswas[i].nim, mahasiswas[i].nama, mahasiswas[i].tahun_masuk, mahasiswas[i].ipk);
    }

    // Tutup file CSV
    fclose(file);

    // Bebaskan memori yang dialokasikan untuk array dinamis
    free(mahasiswas);
}


void hapusData(FILE *file) {
    if (file == NULL) {
        printf("Error: No file is currently open.\n");
        return;
    }

    char nim[MAX_SIZE];
    printf("Masukkan NIM mahasiswa yang ingin dihapus: ");
    fgets(nim, sizeof(nim), stdin);
    nim[strcspn(nim, "\n")] = '\0'; // Menghapus karakter newline dari input

    // Membuat file sementara untuk menulis data yang tidak dihapus
    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        return;
    }

    char line[MAX_SIZE];
    int deleted = 0;
    while (fgets(line, sizeof(line), file)) {
        struct Mahasiswa mhs;
        sscanf(line, "%[^,],%[^,],%d,%f", mhs.nim, mhs.nama, &mhs.tahun_masuk, &mhs.ipk);
        if (strcmp(mhs.nim, nim) != 0) {
            fprintf(tempFile, "%s,%s,%d,%.2f\n", mhs.nim, mhs.nama, mhs.tahun_masuk, mhs.ipk);
        } else {
            deleted = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    // Menghapus file lama
    remove("data.csv");

    // Mengganti nama file sementara menjadi nama file asli
    if (rename("temp.csv", "data.csv") != 0) {
        printf("Error renaming file.\n");
        return;
    }

    // Membuka kembali file yang diperbarui
    file = fopen("data.csv", "r+");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    if (deleted) {
        printf("Data dengan NIM '%s' berhasil dihapus.\n", nim);
    } else {
        printf("Data dengan NIM '%s' tidak ditemukan.\n", nim);
    }
}


void displayCSVFiles() {
    DIR *dir;
    struct dirent *ent;
    int count = 0;

    if ((dir = opendir(".")) != NULL) {
        printf("CSV Files Available:\n");
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".csv") != NULL) {
                printf("%d. %s\n", ++count, ent->d_name);
            }
        }
        closedir(dir);
    } else {
        perror("Error opening directory");
    }
}

char* selectCSVFile() {
    char *filename = (char *)malloc(MAX_SIZE * sizeof(char));
    char choice[MAX_SIZE];

    displayCSVFiles();

    printf("Masukkan nama file CSV yang ingin Anda buka: ");
    fgets(choice, sizeof(choice), stdin);
    choice[strcspn(choice, "\n")] = '\0'; // Menghapus karakter newline dari input

    DIR *dir;
    struct dirent *ent;
    int count = 0;
    int found = 0;

    if ((dir = opendir(".")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".csv") != NULL) {
                if (++count == atoi(choice)) {
                    strcpy(filename, ent->d_name);
                    found = 1;
                    break;
                }
            }
        }
        closedir(dir);
    } else {
        perror("Error opening directory");
    }

    if (!found) {
        printf("File CSV dengan nomor yang dimasukkan tidak ditemukan.\n");
        free(filename);
        filename = NULL;
    }

    return filename;
}

int main() {
    int choice;
    char *selectedFile = NULL;
    FILE *file = NULL;

    do {
        printf("\nMenu:\n");
        printf("1. Buat File CSV\n");
        printf("2. Buka File CSV\n");
        printf("3. Tambah Data\n");
        printf("4. Show Data\n");
        printf("5. Update Data\n");
        printf("6. Hapus Data\n");
        printf("7. Cari Data\n");
        printf("8. Keluar\n");
        printf("Pilih: ");
        scanf("%d", &choice);
        getchar(); // Membersihkan newline karakter dari buffer input

        switch (choice) {
            case 1:
                if (selectedFile != NULL) {
                    free(selectedFile);
                }
                selectedFile = buatFileCSV();
                break;
            case 2:
                if (selectedFile != NULL) {
                    free(selectedFile);
                }
                selectedFile = selectCSVFile();
                if (file != NULL) {
                    fclose(file);
                }
                file = bukaFileCSV(selectedFile);
                break;
            case 3:
                tambahData(file);
                break;
            case 4:
                showData(file);
                break;
            case 5:
    			updateData(file, selectedFile);
   			    break;
            case 6:
                hapusData(file);
                break;
            case 7:
                searchData(file);
                break;
            case 8:
                printf("Terima kasih, program selesai.\n");
                if (selectedFile != NULL) {
                    free(selectedFile);
                }
                if (file != NULL) {
                    fclose(file);
                }
                break;
            default:
                printf("Pilihan tidak ditemukan.\n");
                break;
        }
    } while (choice != 8);

    return 0;
}
	
