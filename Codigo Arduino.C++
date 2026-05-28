#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN A1
#define SOLO_PIN A0

#define LED_VERMELHO A2
#define LED_AMARELO  A3
#define LED_VERDE    6

#define DHTTYPE DHT22

#define TRIG_PIN 4
#define ECHO_PIN 5

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 20, 4);

int somaSolo = 0;
int mediaSolo = 0;

float temperatura = 0;
float umidadeAr = 0;
float distancia = 0;
float maturidade = 0;
float riscoChuva = 0;
float umidadeSolo = 0;
float condicaoRota = 0;
float prioridade = 0;

String prioridadeTexto = "";
String classificacao = "";
String rota = "ROTA OK";
String statusRota = "ROTA OK";  

void setup() {

  Serial.begin(9600);

  dht.begin();

  lcd.init();
  lcd.backlight();

  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  lcd.setCursor(0,0);
  lcd.print("AGRO SPACE");

  delay(2000);
}

void loop() {

  umidadeAr = dht.readHumidity();
  temperatura = dht.readTemperature();

  somaSolo = 0;

  for(int i = 0; i < 10; i++) {
    somaSolo += analogRead(SOLO_PIN);
    delay(100);
  }

  mediaSolo = somaSolo / 10;
  umidadeSolo = map(mediaSolo, 1023, 0, 0, 100);

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duracao = pulseIn(ECHO_PIN, HIGH);

  distancia = duracao * 0.034 / 2;
  maturidade = temperatura * 2;

  if (maturidade > 100) {
    maturidade = 100;
  }

  riscoChuva = umidadeAr;

  if (distancia < 20) {
    condicaoRota = 20;
  }
  else if (distancia < 50) {
    condicaoRota = 50;
  }
  else {
    condicaoRota = 90;
  }

  prioridade = maturidade * 0.4;
  prioridade = prioridade + riscoChuva * 0.3;
  prioridade = prioridade + distancia * 0.2;
  prioridade = prioridade - condicaoRota * 0.1;

  if (prioridade >= 70) {
    prioridadeTexto = "ALTA";
  }
  else if (prioridade >= 40) {
    prioridadeTexto = "MEDIA";
  }
  else {
    prioridadeTexto = "BAIXA";
  }

  if (mediaSolo >= 700) {
    classificacao = "CRITICA";
  }
  else if (mediaSolo >= 400) {
    classificacao = "ATENCAO";
  }
  else {
    classificacao = "SEGURA";
  }

  if (prioridadeTexto == "ALTA") {
    statusRota = "ROTA OK";   
  }
  else if (prioridadeTexto == "MEDIA") {
    statusRota = "ROTA OK";
  }
  else {
    statusRota = "ROTA OK";
  }

  if (classificacao == "CRITICA") {
    digitalWrite(LED_VERMELHO, HIGH);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, LOW);
  }
  else if (classificacao == "ATENCAO") {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERDE, LOW);
  }
  else {
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }

  Serial.println();
  Serial.println("==============================================================");
  Serial.println("                    AGRO SPACE MONITOR");
  Serial.println("==============================================================");

  Serial.println("| PARAMETRO         | VALOR        | CONDICAO               |");
  Serial.println("--------------------------------------------------------------");

  Serial.print("| Temperatura       | ");
  Serial.print(temperatura);
  Serial.print(" C");

  if (temperatura >= 35) {
    Serial.println("       | ALTA                   |");
  }
  else if (temperatura >= 30) {
    Serial.println("       | MEDIA                  |");
  }
  else {
    Serial.println("       | BAIXA                  |");
  }

  Serial.print("| Umidade Solo     | ");
  Serial.print(umidadeSolo);
  Serial.print(" %");

  if (umidadeSolo <= 30) {
    Serial.println("       | BAIXA                  |");
  }
  else if (umidadeSolo <= 70) {
    Serial.println("       | MEDIA                  |");
  }
  else {
    Serial.println("       | ALTA                   |");
  }

  Serial.print("| Umidade Ar       | ");
  Serial.print(umidadeAr);
  Serial.print(" %");

  if (umidadeAr >= 70) {
    Serial.println("       | ALTA                   |");
  }
  else if (umidadeAr >= 40) {
    Serial.println("       | MEDIA                  |");
  }
  else {
    Serial.println("       | BAIXA                  |");
  }

  Serial.print("| Distancia        | ");
  Serial.print(distancia);
  Serial.print(" cm");

  if (distancia < 20) {
    Serial.println("      | CRITICA                |");
  }
  else if (distancia < 50) {
    Serial.println("      | ATENCAO                |");
  }
  else {
    Serial.println("      | SEGURA                 |");
  }

  Serial.println("--------------------------------------------------------------");

  Serial.print("| PRIORIDADE       | ");
  Serial.print(prioridadeTexto);

  if (prioridadeTexto == "ALTA") {
    Serial.println("         | URGENTE                |");
  }
  else if (prioridadeTexto == "MEDIA") {
    Serial.println("        | MODERADA               |");
  }
  else {
    Serial.println("        | ESTAVEL                |");
  }

  Serial.println("==============================================================");

  Serial.print("STATUS DA ROTA: ");
  Serial.println(statusRota);

  Serial.println("==============================================================");

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print((int)temperatura);
  lcd.print("C");

  lcd.setCursor(10,0);
  lcd.print("Solo:");
  lcd.print((int)umidadeSolo);

  lcd.setCursor(0,1);
  lcd.print("Dist:");
  lcd.print((int)distancia);
  lcd.print("cm");

  lcd.setCursor(0,2);
  lcd.print("Prior:");
  lcd.print(prioridadeTexto);

  lcd.setCursor(0,3);
  lcd.print("Rota:");
  lcd.print(statusRota);

  delay(5000);
}