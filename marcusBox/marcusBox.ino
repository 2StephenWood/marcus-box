
// defines and enums
enum led_e {
  DECORA_GREEN_LED,
  DECORA_RED_LED,
  LEFT_TOGGLE_GREEN_LED,
  LEFT_TOGGLE_RED_LED,
  RIGHT_TOGGLE_GREEN_LED,
  RIGHT_TOGGLE_RED_LED,
  PUSHBUTTON_LED_1,
  PUSHBUTTON_LED_2,
  PUSHBUTTON_LED_3,
  PUSHBUTTON_LED_4,
  LED_COUNT
};

// physical pins
const int decoraSwitch = A2;
const int leftToggleSwitch = 12;
const int rightToggleSwitch = 2;

const int ledGnd1 = PIN_A1;
const int ledGnd2 = PIN_A0;
const int ledGnd3 = 6;
const int ledVcc1 = PIN_A3;
const int ledVcc2 = 7;
const int ledVcc3 = 0;
const int ledVcc4 = 1;

//tbd
//const int pushButton1 = 0;
//const int pushButton2 = 0;
//const int pushButton3 = 0;
//const int pushButton4 = 0;

// global variables
int ledStates[LED_COUNT] = {0};

// function prototypes
void setLed(enum led_e led, bool on);

void setup() {
  // initialize the switches:
  pinMode(decoraSwitch, INPUT_PULLUP);
  pinMode(leftToggleSwitch, INPUT_PULLUP);
  pinMode(rightToggleSwitch, INPUT_PULLUP);

  // initialize the LEDs matrix rows and cols
  pinMode(ledGnd1, OUTPUT);
  pinMode(ledGnd2, OUTPUT);
  pinMode(ledGnd3, OUTPUT);
  pinMode(ledVcc1, OUTPUT);
  pinMode(ledVcc2, OUTPUT);
  pinMode(ledVcc3, OUTPUT);
  pinMode(ledVcc4, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);

  // test matrix
  for(int i = 0; i < 10; i++){
    setLed(i, true);
    setLed(i, false);
  }
}


void loop() {
  //original code before switching to LED matrix:
//  if(digitalRead(decoraSwitch)){
//    digitalWrite(decoraGreenLed, HIGH);
//    digitalWrite(decoraRedLed, LOW);
//  } else {
//    digitalWrite(decoraGreenLed, LOW);
//    digitalWrite(decoraRedLed, HIGH);
//  }
//  if(digitalRead(leftToggleSwitch)){
//    digitalWrite(leftToggleGreenLed, LOW);
//    digitalWrite(leftToggleRedLed, HIGH);
//  } else {
//    digitalWrite(leftToggleGreenLed, HIGH);
//    digitalWrite(leftToggleRedLed, LOW);
//  }
//  if(digitalRead(rightToggleSwitch)){
//    digitalWrite(rightToggleGreenLed, LOW);
//    digitalWrite(rightToggleRedLed, HIGH);
//  } else {
//    digitalWrite(rightToggleGreenLed, HIGH);
//    digitalWrite(rightToggleRedLed, LOW);
//  }
}

void setLed(enum led_e led, bool on) {
  ledStates[led] = on;
  switch(led){
    case DECORA_GREEN_LED:
      if(on){
        digitalWrite(ledGnd1, LOW);
      }
      break;
    case DECORA_RED_LED:
      digitalWrite(ledGnd2, LOW);
      break;
    case LEFT_TOGGLE_GREEN_LED:
      digitalWrite(ledGnd3, LOW);
      break;
    case LEFT_TOGGLE_RED_LED:
      digitalWrite(ledGnd3, LOW);
      break;
    case RIGHT_TOGGLE_GREEN_LED:
      digitalWrite(ledGnd3, LOW);
      break;
    case RIGHT_TOGGLE_RED_LED:
      digitalWrite(ledGnd3, LOW);
      break;
    case PUSHBUTTON_LED_1:
      digitalWrite(ledGnd3, LOW);
      break;
    case PUSHBUTTON_LED_2:
      digitalWrite(ledGnd3, LOW);
      break;
    case PUSHBUTTON_LED_3:
      digitalWrite(ledGnd3, LOW);
      break;
    case PUSHBUTTON_LED_4:
      digitalWrite(ledGnd3, LOW);
      break;
    
  }
}
