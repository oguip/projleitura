#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>
 
//Pinos Reset e SS módulo MFRC522
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); 

int buzzer = 7;

char st[20];
 
void setup() 
{
  pinMode(2, OUTPUT); // LED verde
  pinMode(4, OUTPUT); // LED vermelho
  Serial.begin(9600);   // Inicia a serial
  SPI.begin();      // Inicia  SPI bus
  mfrc522.PCD_Init();   // Inicia MFRC522
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  //Define o número de colunas e linhas do LCD:  
  lcd.begin(16, 2);  
  mensageminicial();
}
 
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();
  if (conteudo.substring(1) == "9A A2 76 80") //UID 1 - Chaveiro
  {
    Serial.println("Guilherme, bem vindo!");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Guilherme,");
    lcd.setCursor(0,1);
    lcd.print("Acesso liberado!");
    tone(buzzer, 523, 1000);
    digitalWrite(2, HIGH);
    delay(3000);
    digitalWrite(2, LOW);
    mensageminicial();
  }
 
  if (conteudo.substring(1) == "39 78 0E B3") //UID 2 - Cartao
  {
    Serial.println("Cartao");
    Serial.println();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Cartao");
    lcd.setCursor(0,1);
    lcd.print("Acesso Negado !");
    tone(buzzer, 2000, 2000);
    digitalWrite(4, HIGH);
    delay(3000);
    digitalWrite(4, LOW);
    
    mensageminicial();
  }
} 
 
void mensageminicial()
{
  lcd.clear();
  lcd.print(" Aproxime o seu");  
  lcd.setCursor(0,1);
  lcd.print("cartao do leitor");  
}
