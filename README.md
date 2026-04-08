# 🌍 Posttest 2 Praktikum IoT - UNMUL 2026

Repositori ini berisi *source code* dan dokumentasi untuk pemenuhan Tugas Posttest 1 Praktikum Internet of Things (IoT). Proyek ini berfokus pada pembuatan sistem monitoring level gas, suhu, kelembapan dan kontrol aktuator (LED) melalui konektivitas Wi-Fi dan platform Telegram.

---

## 👥 Anggota Kelompok

| Nama Lengkap | NIM |
| :--- | :--- |
| [Rifqi Ramadhan] | [2309106007] |
| [Irvan Nurdiansyah] | [2309106084] |
| [Achmad Zidan Al-Baihaqi] | [2309106070] |

---

## 📖 Judul Studi Kasus
**Project IoT yang dapat dikontrol dan dimonitor dengan menggunakan platform IoT (Telegram)**

---

## 📝 Deskripsi
Proyek ini adalah prototipe sistem *Smart Home* dan pemantauan lingkungan berbasis Internet of Things (IoT) menggunakan mikrokontroler **ESP32 C3 Super Mini**. Sistem ini terintegrasi langsung dengan Telegram Bot untuk memantau kondisi ruangan dan memberikan hak akses kontrol perangkat secara spesifik kepada masing-masing anggota kelompok. 

Sistem ini dirancang dengan fitur pembatasan hak akses (*Access Control List*) dan peringatan dini (*Early Warning System*) dengan logika sebagai berikut:

- **🔐 Kontrol Akses Terbatas (Private LED):** Setiap anggota memiliki LED pribadi. Akses dikunci berdasarkan *User ID* Telegram. Rifqi hanya bisa mengontrol LED miliknya, Irpan hanya miliknya, dan begitu pula Zidan.
- **🛋️ Kontrol Publik (Main LED):** Terdapat 1 LED Utama yang disimulasikan sebagai lampu **Ruang Keluarga**. Lampu ini bersifat publik dan dapat dikontrol oleh siapa saja di dalam grup.
- **🚨 Peringatan Dini Kebocoran Gas (Push Notification):** Jika sensor **MQ-2** mendeteksi kadar gas di atas ambang batas (> 800), sistem akan mengirimkan pesan peringatan bahaya secara otomatis ke grup Telegram.
- **🌡️ Pemantauan Lingkungan (*On-Demand*):** Seluruh anggota dapat mengecek suhu dan kelembapan ruangan secara *real-time* melalui sensor **DHT11**.

---

## 🤖 Daftar Command & Respons Bot

Berikut adalah daftar perintah yang dapat digunakan di dalam grup Telegram beserta simulasi respons interaktif dari Bot:

### 1. Kontrol LED Utama (Ruang Tamu) - *Akses Terbuka*
* **Command:** `/utama_on`
  * **Respons:** "Lampu Ruang Keluarga NYALA! 💡"
* **Command:** ` /utama_off`
  * **Respons:** "Lampu Ruang Keluarga MATI! 🌙"

### 2. Kontrol LED Pribadi - *Akses Terbatas*
* **Command:** `/leda_on` *(Dieksekusi oleh Anggota Rifqi)*
  * **Respons:** "Lampu Kamar Rifqi Menyala✨"
* **Command:** `/ledb_off` *(Dieksekusi oleh Anggota Rifqi)*
  * **Respons:** "⚠️ AKSES DITOLAK! Rifqi Ramadhan dilarang menyentuh Lampu Irpan!"
* **Command:** `/leda_off` *(Dieksekusi oleh Anggota A)*
  * **Respons:** "Lampu Kamar Rifqi Mati✨"

### 3. Cek Lingkungan Ruangan - *Akses Terbuka*
* **Command:** `/suhu`
  * **Respons:**
    ```text
    🌡️ Suhu: 23.70°C
    💧 Lembap: 19.00%
    ```

### 4. Peringatan Dini Otomatis (Push Notification)
* **Trigger:** Sensor MQ-2 mendeteksi gas > Ambang Batas (> 800)
  * **Respons Otomatis ke Grup:**
    ```text
    🚨 **WARNING!** Terdeteksi kebocoran GAS! (Nilai: 824)
    ```

---

## ⚙️ Komponen yang Digunakan

1. 1x Board Mikrokontroler ([ESP32 C3 Super Mini])
2. 1x Sensor Gas (MQ 2)
3. 1x Sensor Suhu dan Kelembapan (DHT 11)
4. 4x LED
5. Kabel Jumper (Male-to-Male secukupnya)
6. 1x Breadboard
7. Koneksi Wi-Fi dan Platform IoT ([Telegram])

---

## 🛠️ Pembagian Tugas

| Nama Anggota | Deskripsi Tugas / Peran |
| :--- | :--- |
| **[Rifqi Ramadhan]** | Menyetting dan mempersiapkan Bot Telegram. |
| **[Irvan Nurdiansyah]** | Merakit dan Menyusun Board Schematic. |
| **[Achmad Zidan Al-Baihaqi]** | Menulis *source code* (.ino), mengatur koneksi Wi-Fi. |

---

## 🔌 Board Schematic

### Skema (Wokwi)
<img width="678" height="547" alt="image" src="https://github.com/user-attachments/assets/753a2800-e03f-4a68-9537-acf56774df5e" />

### Skema (Real)
<img width="1280" height="720" alt="image" src="https://github.com/user-attachments/assets/dc10639d-606e-4611-9c96-db219ca55079" />


| Komponen | Pin Komponen | Pin Board |
| :--- | :--- | :--- |
| Sensor DHT (Suhu dan Kelembapan) | Analog Out | 2 |
| Sensor MQ (Gas) | Analog Out | 3 |
| LED 1 (Lampu Utama) | Anoda (+) | 5 |
| LED 2 (Lampu Rifqi) | Anoda (+) | 6 |
| LED 3 (Lampu Irpan) | Anoda (+) | 7 |
| LED 4 (Lampu Zidan) | Anoda (+) | 8 |

---

## 🎥 Video Demo

Berikut adalah video demonstrasi dari proyek kami yang memperlihatkan anggota kelompok, rangkaian *hardware*, *source code*, dan hasil monitoring/kontrol pada platform IoT:

[![Video Demo](https://img.shields.io/badge/YouTube-Tonton_Video_Demo-FF0000?style=for-the-badge&logo=youtube&logoColor=white)]()
