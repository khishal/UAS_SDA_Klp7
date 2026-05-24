#include "expense.h"

static void swap(Pengeluaran *a, Pengeluaran *b) {
    Pengeluaran tmp = *a;
    *a = *b;
    *b = tmp;
}

static int partition(Pengeluaran arr[], int low, int high) {
    double pivot = arr[high].jumlah;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j].jumlah >= pivot) { 
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quicksort(Pengeluaran arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

void sort_dan_tampilkan(Konteks *ctx, int mode) {
    if (ctx->jumlah_data == 0) {
        printf("  (belum ada data)\n");
        return;
    }
    Pengeluaran tmp[MAX_DATA];
    int n = 0;

    for (int i = 0; i < ctx->jumlah_data; i++) {
        Pengeluaran *p = &ctx->array[i];
        int masuk = 0;
        switch (mode) {
            case 0: masuk = 1;                          break;
            case 1: masuk = (p->kategori == KAT_SANDANG); break;
            case 2: masuk = (p->kategori == KAT_PANGAN);  break;
            default: masuk = 1;
        }
        if (masuk) tmp[n++] = *p;
    }

    if (n == 0) {
        printf("  (tidak ada data untuk kategori ini)\n");
        return;
    }

    quicksort(tmp, 0, n - 1);

    /* Label judul */
    const char *label;
    switch (mode) {
        case 1:  label = "SANDANG"; break;
        case 2:  label = "PANGAN";  break;
        default: label = "SEMUA KATEGORI";
    }

    printf("\n  === Data Pengeluaran [%s] — Diurutkan Terbesar ke Terkecil ===\n\n", label);
    cetak_garis(72);
    printf("  %-4s %-20s %-12s %-14s %12s\n",
           "ID", "Nama Item", "Tanggal", "Kategori", "Jumlah (Rp)");
    cetak_garis(72);

    double total = 0;
    for (int i = 0; i < n; i++) {
        printf("  %-4d %-20s %-12s %-14s %12.0f\n",
               tmp[i].id,
               tmp[i].nama_item,
               tmp[i].tanggal,
               nama_kategori(tmp[i].kategori),
               tmp[i].jumlah);
        total += tmp[i].jumlah;
    }
    cetak_garis(72);
    printf("  Total %-50s %12.0f\n", "", total);
    printf("  Jumlah transaksi: %d\n", n);
}

void rekap_per_kategori(const Konteks *ctx) {
    double subtotal[KAT_TOTAL] = {0};
    int    cnt[KAT_TOTAL]      = {0};

    for (int i = 0; i < ctx->jumlah_data; i++) {
        Kategori k = ctx->array[i].kategori;
        subtotal[k] += ctx->array[i].jumlah;
        cnt[k]++;
    }

    printf("\n  === Rekap Pengeluaran per Kategori ===\n\n");
    cetak_garis(50);
    printf("  %-16s %8s %16s\n", "Kategori", "Transaksi", "Total (Rp)");
    cetak_garis(50);

    double grand = 0;
    for (int k = 0; k < KAT_TOTAL; k++) {
        if (cnt[k] > 0) {
            printf("  %-16s %8d %16.0f\n",
                   nama_kategori((Kategori)k), cnt[k], subtotal[k]);
            grand += subtotal[k];
        }
    }
    cetak_garis(50);
    printf("  %-16s %8d %16.0f\n", "TOTAL", ctx->jumlah_data, grand);

    printf("\n  Perbandingan Sandang vs Pangan:\n");
    printf("  Sandang : Rp %10.0f  (%d transaksi)\n", subtotal[KAT_SANDANG], cnt[KAT_SANDANG]);
    printf("  Pangan  : Rp %10.0f  (%d transaksi)\n", subtotal[KAT_PANGAN],  cnt[KAT_PANGAN]);

    if (subtotal[KAT_SANDANG] > subtotal[KAT_PANGAN])
        printf("  [!] Pengeluaran SANDANG lebih besar dari PANGAN.\n");
    else if (subtotal[KAT_PANGAN] > subtotal[KAT_SANDANG])
        printf("  [!] Pengeluaran PANGAN lebih besar dari SANDANG.\n");
    else
        printf("  [=] Pengeluaran Sandang dan Pangan seimbang.\n");
}
void sort_dan_tampilkan_file(const char *filename, int mode) {
    Pengeluaran arr[MAX_DATA];
    int jumlah_data = load_pengeluaran_dari_txt(filename, arr, MAX_DATA);
    if (jumlah_data == 0) {
        printf("  (belum ada data)\n");
        return;
    }
    Pengeluaran tmp[MAX_DATA];
    int n = 0;
    for (int i = 0; i < jumlah_data; i++) {
        int masuk = 0;
        switch (mode) {
            case 0: masuk = 1; break;
            case 1: masuk = (arr[i].kategori == KAT_SANDANG); break;
            case 2: masuk = (arr[i].kategori == KAT_PANGAN);  break;
            default: masuk = 1;
        }
        if (masuk) tmp[n++] = arr[i];
    }
    if (n == 0) {
        printf("  (tidak ada data untuk kategori ini)\n");
        return;
    }
    quicksort(tmp, 0, n - 1);

    const char *label;
    switch (mode) {
        case 1:  label = "SANDANG"; break;
        case 2:  label = "PANGAN";  break;
        default: label = "SEMUA KATEGORI";
    }

    printf("\n  === Data Pengeluaran [%s] — Diurutkan Terbesar ke Terkecil ===\n\n", label);
    cetak_garis(72);
    printf("  %-4s %-20s %-12s %-14s %12s\n",
           "ID", "Nama Item", "Tanggal", "Kategori", "Jumlah (Rp)");
    cetak_garis(72);
    double total = 0;
    for (int i = 0; i < n; i++) {
        printf("  %-4d %-20s %-12s %-14s %12.0f\n",
               tmp[i].id,
               tmp[i].nama_item,
               tmp[i].tanggal,
               nama_kategori(tmp[i].kategori),
               tmp[i].jumlah);
        total += tmp[i].jumlah;
    }
    cetak_garis(72);
    printf("  Total %-50s %12.0f\n", "", total);
    printf("  Jumlah transaksi: %d\n", n);
}
void rekap_per_kategori_file(const char *filename) {
    Pengeluaran arr[MAX_DATA];
    int jumlah_data = load_pengeluaran_dari_txt(filename, arr, MAX_DATA);

    double subtotal[KAT_TOTAL] = {0};
    int    cnt[KAT_TOTAL]      = {0};

    for (int i = 0; i < jumlah_data; i++) {
        Kategori k = arr[i].kategori;
        subtotal[k] += arr[i].jumlah;
        cnt[k]++;
    }

    printf("\n  === Rekap Pengeluaran per Kategori ===\n\n");
    cetak_garis(50);
    printf("  %-16s %8s %16s\n", "Kategori", "Transaksi", "Total (Rp)");
    cetak_garis(50);

    double grand = 0;
    for (int k = 0; k < KAT_TOTAL; k++) {
        if (cnt[k] > 0) {
            printf("  %-16s %8d %16.0f\n",
                   nama_kategori((Kategori)k), cnt[k], subtotal[k]);
            grand += subtotal[k];
        }
    }
    cetak_garis(50);
    printf("  %-16s %8d %16.0f\n", "TOTAL", jumlah_data, grand);

    printf("\n  Perbandingan Sandang vs Pangan:\n");
    printf("  Sandang : Rp %10.0f  (%d transaksi)\n", subtotal[KAT_SANDANG], cnt[KAT_SANDANG]);
    printf("  Pangan  : Rp %10.0f  (%d transaksi)\n", subtotal[KAT_PANGAN],  cnt[KAT_PANGAN]);
    if (subtotal[KAT_SANDANG] > subtotal[KAT_PANGAN])
        printf("  [!] Pengeluaran SANDANG lebih besar dari PANGAN.\n");
    else if (subtotal[KAT_PANGAN] > subtotal[KAT_SANDANG])
        printf("  [!] Pengeluaran PANGAN lebih besar dari SANDANG.\n");
    else
        printf("  [=] Pengeluaran Sandang dan Pangan seimbang.\n");
}
