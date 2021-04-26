/* Directivas de preprocesador */
#define INFPIN    3
#define SUPPIN   13
#define CANT     SUPPIN-INFPIN+1
#define DELAY    15
#define THEPIN    8

/* Variables globales */
byte ledPins[CANT];
const byte buttonPin = 2;
volatile byte currentPosition = 0;

/* Prototipos de funcion */

void recorrerLeds(byte[], int, int);
void checkPosition();

void setup()
{
  // estableciendo los pines de salida
  for (int pin = INFPIN, index = 0; pin <= SUPPIN; pin++, index++)
  {
    pinMode(pin, OUTPUT);
    ledPins[index] = pin;
  }

  // estableciendo el pin boton
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop()
{
  // interrupcion de hardware
  attachInterrupt(digitalPinToInterrupt(buttonPin), checkPosition, RISING);
  
  recorrerLeds(ledPins, CANT, DELAY);
}

/*
  Funcion    : recorrerLeds
  Argumentos : byte leds[], int n, int tDelay
  Objetivo   : recorrer un arreglo de led
  Retorno    : ---
*/
void recorrerLeds(byte leds[], int n, int tDelay)
{
  int index;

  for (index = 0; index < n; index++)
  {
    digitalWrite(leds[index], HIGH);
    delay(tDelay);
    digitalWrite(leds[index], LOW);
    delay(tDelay);
    
    currentPosition++;
  }

  for (index = n-1; index >= 0; index--)
  {
    digitalWrite(leds[index], HIGH);
    delay(tDelay);
    digitalWrite(leds[index], LOW);
    delay(tDelay);

    currentPosition--;
  }
}

/*
  Funcion    : checkPosition
  Argumentos : ---
  Objetivo   : ISR activada al presionar el boton
  Retorno    : ---
*/
void checkPosition()
{
  
}
