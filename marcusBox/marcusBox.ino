
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
led_map_t ledMap[LED_COUNT] = {//Gnd, Vcc
    /* DECORA_GREEN_LED */       {0, 0},
    /* DECORA_RED_LED */         {0, 1},
    /* LEFT_TOGGLE_GREEN_LED */  {0, 2},
    /* LEFT_TOGGLE_RED_LED */    {0, 3},
    /* RIGHT_TOGGLE_GREEN_LED */ {1, 0},
    /* RIGHT_TOGGLE_RED_LED */   {1, 1},
    /* PUSHBUTTON_LED_1 */       {1, 2},
    /* PUSHBUTTON_LED_2 */       {2, 0},
    /* PUSHBUTTON_LED_3 */       {2, 1},
    /* PUSHBUTTON_LED_4 */       {2, 2}
};
int ledStates[LED_VCC_LINE_CNT][LED_GND_LINE_CNT] = {0};

// function prototypes
void setLed(enum led_e led, bool on);
void refreshLeds();
void checkSwitches();

// Main functions

void setup() {
  // initialize the switches:
  pinMode(decoraSwitch, INPUT_PULLUP);
  pinMode(leftToggleSwitch, INPUT_PULLUP);
  pinMode(rightToggleSwitch, INPUT_PULLUP);

  // initialize the LED grounds and Vcc pins
  for(int i=0; i < LED_VCC_LINE_CNT; i++){
    pinMode(vccPins[i], OUTPUT);
  }
  for(int i=0; i < LED_GND_LINE_CNT; i++){
    pinMode(gndPins[i], OUTPUT);
  }
  
  // initialize serial communication:
  Serial.begin(115200);

  // test matrix
  for(int i = 0; i < LED_COUNT; i++){
    Serial.print("Turning on LED ");
    Serial.println(i);
    setLed((enum led_e)i, true);
    delay(5000);
    setLed((enum led_e)i, false);
  }
}


void loop() {
  checkSwitches();

  refreshLeds();
}


// helper functions


void checkSwitches(){
  if(digitalRead(decoraSwitch)){
    setLed(DECORA_GREEN_LED, true);
      setLed(DECORA_RED_LED, false);
  } else {
      setLed(DECORA_RED_LED, true);
    setLed(DECORA_GREEN_LED, false);
  }
  if(digitalRead(leftToggleSwitch)){
      setLed(LEFT_TOGGLE_GREEN_LED, true);
      setLed(LEFT_TOGGLE_RED_LED, false);
  } else {
      setLed(LEFT_TOGGLE_RED_LED, true);
      setLed(LEFT_TOGGLE_GREEN_LED, false);
  }
  if(digitalRead(rightToggleSwitch)){
      setLed(RIGHT_TOGGLE_GREEN_LED, true);
      setLed(RIGHT_TOGGLE_RED_LED, false);
  } else {
      setLed(RIGHT_TOGGLE_RED_LED, true);
      setLed(RIGHT_TOGGLE_GREEN_LED, false);
  }
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
  Serial.print("Setting ground ");
  Serial.print(thisGnd);
  Serial.print(", Vcc ");
  Serial.println(thisVcc);
}
