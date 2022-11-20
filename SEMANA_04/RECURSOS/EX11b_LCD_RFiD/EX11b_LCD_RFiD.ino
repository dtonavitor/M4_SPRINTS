#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <MFRC522.h>
#include <SPI.h>

#define I2C_SDA 47 // antes  13
#define I2C_SCL 48 // antes  14
#define RFID_SS_SDA   21
#define RFID_RST      14

MFRC522 rfidBase = MFRC522(RFID_SS_SDA, RFID_RST);
class LeitorRFID{
  private:
    char codigoRFIDLido[100] = "";
    char codigoRFIDEsperado[100] = "";
    MFRC522 *rfid = NULL;
    int cartaoDetectado = 0;
    int cartaoJaLido = 0;
    void processaCodigoLido(){
      char codigo[3*rfid->uid.size+1];
      codigo[0] = 0;
      char temp[10];  
      for(int i=0; i < rfid->uid.size; i++){
        sprintf(temp,"%X",rfid->uid.uidByte[i]);
        strcat(codigo,temp);
      }
      codigo[3*rfid->uid.size+1] = 0;    
      strcpy(codigoRFIDLido,codigo);
      Serial.println(codigoRFIDLido);
    }
  public:
    LeitorRFID(MFRC522 *leitor){
      rfid = leitor;
      rfid->PCD_Init(); 
      Serial.printf("MOSI: %i MISO: %i SCK: %i SS: %i\n",MOSI,MISO,SCK,SS);
    };
    char *tipoCartao(){
      MFRC522::PICC_Type piccType = rfid->PICC_GetType(rfid->uid.sak);
      Serial.println(rfid->PICC_GetTypeName(piccType));
      return((char *)rfid->PICC_GetTypeName(piccType));
    };
    int cartaoPresente(){
      return(cartaoDetectado);
    };
    int cartaoFoiLido(){
      return(cartaoJaLido);
    };
    void leCartao(){
      if (rfid->PICC_IsNewCardPresent()) { // new tag is available
        Serial.println("Cartao presente");
        cartaoDetectado = 1;
        if (rfid->PICC_ReadCardSerial()) { // NUID has been readed      
          Serial.println("Cartao lido");  
          cartaoJaLido = 1;
          processaCodigoLido();
          rfid->PICC_HaltA(); // halt PICC
          rfid->PCD_StopCrypto1(); // stop encryption on PCD
        }
      }else{
        cartaoDetectado = 0;
      }
    };
    char *cartaoLido(){
      return(codigoRFIDLido);
    };
    void resetarLeitura(){
      cartaoDetectado = 0;
      cartaoJaLido = 0;
    }
    void listI2CPorts(){
      Serial.println("\nI2C Scanner");
      byte error, address;
      int nDevices;
      Serial.println("Scanning...");
      nDevices = 0;
      for(address = 1; address < 127; address++ ) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0) {
          Serial.print("I2C device found at address 0x");
          if (address<16) {
            Serial.print("0");
          }
          Serial.println(address,HEX);
          nDevices++;
        }
        else if (error==4) {
          Serial.print("Unknow error at address 0x");
          if (address<16) {
            Serial.print("0");
          }
          Serial.println(address,HEX);
        }    
      }
      if (nDevices == 0) {
        Serial.println("No I2C devices found\n");
      }
      else {
        Serial.println("done\n");
      }
    };
};
LeitorRFID *leitor = NULL;
//////////////////////////////

LiquidCrystal_I2C  lcd_i2cBase(0x27, 16, 2);
class MostradorLCD {
  private:
    LiquidCrystal_I2C *lcd_i2c;
  public:
    MostradorLCD (LiquidCrystal_I2C *lcd){
      lcd_i2c = lcd;     
      lcd_i2c->init(); // initialize the lcd
      lcd_i2c->backlight();

    };
    void mostraL1(char *texto){
      Serial.printf("L1: %s\n",texto);
      lcd_i2c->setCursor(0, 0); 
      lcd_i2c->printf("%-16s",texto);
    };
    void mostraL1tipoCard(char *texto){
      Serial.printf("L1: %s\n",texto);
      lcd_i2c->setCursor(0, 0); 
      lcd_i2c->printf("Tp:%s",texto);
    };
    void mostraL2(char *texto){
      lcd_i2c->setCursor(0, 1); 
      lcd_i2c->printf("%-16s",texto);
    };
    void mostraL2Distancia(int dist){
      lcd_i2c->setCursor(0, 1); 
      lcd_i2c->printf("dist:%4i cm",dist);
    };

};
MostradorLCD *lcd = NULL;
//////////////////////////////

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  SPI.begin();
  //------------------------//
  lcd = new MostradorLCD(&lcd_i2cBase);
  //------------------------//
  leitor = new LeitorRFID(&rfidBase);
  //------------------------//  
}
void loop() {
  lcd->mostraL1("Lendo Cartao:");
  leitor->leCartao();
  if(leitor->cartaoFoiLido()){
    lcd->mostraL1tipoCard(leitor->tipoCartao());
    lcd->mostraL2(leitor->cartaoLido());
    leitor->resetarLeitura();
    delay(1000);
  }
}
