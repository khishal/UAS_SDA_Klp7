#include "expense.h"

void stack_push(NodeStack **top, Pengeluaran p) {
    NodeStack *node = (NodeStack *)malloc(sizeof(NodeStack));
    if (!node) { fprintf(stderr, "Alokasi stack gagal!\n"); return; }
    node->data = p;
    node->next = *top;
    *top = node;
}

int stack_pop(NodeStack **top, Pengeluaran *out) {
    if (*top == NULL) return 0;
    NodeStack *tmp = *top;
    *out = tmp->data;
    *top = tmp->next;
    free(tmp);
    return 1;
}

void undo_terakhir(Konteks *ctx) {
    Pengeluaran p;
    if (!stack_pop(&ctx->stack_top, &p)) {
        printf("  [!] Tidak ada transaksi yang bisa di-undo.\n");
        return;
    }

    if (!hapus_baris_terakhir_txt("riwayat_pengeluaran.txt")) {
        printf("[!] Tidak bisa hapus transaksi terakhir dari file TXT!\n");
    }

    printf("  [Undo] Transaksi \"%s\" (ID %d, Rp %.0f) berhasil dibatalkan.\n",
           p.nama_item, p.id, p.jumlah);
}
