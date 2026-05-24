#include "expense.h"

static void tampilkan_banner(void) {
    printf("\n");
    cetak_garis(60);
    printf("   SISTEM ANALISIS PENGELUARAN MAHASISWA\n");
    printf("   Kelompok 7 — Informatika, Universitas Syiah Kuala\n");
    cetak_garis(60);
}

static void tampilkan_menu(void) {
    printf("\n  MENU UTAMA\n");
    cetak_garis(40);
    printf("  [1] Input pengeluaran baru\n");
    printf("  [2] Tampilkan semua data\n");
    printf("  [3] Analisis pengeluaran\n");
    printf("  [4] Cari pengeluaran\n");
    printf("  [5] Urutkan & filter pengeluaran\n");
    printf("  [6] Rekap per kategori\n");
    printf("  [7] Undo transaksi terakhir\n");
    printf("  [8] Lihat riwayat dari file TXT\n");
    printf("  [0] Keluar\n");
    cetak_garis(40);
    printf("  Pilihan > ");
}

static void init_konteks(Konteks *ctx) {
    ctx->jumlah_data = 0;
    ctx->list_head   = NULL;
    ctx->stack_top   = NULL;
    ht_init(&ctx->ht);
    ht_isi_kamus(&ctx->ht);
    ctx->id_counter = cari_max_id_txt("riwayat_pengeluaran.txt");
}

static void bebaskan_konteks(Konteks *ctx) {
    NodeLL    *cl = ctx->list_head;
    while (cl) { NodeLL    *t = cl->next; free(cl); cl = t; }

    NodeStack *cs = ctx->stack_top;
    while (cs) { NodeStack *t = cs->next; free(cs); cs = t; }
    ht_free(&ctx->ht);
}

static void menu_sort_file(const char *filename) {
    printf("\n  Filter kategori:\n");
    printf("  [1] Semua kategori\n");
    printf("  [2] Sandang saja\n");
    printf("  [3] Pangan saja\n");
    printf("  > ");
    int c;
    scanf("%d", &c);
    bersihkan_buffer();
    switch (c) {
        case 1: sort_dan_tampilkan_file(filename, 0); break;
        case 2: sort_dan_tampilkan_file(filename, 1); break;
        case 3: sort_dan_tampilkan_file(filename, 2); break;
        default:
            printf("  [!] Pilihan tidak valid, menampilkan semua.\n");
            sort_dan_tampilkan_file(filename, 0);
    }
}
int main(void) {
    Konteks ctx;
    init_konteks(&ctx);
    tampilkan_banner();

    int pilihan;
    do {
        tampilkan_menu();
        if (scanf("%d", &pilihan) != 1) {
            bersihkan_buffer(); pilihan = -1;
        } else {
            bersihkan_buffer();
        }
        switch (pilihan) {
            case 1: input_pengeluaran(&ctx);                break;
            case 2:
                printf("\n  === Daftar Semua Pengeluaran ===\n");
                tampilkan_semua(&ctx);
                break;
            case 3: analisis_pengeluaran("riwayat_pengeluaran.txt"); break;
            case 4: cari_pengeluaran_file("riwayat_pengeluaran.txt"); break;
            case 5: menu_sort_file("riwayat_pengeluaran.txt"); break;
            case 6: rekap_per_kategori_file("riwayat_pengeluaran.txt"); break;
            case 7: undo_terakhir(&ctx);                    break;
            case 8: lihat_file_txt();                       break;
            case 0:
                printf("\n  Terima kasih! Semoga keuangan makin terkontrol.\n\n");
                break;
            default:
                printf("  [!] Pilihan tidak valid. Coba lagi.\n");
        }
    } while (pilihan != 0);
    bebaskan_konteks(&ctx);
    return 0;
}
