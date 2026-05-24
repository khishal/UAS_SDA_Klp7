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

