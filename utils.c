#include "expense.h"

const char *nama_kategori(Kategori k) {
    switch (k) {
        case KAT_SANDANG:      return "Sandang";
        case KAT_PANGAN:       return "Pangan";
        case KAT_TRANSPORTASI: return "Transportasi";
        case KAT_PENDIDIKAN:   return "Pendidikan";
        case KAT_LAINNYA:      return "Lainnya";
        default:               return "Unknown";
    }
}

void cetak_garis(int n) {
    for (int i = 0; i < n; i++) putchar('-');
    putchar('\n');
}

void bersihkan_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void str_tolower(char *dst, const char *src, int max) {
    int i = 0;
    for (; src[i] && i < max - 1; i++)
        dst[i] = (char)tolower((unsigned char)src[i]);
    dst[i] = '\0';
}

int cari_max_id_txt(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;
    int max_id = 0, id = 0;
    char buf[256];
    while (fgets(buf, sizeof(buf), fp)) {
        if (sscanf(buf, "ID: %d |", &id) == 1) {
            if (id > max_id) max_id = id;
        }
    }
    fclose(fp);
    return max_id;
}

int hapus_baris_terakhir_txt(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;
    char baris[256][256];
    int count = 0;
    while (fgets(baris[count], sizeof(baris[count]), fp)) {
        count++;
    }
    fclose(fp);
    if (count == 0) return 0;
    fp = fopen(filename, "w");
    if (!fp) return 0;
    for (int i = 0; i < count-1; i++) {
        fputs(baris[i], fp);
    }
    fclose(fp);
    return 1;
}

int load_pengeluaran_dari_txt(const char *filename, Pengeluaran arr[], int max) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;
    int n = 0;
    char buf[256];
    while (fgets(buf, sizeof(buf), fp) && n < max) {
        Pengeluaran tmp;
        char katstr[32];
        int scanned = sscanf(buf, "ID: %d | Tgl: %11s | Item: %63[^|]| Kat: %31[^|]| Rp %lf",
            &tmp.id, tmp.tanggal, tmp.nama_item, katstr, &tmp.jumlah);

        char *end;
        end = tmp.nama_item + strlen(tmp.nama_item) - 1;
        while(end > tmp.nama_item && (*end==' ')) *end-- = '\0';
        end = katstr + strlen(katstr) - 1;
        while(end > katstr && (*end==' ')) *end-- = '\0';

        if (strcmp(katstr, "Sandang")==0) tmp.kategori = KAT_SANDANG;
        else if (strcmp(katstr, "Pangan")==0) tmp.kategori = KAT_PANGAN;
        else if (strcmp(katstr, "Transportasi")==0) tmp.kategori = KAT_TRANSPORTASI;
        else if (strcmp(katstr, "Pendidikan")==0) tmp.kategori = KAT_PENDIDIKAN;
        else tmp.kategori = KAT_LAINNYA;

        if (scanned >= 5) {
            arr[n++] = tmp;
        }
    }
    fclose(fp);
    return n;
}

void sort_ascending_by_jumlah(Pengeluaran arr[], int n) {
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (arr[j].jumlah > arr[j+1].jumlah) {
                Pengeluaran tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

