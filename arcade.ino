// Directivas de preprocesador

#define INFPIN     3 // pin de salida inferior en la placa
#define SUPPIN    13 // pin de salida superior en la placa
#define CANT      SUPPIN-INFPIN+1 // cantidad de pines
#define DELAY     15
#define LUCKYPIN   8 // indica el pin objetivo
#define BUTTON     2

// Estructuras

struct Juego {
  int ledPins[CANT], cantPins, tDelay;
}juego;

// Prototipos de funciones

void recorrerLeds(int[], int, int); 
boolean debounceButton (boolean);

void setup()
{
  // iniciando los datos del juego
  juego.cantPins = CANT;
  juego.tDelay = DELAY;
  
  // estableciendo y asignando los pines de salida 
  for (int pin = INFPIN, index = 0; pin <= SUPPIN; pin++, index++)
  {
    pinMode(pin, OUTPUT);
    juego.ledPins[index] = pin;
  }

  // especificando el buton
  pinMode(BUTTON, INPUT);
}

void loop()
{
  recorrerLeds(juego.ledPins, juego.cantPins, juego.tDelay);
}

/*
  Funcion    : recorrerLeds
  Argumentos : int leds[], int n, int tDelay
  Objetivo   : recorrer el arreglo de leds
  Retorno    : ---
*/
void recorrerLeds(int leds[], int n, int tDelay)
{
  int index;

  for (index = 0; index < n; index++)
  {
    digitalWrite(leds[index], HIGH);
    delay(tDelay);
    digitalWrite(leds[index], LOW);
    delay(tDelay);
  }

  for (index = n-1; index >= 0; index--)
  {
    digitalWrite(leds[index], HIGH);
    delay(tDelay);
    digitalWrite(leds[index], LOW);
    delay(tDelay);
  }
}

/*
  Funcion    : debounceButton
  Argumentos : boolean state
  Objetivo   : filtrar el ruido en el boton
  Retorno    : (boolean) stateNow
*/
boolean debounceButton (boolean state) 
{
  boolean stateNow = digitalRead(BUTTON);
  if (state != stateNow)
  {
    delay(10);
    stateNow = digitalRead(BUTTON);
  }

  return stateNow;
}
