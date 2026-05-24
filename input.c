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

void input_pengeluaran(Konteks *ctx) {
    if (ctx->jumlah_data >= MAX_DATA) {
        printf("[!] Kapasitas penuh (%d data).\n", MAX_DATA);
        return;
    }

    Pengeluaran p;
    p.id = ++(ctx->id_counter);

    printf("\n--- Input Pengeluaran Baru (ID: %d) ---\n", p.id);

    printf("Nama Item            : ");
    baca_baris(p.nama_item, MAX_STR);

    printf("Tanggal (DD-MM-YYYY) : ");
    baca_baris(p.tanggal, MAX_TANGGAL);

    double jml = -1;
    while (jml < 0) {
        printf("Jumlah (Rp)          : ");
        char buf[32];
        baca_baris(buf, sizeof(buf));
        jml = atof(buf);
        if (jml < 0) printf("[!] Jumlah tidak boleh negatif.\n");
    }
    p.jumlah = jml;

    Kategori terdeteksi = deteksi_kategori(&ctx->ht, p.nama_item);
    p.kategori = konfirmasi_kategori(terdeteksi);

    ctx->array[ctx->jumlah_data++] = p;
    ll_tambah(&ctx->list_head, p);
    stack_push(&ctx->stack_top, p);

    FILE *fp = fopen("riwayat_pengeluaran.txt", "a");
    if (fp != NULL) {
        fprintf(fp, "ID: %d | Tgl: %s | Item: %s | Kat: %s | Rp %.0f\n",
                p.id, p.tanggal, p.nama_item, nama_kategori(p.kategori), p.jumlah);
        fclose(fp);
    } else {
        printf("[!] Gagal menulis ke file TXT.\n");
    }

    printf("[+] Data disimpan  (Kategori: %s)\n", nama_kategori(p.kategori));
}
