// Código de prueba próximamente
#include <Wire.h>
#include <SPI.h>

#include <Adafruit_PN532.h>
#define PN532_IRQ (2)
#define PN532_RESET (3)
#define buzzer 9

// Interfaz de comunicación por I2C
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

String llaveMaestra= "1066725263";

void setup(void) {

  Serial.begin(9600);
  nfc.begin();
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);

  // Configurar para leer etiquetas RFID
  nfc.setPassiveActivationRetries(0xFF);
  nfc.SAMConfig();
}

void loop(void) {
  boolean success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;

  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength);

  if (success) {
    Serial.println("Tarjeta encontrada");
    Serial.print("UID Longitud: ");
    Serial.print(uidLength, DEC); Serial.println(" bytes");
    Serial.print("UID: "); printArray(uid, uidLength);
    Serial.println("");
    digitalWrite(buzzer, LOW);
    delay(2000);
  }
  else
  {
    Serial.println("Tarjeta no encontrada");
  }
}

// Funcion auxiliar para mostrar el buffer
void printArray(byte *buffer, byte bufferSize) {
  String leido= "";
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
    leido+= buffer[i];
  }
  if (leido== llaveMaestra)
  {
    digitalWrite(buzzer, HIGH);
    Serial.println("");
    Serial.println(leido);
    Serial.println("Llave correcta");
  }
  else
  {
    digitalWrite(buzzer, HIGH);
    Serial.println("");
    Serial.println(leido);
    Serial.println("Llave incorrecta");
  }
}
