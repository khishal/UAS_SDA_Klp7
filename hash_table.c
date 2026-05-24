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

void ht_free(HashTable *ht) {
    for (int i = 0; i < HT_SIZE; i++) {
        NodeKW *cur = ht->bucket[i];
        while (cur) {
            NodeKW *tmp = cur->next;
            free(cur);
            cur = tmp;
        }
        ht->bucket[i] = NULL;
    }
}

void ht_isi_kamus(HashTable *ht) {
    const char *sandang[] = {
        "baju","kaos","kemeja","celana","rok","jaket","sweater",
        "sepatu","sandal","tas","dompet","ikat pinggang","topi","syal",
        "pakaian","bra","kaos kaki","sarung tangan","piyama","jas",
        "hoodie","shirt","dress","blouse","hijab","jilbab","kain",
        NULL
    };
    for (int i = 0; sandang[i]; i++) ht_insert(ht, sandang[i], KAT_SANDANG);

    const char *pangan[] = {
        "makan","minum","nasi","ayam","ikan","sayur","buah","roti",
        "kopi","teh","jus","susu","snack","cemilan","bakso","mie",
        "soto","gado","pizza","burger","indomie","beras","telur",
        "tempe","tahu","lauk","es","minuman","makanan","warung",
        "restoran","kantin","cafe","kafe","gorengan","kerupuk",
        NULL
    };
    for (int i = 0; pangan[i]; i++) ht_insert(ht, pangan[i], KAT_PANGAN);

    const char *trans[] = {
        "ojek","gojek","grab","taxi","bensin","bbm","bus","angkot",
        "kereta","tiket","parkir","tol","motor","mobil","bensin",
        "solar","pertamax","pertalite","transjakarta","busway",
        NULL
    };
    for (int i = 0; trans[i]; i++) ht_insert(ht, trans[i], KAT_TRANSPORTASI);

    const char *didik[] = {
        "buku","modul","fotokopi","print","alat tulis","pulpen","pensil",
        "kertas","tinta","kalkulator","tas sekolah","uang kuliah","spp",
        "praktikum","laboratorium","kursus","les","bimbel","referensi",
        "diktat","jurnal","makalah","skripsi","riset","seminar",
        NULL
    };
    for (int i = 0; didik[i]; i++) ht_insert(ht, didik[i], KAT_PENDIDIKAN);
}
