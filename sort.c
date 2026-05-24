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
            case 0:
                masuk = 1;
                break;

            case 1:
                masuk = (p->kategori == KAT_SANDANG);
                break;

            case 2:
                masuk = (p->kategori == KAT_PANGAN);
                break;

            default:
                masuk = 1;
        }

        if (masuk) {
            tmp[n++] = *p;
        }
    }

    if (n == 0) {
        printf("  (tidak ada data untuk kategori ini)\n");
        return;
    }

    quicksort(tmp, 0, n - 1);
