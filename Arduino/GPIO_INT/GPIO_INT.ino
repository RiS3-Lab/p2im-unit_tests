//NUCLEOF103
//const byte ledPin = LED_BUILTIN;
//const byte interruptPin = USER_BTN;

//ARDUINO DUE
const byte ledPin = 13;
const byte interruptPin = 2;


volatile byte state = LOW;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING  );
}

void loop() {
  digitalWrite(ledPin, state);
}

void blink() {
  state = !state;
}
