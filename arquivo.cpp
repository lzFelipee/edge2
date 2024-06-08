#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define Ledverde 11
#define Ledazul 10
#define Ledlara 9
#define Ledverm 8

#define disparo 2
#define eco 3

#define TRES_QUARTOS 45
#define METADE 70 
#define UM_QUARTO 95

#define colunas_lcd 16
#define linhas_lcd 2
#define endereco_lcd 0x27

LiquidCrystal_I2C lcd(endereco_lcd, colunas_lcd, linhas_lcd);

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(disparo, OUTPUT);
  pinMode(eco, INPUT);
  pinMode(Ledverde, OUTPUT);
  pinMode(Ledazul, OUTPUT);
  pinMode(Ledlara, OUTPUT);
  pinMode(Ledverm, OUTPUT);
  digitalWrite(Ledverm, HIGH);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(disparo, HIGH);
  delayMicroseconds(10); 
  digitalWrite(disparo, LOW);
  
  long duracao = pulseIn(eco, HIGH); 
  long distancia = (duracao / 2) / 29.1; 
  
  
  digitalWrite(Ledverde, LOW);
  digitalWrite(Ledazul, LOW);
  digitalWrite(Ledlara, LOW);
  
  if (distancia < TRES_QUARTOS) {
    digitalWrite(Ledverde, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reservatorio: 100%");
    lcd.setCursor(0, 1);
    lcd.print("Capacidade Total");
  }
  else if (distancia < METADE) {
    digitalWrite(Ledazul, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reservatorio: 75%");
    lcd.setCursor(0, 1);
    lcd.print("Capacidade 75%");
  }
  else if (distancia < UM_QUARTO) {
    digitalWrite(Ledlara, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reservatorio: 50%");
    lcd.setCursor(0, 1);
    lcd.print("Capacidade 50%");
  }
  else {
    digitalWrite(Ledverm, HIGH);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Reservatorio: 25%");
    lcd.setCursor(0, 1);
    lcd.print("Capacidade 25%");
  }
  
  Serial.print("Distancia (cm): ");
  Serial.println(distancia);
  
  delay(250);
}
