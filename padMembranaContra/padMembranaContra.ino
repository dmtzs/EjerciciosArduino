#include <Keypad.h>

//--------Variables tamaño de teclado--------
const byte totFilas= 4;
const byte totColum= 4;

//--------Layout teclado--------
char teclas[totFilas][totColum]= {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
  };

//--------Definición de pines para teclado--------
byte filaPins[totFilas]= {11, 10, 9, 8};
byte columnaPins[totColum]= {7, 6, 5, 4};

Keypad keypad= Keypad(makeKeymap(teclas), filaPins, columnaPins, totFilas, totColum);

//--------Variables contraseñas--------
char claveReci[9];
char claveMaestra[9]= "1234B*56";
byte indice= 0;
int incorrecto= 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  char teclaPres= keypad.getKey();

  if (incorrecto== 3)
  {
    Serial.println("Ya no puedes ingresar mas dígitos");
    delay(2000);
  }
  else
  {
    if (teclaPres)
    {
      claveReci[indice]= teclaPres;
      indice++;
      Serial.print(teclaPres);
    }

    if (indice== 8)
    {
      if (!strcmp(claveReci, claveMaestra))
      {
        Serial.println("\nCorrecta");
      }
      else
      {
        Serial.println("\nIncorrecta");
        incorrecto++;
      }
      indice= 0;
    }
  }
}
