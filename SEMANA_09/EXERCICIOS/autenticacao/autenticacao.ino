#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Creating the lcd element from the adress 0x27 with 16 columns and two rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

String passwordReg = "";
String passwordAut = "";

void registration() {
  lcd.clear();
  Serial.println("Digite uma senha de 4 dígitos:");
  while (Serial.available() == 0) {  
  } 
  passwordReg = Serial.readString();
  if ((passwordReg.length() - 1) != 4) {
    Serial.println("Senha inválida!");
    registration();
  }
  else {
    Serial.println("Cadastrado com sucesso!");
    Serial.println(" ");
    Serial.println("~~ Autenticação ~~");
    Serial.println(" ");
    authentication();
  }
}

void authentication() {
  lcd.clear();
  Serial.println("Insira a senha de 4 dígitos:");
  while (Serial.available() == 0) {  
  } 
  passwordAut = Serial.readString();
  if (passwordAut == passwordReg) {
    lcd.print("Autenticado!");
    neopixelWrite(RGB_BUILTIN,0,RGB_BRIGHTNESS,0);
    delay(1000);
    digitalWrite(RGB_BUILTIN, LOW);
    Serial.println(" ");
    Serial.println("~~ Cadastro ~~");
    Serial.println(" ");
    registration();
  }
  else {
    lcd.print("Senha errada!");
    neopixelWrite(RGB_BUILTIN,RGB_BRIGHTNESS,0,0);
    delay(1000);
    digitalWrite(RGB_BUILTIN, LOW);
    authentication();
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin(4, 5);
  pinMode(RGB_BUILTIN, OUTPUT);
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();
  // set cursor to first column, first row
  lcd.setCursor(0, 0);
}

void loop() {
  digitalWrite(RGB_BUILTIN, LOW);
  Serial.println(" ");
  Serial.println("~~ Cadastro ~~");
  Serial.println(" ");
  registration();
}
