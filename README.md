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
Proyek ini adalah prototipe sistem *Smart Home* dan pemantauan lingkungan berbasis Internet of Things (IoT) menggunakan mikrokontroler **[Sebutkan board, misal: ESP32 / NodeMCU ESP8266]**. Sistem ini terintegrasi langsung dengan Telegram Bot untuk memantau kondisi ruangan dan memberikan hak akses kontrol perangkat secara spesifik kepada masing-masing anggota kelompok. 

Sistem ini dirancang dengan fitur pembatasan hak akses (*Access Control List*) dan peringatan dini (*Early Warning System*) dengan logika sebagai berikut:

- **🔐 Kontrol Akses Terbatas (Private LED):** Setiap anggota kelompok memiliki 1 LED pribadi. Akses dikunci berdasarkan *User ID* Telegram. Anggota A hanya bisa mengontrol LED A, Anggota B hanya LED B, dan seterusnya.
- **🛋️ Kontrol Publik (Main LED):** Terdapat 1 LED Utama yang disimulasikan sebagai lampu **Ruang Tamu**. Lampu ini bersifat publik dan dapat dinyalakan/dimatikan oleh siapa saja di dalam grup.
- **🚨 Peringatan Dini Kebocoran Gas (Push Notification):** Jika sensor **MQ-2** mendeteksi kadar gas melebihi ambang batas aman, sistem akan mengambil alih dan bot akan mengirimkan pesan **Peringatan Darurat (Warning)** secara otomatis ke grup Telegram.
- **🌡️ Pemantauan Lingkungan (*On-Demand*):** Seluruh anggota grup memiliki akses penuh untuk mengecek suhu dan kelembapan ruangan (menggunakan sensor **[Sebutkan sensor, misal: DHT11 / DHT22]**) kapan saja melalui *command* bot.

---

## 🛠️ Komponen yang Digunakan
* **Microcontroller:** [ESP32 / NodeMCU 8266]
* **Sensor Gas:** MQ-2
* **Sensor Suhu & Kelembapan:** [DHT11 / DHT22]
* **Aktuator:** [Jumlah, misal: 4] buah LED (1 LED Utama + [Jumlah] LED Anggota)
* **Platform IoT:** Telegram Bot API

---

## 🤖 Daftar Command & Respons Bot

Berikut adalah daftar perintah yang dapat digunakan di dalam grup Telegram beserta simulasi respons interaktif dari Bot:

### 1. Kontrol LED Utama (Ruang Tamu) - *Akses Terbuka*
* **Command:** `/nyalakan_ruangtamu`
  * **Respons:** "🛋️ *KLIK!* Lampu Ruang Tamu telah dinyalakan oleh **[Nama User]**. Terang benderang!"
* **Command:** `/matikan_ruangtamu`
  * **Respons:** "🛋️ Lampu Ruang Tamu dimatikan oleh **[Nama User]**. Mode hemat energi diaktifkan! 🌙"

### 2. Kontrol LED Pribadi - *Akses Terbatas*
* **Command:** `/nyalakan_ledA` *(Dieksekusi oleh Anggota A)*
  * **Respons:** "🟢 *Akses Diterima.* Halo **[Nama Anggota A]**, LED pribadimu sekarang menyala!"
* **Command:** `/nyalakan_ledB` *(Dieksekusi oleh Anggota A)*
  * **Respons:** "⚠️ **AKSES DITOLAK!** 🛑 Wah, **[Nama Anggota A]** terciduk mencoba menyalakan LED milik **[Nama Anggota B]**! Jangan iseng ya, tanganmu diawasi sistem! 👁️"
* **Command:** `/matikan_ledA` *(Dieksekusi oleh Anggota A)*
  * **Respons:** "🔴 LED pribadi **[Nama Anggota A]** telah dimatikan. 📴"

### 3. Cek Lingkungan Ruangan - *Akses Terbuka*
* **Command:** `/cek_ruangan`
  * **Respons:** ```text
    📊 Laporan Kondisi Ruangan Saat Ini:
    🌡️ Suhu: 28°C (Cukup Sejuk 🍃)
    💧 Kelembapan: 60% (Normal)
    💨 Status Gas: 150 ppm (Aman 🟢)
        
    Sistem beroperasi dengan optimal, bos! 🤖✨
    ```

### 4. Peringatan Dini Otomatis (Push Notification)
* **Trigger:** Sensor MQ-2 mendeteksi gas > Ambang Batas (misal: > 500)
  * **Respons Otomatis ke Grup:**
    ```text
    🚨🚨 PANGGILAN DARURAT! 🚨🚨
    ⚠️ DETEKSI KEBOCORAN GAS TINGGI DI RUANGAN!
    💨 Kadar Gas: 850 ppm (BAHAYA 🔴)
        
    Harap segera buka ventilasi udara dan hindari menyalakan api! Sistem bersiaga! ⚠️
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
| **[Rifqi Ramadhan]** | Menyusun rangkaian *hardware* pada breadboard dan membuat *Board Schematic*. |
| **[Irvan Nurdiansyah]** | Menyusun laporan/dokumentasi (README) dan melakukan *testing* fungsionalitas. |
| **[Achmad Zidan Al-Baihaqi]** | Menulis *source code* (.ino), mengatur koneksi Wi-Fi, dan konfigurasi platform IoT. |

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
