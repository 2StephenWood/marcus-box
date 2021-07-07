
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

// types
typedef struct led_map_s {
  uint8_t gndLine;
  uint8_t vccLine;
} led_map_t;

// physical pins
const int decoraSwitch = A2;
const int leftToggleSwitch = 12;
const int rightToggleSwitch = 2;

const int LED_VCC_LINE_CNT = 4;
const int vccPins[LED_VCC_LINE_CNT] = {A3, 7, 0, 1};
const int LED_GND_LINE_CNT = 3;
const int gndPins[LED_GND_LINE_CNT] = {A1, A0, 6};

//tbd
//const int pushButton1 = 0;
//const int pushButton2 = 0;
//const int pushButton3 = 0;
//const int pushButton4 = 0;

// global variables
led_map_t ledMap[LED_COUNT] = {
    /* DECORA_GREEN_LED */       {0, 0},
    /* DECORA_RED_LED */         {0, 0},
    /* LEFT_TOGGLE_GREEN_LED */  {0, 0},
    /* LEFT_TOGGLE_RED_LED */    {0, 0},
    /* RIGHT_TOGGLE_GREEN_LED */ {0, 0},
    /* RIGHT_TOGGLE_RED_LED */   {0, 0},
    /* PUSHBUTTON_LED_1 */       {0, 0},
    /* PUSHBUTTON_LED_2 */       {0, 0},
    /* PUSHBUTTON_LED_3 */       {0, 0},
    /* PUSHBUTTON_LED_4 */       {0, 0}
};
int ledStates[LED_VCC_LINE_CNT][LED_GND_LINE_CNT] = {0};

// function prototypes
void setLed(enum led_e led, bool on);

void setup() {
  // initialize the switches:
  pinMode(decoraSwitch, INPUT_PULLUP);
  pinMode(leftToggleSwitch, INPUT_PULLUP);
  pinMode(rightToggleSwitch, INPUT_PULLUP);

  // initialize the LED grounds and Vcc pins
  for(int i=0; i < sizeof(vccPins); i++){
    pinMode(vccPins[i], OUTPUT);
  }
  for(int i=0; i < sizeof(gndPins); i++){
    pinMode(gndPins[i], OUTPUT);
  }
  
  // initialize serial communication:
  Serial.begin(9600);

  // test matrix
  for(int i = 0; i < LED_COUNT; i++){
    setLed((enum led_e)i, true);
    delay(500);
    setLed((enum led_e)i, false);
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

void refreshLeds() {
  // iterate over the rows (anodes):
  for (int thisVcc = 0; thisVcc < LED_VCC_LINE_CNT; thisVcc++) {
    // take the Vcc pin (anode) high:
    digitalWrite(vccPins[thisVcc], HIGH);
    // iterate over the ground lines (cathodes):
    for (int thisGnd = 0; thisGnd < LED_GND_LINE_CNT; thisGnd++) {
      // get the state of the current LED;
      int thisLed = ledStates[thisVcc][thisGnd];
      // when the Vcc is HIGH and the ground is LOW,
      // the LED where they meet turns on:
      digitalWrite(gndPins[thisGnd], thisLed);
      // turn the LED off:
      if (thisLed == LOW) {
        digitalWrite(gndPins[thisGnd], HIGH);
      }
    }
    // take the Vcc pin low to turn off the whole row:
    digitalWrite(vccPins[thisVcc], LOW);
  }
}

void setLed(enum led_e led, bool on) {
  int thisVcc = ledMap[led].vccLine;
  int thisGnd = ledMap[led].gndLine;
  ledStates[thisVcc][thisGnd] = on;
}
