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
