#include "expense.h"

static unsigned int hash_djb2(const char *str) {
    unsigned long h = 5381;
    int c;
    while ((c = (unsigned char)*str++))
        h = ((h << 5) + h) + c; 
    return (unsigned int)(h % HT_SIZE);
}
void ht_init(HashTable *ht) {
    for (int i = 0; i < HT_SIZE; i++)
        ht->bucket[i] = NULL;
}

void ht_insert(HashTable *ht, const char *keyword, Kategori kat) {
    char lower[MAX_KEYWORD];
    str_tolower(lower, keyword, MAX_KEYWORD);

    unsigned int idx = hash_djb2(lower);

    NodeKW *cur = ht->bucket[idx];
    while (cur) {
        if (strcmp(cur->keyword, lower) == 0) return;
        cur = cur->next;
    }

    NodeKW *node = (NodeKW *)malloc(sizeof(NodeKW));
    if (!node) { fprintf(stderr, "[!] Alokasi HashTable gagal\n"); return; }
    strncpy(node->keyword, lower, MAX_KEYWORD - 1);
    node->keyword[MAX_KEYWORD - 1] = '\0';
    node->kategori = kat;
    node->next     = ht->bucket[idx];
    ht->bucket[idx] = node;
}

Kategori ht_lookup(const HashTable *ht, const char *keyword) {
    char lower[MAX_KEYWORD];
    str_tolower(lower, keyword, MAX_KEYWORD);

    unsigned int idx = hash_djb2(lower);
    NodeKW *cur = ht->bucket[idx];
    while (cur) {
        if (strcmp(cur->keyword, lower) == 0)
            return cur->kategori;
        cur = cur->next;
    }
    return KAT_LAINNYA;
}
