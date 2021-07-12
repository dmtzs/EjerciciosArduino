#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc= NfcAdapter(pn532_i2c);

String tags[]= {"9A 9A B6 1A"};
boolean autorizado= false;

void setup(void) {
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  Serial.begin(9600);
  nfc.begin();

}

void loop(void) {
  int i;
  if (nfc.tagPresent())
  {
    digitalWrite(9, HIGH);
    
    NfcTag tag= nfc.read();
    Serial.println("Tag id: "+tag.getUidString());

    for(i=0;i < sizeof(tags);i++)
    {
      if (tag.getUidString()== tags[i])
      {
        autorizado= true;
      }
    }

    if (autorizado)
    {
      Serial.println("Autorizado");
      autorizado= false;
    }
    else
    {
      Serial.println("No autorizado");
    }
    delay(1000);
    digitalWrite(9, LOW);
  }
}
