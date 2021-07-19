#include <Servo.h>

//Creación objeto servo motor
Servo mot;

void setup() {
  Serial.begin(9600);
  mot.attach(11);
}

void loop() {
  //Posición inicial
  int pos= 0;
  mot.write(pos);
  
  for (pos= 0;pos<= 180;pos++)
  {
    Serial.println(pos);
    mot.write(pos);
    delay(10);
  }

  for (pos= 180;pos>= 0;pos--)
  {
    Serial.println(pos);
    mot.write(pos);
    delay(10);
  }
}
