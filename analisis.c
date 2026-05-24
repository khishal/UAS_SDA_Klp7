#include "expense.h"

void analisis_pengeluaran(const char *filename) {
    Pengeluaran arr[MAX_DATA];
    int jumlah_data = load_pengeluaran_dari_txt(filename, arr, MAX_DATA);

    if (jumlah_data == 0) {
        printf("  (belum ada data untuk dianalisis)\n");
        return;
    }

    double total = 0, maks = arr[0].jumlah, min = arr[0].jumlah;
    int idx_maks = 0, idx_min = 0;
    for (int i = 0; i < jumlah_data; i++) {
        double j = arr[i].jumlah;
        total += j;
        if (j > maks) { maks = j; idx_maks = i; }
        if (j < min)  { min  = j; idx_min  = i; }
    }
    double rata = total / jumlah_data;

    printf("\n  === Hasil Analisis Pengeluaran ===\n\n");
    cetak_garis(50);
    printf("  Total Pengeluaran  : Rp %12.0f\n", total);
    printf("  Rata-rata          : Rp %12.0f\n", rata);
    printf("  Pengeluaran Maks   : Rp %12.0f  (%s)\n",
           maks, arr[idx_maks].nama_item);
    printf("  Pengeluaran Min    : Rp %12.0f  (%s)\n",
           min,  arr[idx_min].nama_item);
    printf("  Jumlah Transaksi   : %d\n", jumlah_data);
    cetak_garis(50);

    printf("\n  Urutan pengeluaran kecil ke besar (berdasarkan file TXT):\n");
    cetak_garis(50);
    sort_ascending_by_jumlah(arr, jumlah_data);
    for (int i = 0; i < jumlah_data; i++) {
        printf("  [ID:%d] %-20s Rp %10.0f  (%s)\n",
            arr[i].id,
            arr[i].nama_item,
            arr[i].jumlah,
            nama_kategori(arr[i].kategori));
    }
    cetak_garis(50);
