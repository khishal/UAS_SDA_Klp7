#ifndef EXPENSE_H
#define EXPENSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_DATA 100
#define MAX_STR 64
#define MAX_TANGGAL 12
#define HT_SIZE 64
#define MAX_KEYWORD 32

typedef enum {
    KAT_SANDANG = 0,
    KAT_PANGAN = 1,
    KAT_TRANSPORTASI = 2,
    KAT_PENDIDIKAN = 3,
    KAT_LAINNYA = 4,
    KAT_TOTAL = 5
} Kategori;

typedef struct {
    int id;
    char nama_item[MAX_STR];
    char tanggal[MAX_TANGGAL];
    Kategori kategori;
    double jumlah;
} Pengeluaran;

typedef struct NodeLL {
    Pengeluaran  data;
    struct NodeLL *next;
} NodeLL;

typedef struct NodeStack {
    Pengeluaran data;
    struct NodeStack *next;
} NodeStack;

typedef struct NodeKW {
    char keyword[MAX_KEYWORD];
    Kategori kategori;
    struct NodeKW *next;
} NodeKW;

typedef struct {
    NodeKW *bucket[HT_SIZE];
} HashTable;

typedef struct {
    Pengeluaran array[MAX_DATA];
    int jumlah_data;
    int id_counter;
    NodeLL *list_head;
    NodeStack *stack_top;
    HashTable ht;
} Konteks;

//Hash Table 
void ht_init(HashTable *ht);
void ht_insert(HashTable *ht, const char *keyword, Kategori kat);
Kategori ht_lookup(const HashTable *ht, const char *keyword);
void ht_free(HashTable *ht);
void ht_isi_kamus(HashTable *ht);

//String Matching
Kategori deteksi_kategori(const HashTable *ht, const char *nama_item);

//Input/Output
void input_pengeluaran(Konteks *ctx);
void tampilkan_semua(const Konteks *ctx);
void lihat_file_txt(void);

//Sorting/Recap 
void quicksort(Pengeluaran arr[], int low, int high);
void sort_dan_tampilkan_file(const char *filename, int mode);
void rekap_per_kategori_file(const char *filename);

//Search
int binary_search(const Pengeluaran arr[], int n, double target);
void cari_pengeluaran_file(const char *filename);

// Analisis
void analisis_pengeluaran(const char *filename);

// Stack
void stack_push(NodeStack **top, Pengeluaran p);
int stack_pop (NodeStack **top, Pengeluaran *out);
void undo_terakhir(Konteks *ctx);

// Linked List
void ll_tambah(NodeLL **head, Pengeluaran p);
void ll_hapus_tail(NodeLL **head);

// Utils
const char *nama_kategori(Kategori k);
void cetak_garis(int n);
void bersihkan_buffer(void);
void str_tolower(char *dst, const char *src, int max);
int cari_max_id_txt(const char *filename);
int hapus_baris_terakhir_txt(const char *filename);
int load_pengeluaran_dari_txt(const char *filename, Pengeluaran arr[], int max);
void sort_ascending_by_jumlah(Pengeluaran arr[], int n);
#endif
