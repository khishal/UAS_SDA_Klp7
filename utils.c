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
