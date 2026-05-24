#include "expense.h"

void ll_tambah(NodeLL **head, Pengeluaran p) {
    NodeLL *node = (NodeLL *)malloc(sizeof(NodeLL));
    if (!node) { fprintf(stderr, "Alokasi linked list gagal!\n"); return; }
    node->data = p;
    node->next = NULL;
    
    if (*head == NULL) {
        *head = node;
        return;
    }
    NodeLL *cur = *head;
    while (cur->next) cur = cur->next;
    cur->next = node;
}
void ll_hapus_tail(NodeLL **head) {
    if (*head == NULL) return;

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    NodeLL *cur = *head;
    while (cur->next->next) cur = cur->next;
    free(cur->next);
    cur->next = NULL;
}
