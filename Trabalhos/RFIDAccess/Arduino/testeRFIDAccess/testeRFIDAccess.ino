#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

#define SS_PIN 10
#define RST_PIN 9
#define buzzer 8
#define rele A2

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key; 

byte nuidPICC[4];


LiquidCrystal lcd(6, 7, 5, 4, 3, 2);


int qtdCartoes; 
int leBotoes=0;
void setup()

{ 

  qtdCartoes = EEPROM.read(0);
 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 



  lcd.begin(16, 2);
  pinMode(buzzer,OUTPUT);
  pinMode(rele,OUTPUT);

  digitalWrite(buzzer,LOW);
  digitalWrite(rele,LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aguard. Cartao");
}
 
void loop()
{
  aguardCartao();
  
  leBotoes = analogRead(A0);
  Serial.println(leBotoes);
  if(leBotoes>1000)
    { 
    while(leBotoes > 1000) {leBotoes = analogRead(A0); delay(50); }
    //for (byte i = 0; i < 4; i++) nuidPICC[i] = rfid.uid.uidByte[i]; 
    cadastraCartao();
    }

    if(leBotoes>100 && leBotoes<200)
    { 
    while(leBotoes>100 && leBotoes < 200) {leBotoes = analogRead(A0); delay(50); }
    //for (byte i = 0; i < 4; i++) nuidPICC[i] = rfid.uid.uidByte[i]; 
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Memoria ZERADA");
     for (int i = 0; i < 512; i++)
    EEPROM.write(i, 0);
    
    }


   
    
    
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aguard. Cartao");
  
}


void printHex(byte *buffer, byte bufferSize)
{
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void aguardCartao()
{
  
if ( ! rfid.PICC_IsNewCardPresent()) return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial()) return;

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  Serial.print(F("The NUID tag is:"));
    
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println("");
  
   // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();

verifCartao();
}

void cadastraCartao()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Aprox. Cartao");
  lcd.setCursor(0, 1);
  lcd.print("  p/ Cadastrar");
  delay(100);
  
  while ( ! rfid.PICC_IsNewCardPresent() )
  { 
    //return; 
  }

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial()) cadastraCartao();

  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  Serial.print(F("The NUID tag is:"));
    
  printHex(rfid.uid.uidByte, rfid.uid.size);
  Serial.println("");
  
   // Halt PICC
  rfid.PICC_HaltA();

  // Stop encryption on PCD
  rfid.PCD_StopCrypto1();


  if(qtdCartoes == 0)
    {
    EEPROM.write(1,rfid.uid.uidByte[0]);
    EEPROM.write(2,rfid.uid.uidByte[1]);
    EEPROM.write(3,rfid.uid.uidByte[2]);
    EEPROM.write(4,rfid.uid.uidByte[3]);
    qtdCartoes++;
    EEPROM.write(0, qtdCartoes);
    Serial.print("CartaoCadastrado >>>>   QTDCARTOES: ");
    Serial.println(qtdCartoes);
    lcd.clear();
     lcd.setCursor(0, 0);
    lcd.print("   O Cartao   ");
    lcd.setCursor(0, 1);
    lcd.print("  Foi Cadastrado   ");
          delay(2000);
          return;
    } 

  else
  {
    int j=0;
    for(int i=0; i<qtdCartoes; i++)
    {
      nuidPICC[0] = EEPROM.read(1+j);
      nuidPICC[1] = EEPROM.read(2+j);
      nuidPICC[2] = EEPROM.read(3+j);
      nuidPICC[3] = EEPROM.read(4+j);
      j=j+4;
      if( (rfid.uid.uidByte[0] == nuidPICC[0])  &&  (rfid.uid.uidByte[1] == nuidPICC[1]) &&  (rfid.uid.uidByte[2] == nuidPICC[2]) &&   (rfid.uid.uidByte[3] == nuidPICC[3]) )
      {
        Serial.println("CartaoJaSalvo");
        lcd.clear();
        lcd.setCursor(0, 1);
          lcd.print("JA EH CADASTRADO!!!");
          delay(2000);
        return;
      }
    }
    
    EEPROM.write(1+j,rfid.uid.uidByte[0]);
    EEPROM.write(2+j,rfid.uid.uidByte[1]);
    EEPROM.write(3+j,rfid.uid.uidByte[2]);
    EEPROM.write(4+j,rfid.uid.uidByte[3]);
    qtdCartoes++;
    EEPROM.write(0, qtdCartoes);
    Serial.print("CartaoCadastrado >>>>   QTDCARTOES: ");
    lcd.clear();
     lcd.setCursor(0, 0);
    lcd.print("   O Cartao   ");
    lcd.setCursor(0, 1);
    lcd.print("  Foi Cadastrado   ");
          delay(2000);
    Serial.println(qtdCartoes);
    return;
    
    
  }
  
 return;
  
}

  
void verifCartao()
{
  
  int j=0;
    for(int i=0; i<qtdCartoes; i++)
    {
      nuidPICC[0] = EEPROM.read(1+j);
      nuidPICC[1] = EEPROM.read(2+j);
      nuidPICC[2] = EEPROM.read(3+j);
      nuidPICC[3] = EEPROM.read(4+j);
      j=j+4;
      if( (rfid.uid.uidByte[0] == nuidPICC[0])  &&  (rfid.uid.uidByte[1] == nuidPICC[1]) &&  (rfid.uid.uidByte[2] == nuidPICC[2]) &&   (rfid.uid.uidByte[3] == nuidPICC[3]) )
      {
        digitalWrite(rele, HIGH);
        digitalWrite(buzzer,HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
          lcd.print("Acesso Permitido!!!");
         delay(1000);
         digitalWrite(buzzer,LOW);
         nuidPICC[0] = 0xAA;
          nuidPICC[1] = 0xAA;
          nuidPICC[2] = 0xAA;
          nuidPICC[3] = 0xAA;
          rfid.uid.uidByte[1] = 0xBB;
          rfid.uid.uidByte[2] = 0xBB;
          rfid.uid.uidByte[3] = 0xBB;
          rfid.uid.uidByte[4] = 0xBB;
          
   lcd.setCursor(0, 1);
  lcd.print("Aguardando Fechar");
     
     leBotoes = analogRead(A0);
    while(!(leBotoes>200 && leBotoes<300)) { delay(50); leBotoes = analogRead(A0);  lcd.clear(); lcd.setCursor(0, 0);     lcd.print("Acesso Permitido!!!");  lcd.setCursor(0, 1);  lcd.print("Aguardando Fechar"); }
  digitalWrite(rele, LOW);
        return;
      }
    }
      lcd.clear();
        lcd.setCursor(0, 0);
          lcd.print("Acesso NEGADO!!!");
        digitalWrite(buzzer,HIGH);
        delay(100);
        digitalWrite(buzzer,LOW);
        delay(100);
        digitalWrite(buzzer,HIGH);
        delay(100);
        digitalWrite(buzzer,LOW);
        delay(100);
        digitalWrite(buzzer,HIGH);
        delay(100);
        
         
        digitalWrite(buzzer,LOW);
        delay(100);
        digitalWrite(buzzer,HIGH);
        delay(100);
        digitalWrite(buzzer,LOW);
        delay(100);
        digitalWrite(buzzer,HIGH);
        delay(100);
        digitalWrite(buzzer,LOW);
        delay(100);
        return;
      
    
  
}



 

