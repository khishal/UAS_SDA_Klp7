# 💸 Sistem Analisis Pengeluaran Mahasiswa

<div align="center">

![C](https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Active-brightgreen?style=for-the-badge)

**Aplikasi manajemen & analisis pengeluaran harian berbasis CLI untuk mahasiswa**

*Kelompok 7 — Informatika, Universitas Syiah Kuala*

</div>

---

## 📋 Daftar Isi

- [Tentang Proyek](#-tentang-proyek)
- [Fitur Utama](#-fitur-utama)
- [Struktur Proyek](#-struktur-proyek)
- [Algoritma & Struktur Data](#-algoritma--struktur-data)
- [Cara Build & Menjalankan](#-cara-build--menjalankan)
- [Panduan Penggunaan](#-panduan-penggunaan)
- [Format File Data](#-format-file-data)
- [Kategori Pengeluaran](#-kategori-pengeluaran)
- [Anggota Kelompok](#-anggota-kelompok)

---

## 🎯 Tentang Proyek

Sistem Analisis Pengeluaran Mahasiswa adalah aplikasi berbasis **command-line interface (CLI)** yang dirancang untuk membantu mahasiswa mencatat, mengelola, dan menganalisis pengeluaran harian mereka. Aplikasi ini dibangun menggunakan bahasa **C** dengan menerapkan berbagai algoritma dan struktur data yang dipelajari dalam mata kuliah Algoritma & Struktur Data.

Data pengeluaran disimpan secara **persisten** dalam file teks (`riwayat_pengeluaran.txt`), sehingga riwayat tetap tersedia meski program ditutup.

---

## ✨ Fitur Utama

| No | Fitur | Deskripsi |
|----|-------|-----------|
| 1 | **Input Pengeluaran** | Tambah data pengeluaran baru dengan deteksi kategori otomatis |
| 2 | **Tampilkan Semua Data** | Lihat seluruh riwayat pengeluaran dalam sesi aktif |
| 3 | **Analisis Pengeluaran** | Statistik lengkap: total, rata-rata, tertinggi, terendah + rekomendasi |
| 4 | **Cari Pengeluaran** | Binary search berdasarkan nominal pengeluaran |
| 5 | **Urutkan & Filter** | Quicksort descending dengan filter per kategori |
| 6 | **Rekap per Kategori** | Ringkasan total pengeluaran tiap kategori |
| 7 | **Undo Transaksi** | Batalkan transaksi terakhir menggunakan stack |
| 8 | **Lihat File Riwayat** | Baca langsung isi file TXT penyimpanan data |

---

## 📁 Struktur Proyek

```
expense-tracker/
│
├── expense.h           # Header utama: semua struct, enum, dan deklarasi fungsi
│
├── main.c              # Entry point, menu utama, inisialisasi konteks
├── input.c             # Input data baru, tampil semua, lihat file TXT
├── analisis.c          # Analisis statistik & rekomendasi pengeluaran
├── search.c            # Binary search berdasarkan nominal
├── sort.c              # Quicksort, filter kategori, rekap per kategori
├── stringmatch.c       # Deteksi kategori dengan KMP + HashTable
├── hashtable.c         # Hash table (DJB2) untuk kamus kata kunci
├── linkedlist.c        # Linked list untuk riwayat sesi aktif
├── stack.c             # Stack untuk fitur undo transaksi
├── utils.c             # Fungsi utilitas: I/O file, string, sorting
│
├── Makefile            # Build automation
└── riwayat_pengeluaran.txt   # File data (dibuat otomatis saat pertama input)
```

---

## 🧠 Algoritma & Struktur Data

### Struktur Data yang Digunakan

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Linked List   │    │     Stack       │    │   Hash Table    │
│                 │    │                 │    │  (DJB2, HT=64)  │
│ Riwayat sesi   │    │  Undo transaksi │    │  Kamus kategori │
│ pengeluaran    │    │  (LIFO)         │    │  kata kunci     │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

### Algoritma yang Diimplementasikan

| Algoritma | File | Kegunaan | Kompleksitas |
|-----------|------|----------|--------------|
| **KMP (Knuth-Morris-Pratt)** | `stringmatch.c` | Deteksi kategori dari nama item | O(n + m) |
| **Quicksort** | `sort.c` | Mengurutkan pengeluaran descending | O(n log n) avg |
| **Binary Search** | `search.c` | Mencari pengeluaran berdasarkan nominal | O(log n) |
| **Bubble Sort** | `utils.c` | Pengurutan ascending untuk analisis | O(n²) |
| **Hash DJB2** | `hashtable.c` | Hashing kata kunci kategori | O(1) avg |

### Alur Deteksi Kategori

```
Input nama item
      │
      ▼
  str_tolower()
      │
      ▼
 Tokenisasi per kata
      │
      ▼
 ht_lookup() ──── Cocok? ──► Return kategori
      │ Tidak
      ▼
 KMP Search (substring)
      │
      ▼
 Cocok? ──► Return kategori
      │ Tidak
      ▼
 Return KAT_LAINNYA
```

---

## 🔧 Cara Build & Menjalankan

### Prasyarat

- GCC (GNU Compiler Collection)
- GNU Make
- Terminal Linux / WSL / MinGW (Windows)

### Build

```bash
# Clone atau download project
cd expense-tracker/

# Build menggunakan Makefile
make

# Atau compile manual
gcc -Wall -Wextra -o expense main.c input.c analisis.c search.c sort.c \
    stringmatch.c hashtable.c linkedlist.c stack.c utils.c
```

### RUN

```bash
# Windows
mingw32-make

#linux
make

```

### Bersihkan Build

```bash
make clean
```

---
