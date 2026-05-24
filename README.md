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
