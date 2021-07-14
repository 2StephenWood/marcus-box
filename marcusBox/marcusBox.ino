
// defines and enums
#define DEBOUNCE_TIME_MS  (200)
#define HOLD_TIME_MS      (4 * 1000)

// types
typedef enum mode_e {
  SimpleMode,
  ToggleMode
} mode_t;

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

// global variables
mode_t currentMode = SimpleMode;

// function prototypes
void switchModes(mode_t newMode);
void runSimpleMode();
void runSimpleToggleMode();

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

bool pushbuttonHeld = false;

void loop() {
  // check for held pushbuttons
  static unsigned long heldTimerStart;
  unsigned long timeNow = millis();

  if(!digitalRead(PUSHBUTTON_1)){
    if(!pushbuttonHeld) {
      pushbuttonHeld = true;
      heldTimerStart = millis();
      Serial.println("Starting button hold timer for button 1.");
    } else if((timeNow - heldTimerStart) > HOLD_TIME_MS) {
      switchModes(SimpleMode);
    }
  } else if(!digitalRead(PUSHBUTTON_2)){
    if(!pushbuttonHeld) {
      pushbuttonHeld = true;
      heldTimerStart = millis();
      Serial.println("Starting button hold timer for button 2.");
    } else if((timeNow - heldTimerStart) > HOLD_TIME_MS) {
      switchModes(ToggleMode);
    }
  } else {
    pushbuttonHeld = false;
  }

  switch(currentMode) {
    case SimpleMode:
      runSimpleMode();
      break;
    case ToggleMode:
      runToggleMode();
      break;
  }
}

void runSimpleMode() {
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

void runToggleMode() {
  static bool pushbutton1On = false;
  static bool pushbutton2On = false;
  static bool pushbutton3On = false;
  static bool pushbutton4On = false;

  // Keep the switches doing the same thing as normal mode
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

  // switch the state of each push button LED each time you push that button
  if(!digitalRead(PUSHBUTTON_1)){
    pushbutton1On = !pushbutton1On;
    delay(DEBOUNCE_TIME_MS); //debounce
  }
  if(!digitalRead(PUSHBUTTON_2)){
    pushbutton2On = !pushbutton2On;
    delay(DEBOUNCE_TIME_MS); //debounce
  }
  if(!digitalRead(PUSHBUTTON_3)){
    pushbutton3On = !pushbutton3On;
    delay(DEBOUNCE_TIME_MS); //debounce
  }
  if(!digitalRead(PUSHBUTTON_4)){
    pushbutton4On = !pushbutton4On;
    delay(DEBOUNCE_TIME_MS); //debounce
  }

  if(pushbutton1On){
    digitalWrite(PUSHBUTTON_LED_1, HIGH);
  } else {
    digitalWrite(PUSHBUTTON_LED_1, LOW);
  }

  if(pushbutton2On){
    digitalWrite(PUSHBUTTON_LED_2, HIGH);
  } else {
    digitalWrite(PUSHBUTTON_LED_2, LOW);
  }

  if(pushbutton3On){
    digitalWrite(PUSHBUTTON_LED_3, HIGH);
  } else {
    digitalWrite(PUSHBUTTON_LED_3, LOW);
  }

  if(pushbutton4On){
    digitalWrite(PUSHBUTTON_LED_4, HIGH);
  } else {
    digitalWrite(PUSHBUTTON_LED_4, LOW);
  }
}

void switchModes(mode_t newMode) {
  currentMode = newMode;
  Serial.print("Switching to mode ");
  Serial.println(newMode);

  // Flash all the LEDs to show mode change
  digitalWrite(PUSHBUTTON_LED_1, HIGH);
  digitalWrite(PUSHBUTTON_LED_2, HIGH);
  digitalWrite(PUSHBUTTON_LED_3, HIGH);
  digitalWrite(PUSHBUTTON_LED_4, HIGH);
  delay(DEBOUNCE_TIME_MS);
  digitalWrite(PUSHBUTTON_LED_1, LOW);
  digitalWrite(PUSHBUTTON_LED_2, LOW);
  digitalWrite(PUSHBUTTON_LED_3, LOW);
  digitalWrite(PUSHBUTTON_LED_4, LOW);
  delay(DEBOUNCE_TIME_MS);
}
