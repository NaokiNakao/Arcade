#define INFPIN    3
#define SUPPIN   13
#define CANT     SUPPIN-INFPIN+1
#define DELAY    15
#define THEPIN    8
#define TIMES     4

/* Variables globales */
byte ledPins[CANT];
const byte buttonPin = 2;
boolean buttonPressed = false;

/* Prototipos de funciones */

void positionControl(int*, int, boolean*);
void ledBlink(byte, int);
void changeButtonState();
void correctPosition(int, int, int, int, int);
void wrongPosition(int, int, int);

void setup() {
  // incializando los pines de salida
  for (int pin = INFPIN, index = 0; pin <= SUPPIN; pin++, index++) {
    pinMode(pin, OUTPUT);
    ledPins[index] = pin; 
  }

  // estableciendo interrupcion de hardware
  attachInterrupt(digitalPinToInterrupt(buttonPin), changeButtonState, RISING);
}

void loop() {
  int pos = 0;
  boolean forward = true, gameOver = false;

  while (!gameOver) {
    // recorriendo los leds
    positionControl(&pos, CANT, &forward);
    ledBlink(ledPins[pos], DELAY);

    // se comprueba si se presiono el boton
    if (buttonPressed)
    {
      // se comprueba si la jugada fue correcta
      if (ledPins[pos] == THEPIN) {
        correctPosition(INFPIN, SUPPIN, THEPIN, TIMES, DELAY*2);
      }
      else {
        wrongPosition(ledPins[pos], 100, TIMES);
      }
      
      break;
    }
  }
  
  buttonPressed = false;
  delay(2000);
}

/*
  Funcion    : positionControl
  Argumentos : int *currentPosition, int n, boolean forward
  Objetivo   : controlar el recorrido de los leds
  Retorno    : ---
*/
void positionControl(int *currentPosition, int n, boolean *forward) {

  if (*forward)
  {
    if (*currentPosition == n-1) 
    {
      *forward = false;
      (*currentPosition)--;
    }
    else 
    {
      (*currentPosition)++;
    }
  }
  else
  {
    if (*currentPosition == 0) 
    {
      *forward = true;
      (*currentPosition)++;
    }
    else
    {
      (*currentPosition)--;
    }
  }
  
}

/*
  Funcion    : ledBlink
  Argumentos : byte led, int tDelay
  Objetivo   : hacer parpadear un led
  Retorno    : ---
*/
void ledBlink(byte led, int tDelay) {
  digitalWrite(led, HIGH);
  delay(tDelay);
  digitalWrite(led, LOW);
  delay(tDelay);
}

/*
  Funcion    : changeButtonState
  Argumentos : ---
  Objetivo   : cambiar el estado del boton
  Retorno    : ---
*/
void changeButtonState() {
  buttonPressed = !buttonPressed;
}

/*
  Funcion    : correctPosition
  Argumentos : int inf, int sup, int center, int times, int tDelay
  Objetivo   : secuencia ganadora 
  Retorno    : ---
*/
void correctPosition(int inf, int sup, int center, int times, int tDelay) {

  int pininf, pinsup, count = 0;

  while (count < times) 
  {
    for (pininf = inf, pinsup = sup; pininf != center && pinsup != center; pininf++, pinsup--) {
      ledBlink(pininf, tDelay);
      ledBlink(pinsup, tDelay);
    }

    ledBlink(center, tDelay*2);

    count++;
  }
}

/*
  Funcion    : wrongPosition
  Argumentos : int led, int tDelay, int times
  Objetivo   : secuencia de jugada fallida
  Retorno    : ---
*/
void wrongPosition(int led, int tDelay, int times) {

  int count = 0;

  while (count < times) {
    ledBlink(led, tDelay);
    count++;
  }
}
