#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

// HC-SR04 sensörü için pin tanımlamaları
#define TRIGGER_PIN  11 
#define ECHO_PIN     12 
#define MAX_DISTANCE 400 // Maksimum ölçüm mesafesi (cm cinsinden)

// LCD ekran için I2C adresi ve boyut tanımlamaları
LiquidCrystal_I2C lcd(0x27, 16, 2); 

// NewPing nesnesini oluştur
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

unsigned long previousMillis = 0;
const long interval = 25iü0; // 250ms'de bir ölçüm yap

void setup() {
  // LCD'yi başlat ve arka ışığını aç
  lcd.init();
  lcd.backlight();
  
  // LCD'ye başlangıç mesajı yazdır
  lcd.setCursor(0, 0);
  lcd.print("Mesafe Olcer");
  lcd.setCursor(0, 1);
  lcd.print("Yukleniyor...");

  delay(2000); // 2 saniye bekle

  // Ekranı temizle
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();

  // Her 250 milisaniyede bir ölçüm yap
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Mesafe ölçümü
    unsigned int uS = sonar.ping_median(5); // 5 defa ortalama ping al
    // Mikrosaniyeyi santimetreye çevir
    long distance_cm = sonar.convert_cm(uS); 

    // Ekrana veriyi yazdır
    lcd.setCursor(0, 0);
    lcd.print("Mesafe:        "); // Eski veriyi silmek için boşluk bırak
    lcd.setCursor(8, 0);
    
    // Eğer mesafe 0 ise (sensörden cevap gelmiyorsa)
    if (distance_cm == 0) {
      lcd.print("Hata");
    } else {
      lcd.print(distance_cm);
      lcd.print(" cm");
    }
  }
}
