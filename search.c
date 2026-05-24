#include "expense.h"

int binary_search(const Pengeluaran arr[], int n, double target) {
    int lo = 0, hi = n - 1;
    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid].jumlah == target)
            return mid;
        else if (arr[mid].jumlah > target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}

void cari_pengeluaran_file(const char *filename) {
    Pengeluaran arr[MAX_DATA];
    int jumlah_data = load_pengeluaran_dari_txt(filename, arr, MAX_DATA);
    if (jumlah_data == 0) {
        printf("  (belum ada data untuk dicari)\n");
        return;
    }
    Pengeluaran tmp[MAX_DATA];
    memcpy(tmp, arr, jumlah_data * sizeof(Pengeluaran));
    quicksort(tmp, 0, jumlah_data - 1);

    double target;
    printf("  Masukkan nominal yang dicari (Rp): ");
    if (scanf("%lf", &target) != 1) {
        bersihkan_buffer();
        printf("  [!] Input tidak valid.\n");
        return;
    }
    bersihkan_buffer();

    int idx = binary_search(tmp, jumlah_data, target);

    if (idx == -1) {
        printf("  Tidak ditemukan pengeluaran sebesar Rp %.0f.\n", target);
        return;
    }

    printf("\n  Hasil pencarian (nominal Rp %.0f):\n", target);
    cetak_garis(72);
    printf("  %-4s %-20s %-12s %-14s %12s\n",
           "ID", "Nama Item", "Tanggal", "Kategori", "Jumlah (Rp)");
    cetak_garis(72);
    for (int i = 0; i < jumlah_data; i++) {
        if (tmp[i].jumlah == target) {
            printf("  %-4d %-20s %-12s %-14s %12.0f\n",
                   tmp[i].id,
                   tmp[i].nama_item,
                   tmp[i].tanggal,
                   nama_kategori(tmp[i].kategori),
                   tmp[i].jumlah);
        }
    }
    cetak_garis(72);
}
