#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <DHT.h>

// --- KONFIGURASI ---
const char* ssid = "Universitas Mulawarman";
const char* password = "";
const char* botToken = "8649319519:AAFO04ys0xxxlFGXiPe1ntgsIPLIjzxml5g";

// Masukkan ID Telegram Anggota
String id_1 = "6129443081"; // Rifqi Ramadhan 
String id_2 = "922219915"; // Irpan bin Laden
String id_3 = "5009863699"; // Ahmad Zidan Al-Baihaqi
String id_grup = "-5203134497"; // ID Grup untuk Push Notification

// --- PIN ---
#define LED_UTAMA 5
#define LED_1 6
#define LED_2 7
#define LED_3 8
#define DHTPIN 2
#define MQ2PIN 3

DHT dht(DHTPIN, DHT11);
WiFiClientSecure client;
UniversalTelegramBot bot(botToken, client);

unsigned long lastTimeBotRan;
int botRequestDelay = 1000;
bool gasAlert = false;

// Variabel tambahan untuk pewaktu Serial Monitor
unsigned long lastSerialPrint = 0;
const int serialPrintInterval = 2000; // Tampilkan status sensor setiap 2 detik (2000 ms)

void handleNewMessages(int numNewMessages) {
  Serial.println("\n=== PESAN TELEGRAM BARU ===");
  Serial.println("Jumlah pesan: " + String(numNewMessages));

  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String sender_id = String(bot.messages[i].from_id);
    String text = bot.messages[i].text;
    String from_name = bot.messages[i].from_name;

    // Log pesan ke Serial Monitor
    Serial.println("Dari    : " + from_name + " (ID: " + sender_id + ")");
    Serial.println("Perintah: " + text);

    if (text == "/start") {
      String welcome = "Selamat datang di Smart House, " + from_name + "!\n";
      welcome += "/utama_on | /utama_off\n/leda_on | /leda_off\n/ledb_on | /ledb_off\n/ledc_on | /ledc_off\n/suhu";
      bot.sendMessage(chat_id, welcome, "");
      Serial.println("-> Info: Membalas menu /start");
    }

    // LED UTAMA (Semua bisa)
    else if (text == "/utama_on") {
      digitalWrite(LED_UTAMA, HIGH);
      bot.sendMessage(chat_id, "Lampu Ruang Keluarga NYALA! 💡", "");
      Serial.println("-> Status: Lampu Ruang Keluarga ON");
    }
    else if (text == "/utama_off") {
      digitalWrite(LED_UTAMA, LOW);
      bot.sendMessage(chat_id, "Lampu Ruang Keluarga MATI! 🌙", "");
      Serial.println("-> Status: Lampu Ruang Keluarga OFF");
    }

    // LED ANGGOTA 1
    else if (text == "/leda_on") {
      if (sender_id == id_1) {
        digitalWrite(LED_1, HIGH);
        bot.sendMessage(chat_id, "Lampu Kamar Rifqi Menyala✨", "");
        Serial.println("-> Status: Lampu Kamar 1 ON (Diakses Rifqi)");
      } else {
        bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! " + from_name + " dilarang menyentuh lampu Rifqi!", "");
        Serial.println("-> Warning: Akses ilegal ke Lampu 1 oleh " + from_name);
      }
    }
    else if (text == "/leda_off") {
      if (sender_id == id_1) {
        digitalWrite(LED_1, LOW);
        Serial.println("-> Status: Lampu Kamar 1 OFF");
        bot.sendMessage(chat_id, "Lampu Kamar Rifqi Mati✨", "");
      }else {
        bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! " + from_name + " dilarang menyentuh lampu Rifqi!", "");
        Serial.println("-> Warning: Akses ilegal ke Lampu 1 oleh " + from_name);
      }
    }

    // LED ANGGOTA 2
    else if (text == "/ledb_on") {
      if (sender_id == id_2) {
        digitalWrite(LED_2, HIGH);
        bot.sendMessage(chat_id, "Lampu Kamar Irpan Menyala✨", "");
        Serial.println("-> Status: Lampu Kamar 2 ON (Diakses Irpan)");
      } else {
        bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! " + from_name + " dilarang menyentuh Lampu Irpan!", "");
        Serial.println("-> Warning: Akses ilegal ke Lampu 2 oleh " + from_name);
      }
    }
    else if (text == "/ledb_off") {
      if (sender_id == id_2) {
        digitalWrite(LED_2, LOW);
        Serial.println("-> Status: Lampu Kamar 2 OFF");
        bot.sendMessage(chat_id, "Lampu Kamar Irpan Mati", "");
      } else {
        bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! " + from_name + " dilarang menyentuh Lampu Irpan!", "");
        Serial.println("-> Warning: Akses ilegal ke Lampu 2 oleh " + from_name);
      }
    }

    // LED ANGGOTA 3
    else if (text == "/ledc_on") {
      if (sender_id == id_3) {
        digitalWrite(LED_3, HIGH);
        bot.sendMessage(chat_id, "Lampu Kamar Zidan Menyala✨", "");
        Serial.println("-> Status: Lampu Kamar 3 ON (Diakses Zidan)");
      } else {
        bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! " + from_name + " dilarang menyentuh Lampu Zidan!", "");
        Serial.println("-> Warning: Akses ilegal ke Lampu 3 oleh " + from_name);
      }
    }
    else if (text == "/ledc_off") {
      if (sender_id == id_3) {
        digitalWrite(LED_3, LOW);
        Serial.println("-> Status: Lampu Kamar 3 OFF");
        bot.sendMessage(chat_id, "Lampu Kamar Zidan Mati✨", "");
      } else {
        bot.sendMessage(chat_id, "⚠️ AKSES DITOLAK! " + from_name + " dilarang menyentuh Lampu Zidan!", "");
        Serial.println("-> Warning: Akses ilegal ke Lampu 3 oleh " + from_name);
      }
    }

    // CEK SUHU
    else if (text == "/suhu") {
      float t = dht.readTemperature();
      float h = dht.readHumidity();
      String msg = "🌡️ Suhu: " + String(t) + "°C\n💧 Lembap: " + String(h) + "%";
      bot.sendMessage(chat_id, msg, "");
      Serial.println("-> Info: Membaca Sensor DHT11 dikirim ke Telegram");
    } 
    else {
      Serial.println("-> Warning: Perintah tidak dikenali");
    }
    Serial.println("---------------------------");
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n--- Memulai Sistem Smart House ---");
  
  pinMode(LED_UTAMA, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  
  dht.begin();
  Serial.println("-> Sensor DHT11 Diinisialisasi");

  Serial.print("-> Menghubungkan ke Wi-Fi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT); 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\n✅ Wi-Fi Berhasil Terhubung!");
  Serial.print("-> Alamat IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("✅ Sistem siap menerima perintah dari Telegram.");
}

void loop() {
  // 1. Polling Pesan Telegram
  if (millis() > lastTimeBotRan + botRequestDelay) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }

  // 2. Monitoring Pembacaan Sensor secara Berkala di Serial Monitor
  int gasVal = analogRead(MQ2PIN);
  
  if (millis() - lastSerialPrint > serialPrintInterval) {
    float t = dht.readTemperature();
    float h = dht.readHumidity();
    Serial.println("[SENSOR] Gas MQ-2: " + String(gasVal) + " | Suhu: " + String(t) + "°C | Lembap: " + String(h) + "%");
    lastSerialPrint = millis();
  }

  // 3. Logika Push Notification Gas Bocor
  if (gasVal > 800 && !gasAlert) {
    Serial.println("🚨 BAHAYA! KEBOCORAN GAS! Mengirim notifikasi ke grup...");
    bot.sendMessage(id_grup, "🚨 **WARNING!** Terdeteksi kebocoran GAS! (Nilai: " + String(gasVal) + ")", "");
    gasAlert = true;
  } else if (gasVal < 700 && gasAlert) {
    Serial.println("✅ Kondisi gas kembali normal.");
    gasAlert = false;
  }
}