
// defines and enums

// types
typedef struct led_map_s {
  uint8_t gndLine;
  uint8_t vccLine;
} led_map_t;

// physical pins
const int decoraSwitch = A2;
const int leftToggleSwitch = 12;
const int rightToggleSwitch = 8;

const int DECORA_GREEN_LED = 7;
const int DECORA_RED_LED = A5;
const int LEFT_TOGGLE_GREEN_LED = 2;
const int LEFT_TOGGLE_RED_LED = 5;
const int RIGHT_TOGGLE_GREEN_LED = 6;
const int RIGHT_TOGGLE_RED_LED = 3;
const int PUSHBUTTON_LED_1 = A3;
const int PUSHBUTTON_LED_2 = A1;
const int PUSHBUTTON_LED_3 = A4;
const int PUSHBUTTON_LED_4 = 4;

const int PUSHBUTTON_1 = 13;
const int PUSHBUTTON_2 = 11;
const int PUSHBUTTON_3 = 10;
const int PUSHBUTTON_4 = A0;

// function prototypes


// function definitions

void setup() {
  // initialize the switches:
  pinMode(decoraSwitch, INPUT_PULLUP);
  pinMode(leftToggleSwitch, INPUT_PULLUP);
  pinMode(rightToggleSwitch, INPUT_PULLUP);
  pinMode(PUSHBUTTON_1, INPUT_PULLUP);
  pinMode(PUSHBUTTON_2, INPUT_PULLUP);
  pinMode(PUSHBUTTON_3, INPUT_PULLUP);
  pinMode(PUSHBUTTON_4, INPUT_PULLUP);

  // initialize the LEDs
  pinMode(DECORA_GREEN_LED, OUTPUT);
  pinMode(DECORA_RED_LED, OUTPUT);
  pinMode(LEFT_TOGGLE_GREEN_LED, OUTPUT);
  pinMode(LEFT_TOGGLE_RED_LED, OUTPUT);
  pinMode(RIGHT_TOGGLE_GREEN_LED, OUTPUT);
  pinMode(RIGHT_TOGGLE_RED_LED, OUTPUT);
  pinMode(PUSHBUTTON_LED_1, OUTPUT);
  digitalWrite(PUSHBUTTON_LED_1, LOW);
  pinMode(PUSHBUTTON_LED_2, OUTPUT);
  digitalWrite(PUSHBUTTON_LED_2, LOW);
  pinMode(PUSHBUTTON_LED_3, OUTPUT);
  digitalWrite(PUSHBUTTON_LED_3, LOW);
  pinMode(PUSHBUTTON_LED_4, OUTPUT);
  digitalWrite(PUSHBUTTON_LED_4, LOW);

  // initialize serial communication:
  Serial.begin(115200);
}

void loop() {
  if(digitalRead(decoraSwitch)){
    digitalWrite(DECORA_GREEN_LED, HIGH);
    digitalWrite(DECORA_RED_LED, LOW);
  } else {
    digitalWrite(DECORA_GREEN_LED, LOW);
    digitalWrite(DECORA_RED_LED, HIGH);
  }

  if(digitalRead(leftToggleSwitch)){
    digitalWrite(LEFT_TOGGLE_GREEN_LED, LOW);
    digitalWrite(LEFT_TOGGLE_RED_LED, HIGH);
  } else {
    digitalWrite(LEFT_TOGGLE_GREEN_LED, HIGH);
    digitalWrite(LEFT_TOGGLE_RED_LED, LOW);
  }

  if(digitalRead(rightToggleSwitch)){
    digitalWrite(RIGHT_TOGGLE_GREEN_LED, LOW);
    digitalWrite(RIGHT_TOGGLE_RED_LED, HIGH);
  } else {
    digitalWrite(RIGHT_TOGGLE_GREEN_LED, HIGH);
    digitalWrite(RIGHT_TOGGLE_RED_LED, LOW);
  }

  if(digitalRead(PUSHBUTTON_1)){
    digitalWrite(PUSHBUTTON_LED_1, LOW);
  } else {
    digitalWrite(PUSHBUTTON_LED_1, HIGH);
  }

  if(digitalRead(PUSHBUTTON_2)){
    digitalWrite(PUSHBUTTON_LED_2, LOW);
  } else {
    digitalWrite(PUSHBUTTON_LED_2, HIGH);
  }

  if(digitalRead(PUSHBUTTON_3)){
    digitalWrite(PUSHBUTTON_LED_3, LOW);
  } else {
    digitalWrite(PUSHBUTTON_LED_3, HIGH);
  }

  if(digitalRead(PUSHBUTTON_4)){
    digitalWrite(PUSHBUTTON_LED_4, LOW);
  } else {
    digitalWrite(PUSHBUTTON_LED_4, HIGH);
  }
}
