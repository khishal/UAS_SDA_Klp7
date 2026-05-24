#include "expense.h"

static void baca_baris(char *buf, int max) {
    if (!fgets(buf, max, stdin)) buf[0] = '\0';
    buf[strcspn(buf, "\n")] = '\0';
    if ((int)strlen(buf) == max - 1) bersihkan_buffer();
}

static Kategori konfirmasi_kategori(Kategori terdeteksi) {
    printf("  Kategori terdeteksi : [%s]\n", nama_kategori(terdeteksi));
    printf("  Gunakan kategori ini? [y/n] > ");
    char buf[4];
    baca_baris(buf, sizeof(buf));

    if (buf[0] == 'y' || buf[0] == 'Y') return terdeteksi;

    printf("  Pilih Kategori Manual:\n");
    printf("  [1] Sandang\n");
    printf("  [2] Pangan\n");
    printf("  [3] Transportasi\n");
    printf("  [4] Pendidikan\n");
    printf("  [5] Lainnya\n");
    printf("  > ");
    char num[4];
    baca_baris(num, sizeof(num));
    switch (atoi(num)) {
        case 1: return KAT_SANDANG;
        case 2: return KAT_PANGAN;
        case 3: return KAT_TRANSPORTASI;
        case 4: return KAT_PENDIDIKAN;
        default: return KAT_LAINNYA;
    }
}

