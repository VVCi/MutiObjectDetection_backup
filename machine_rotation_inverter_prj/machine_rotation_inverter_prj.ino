/*
   @Motor Winding Machine Rotation Counter
   @Date: March - 2021
   @Author:
*/

/*-------INPUT TABLE -----
   Start Button:      Pin 2
   Stop Button:       Pin 3
   Push Up Button:    Pin 5
   Push Down Button:  Pin 6
   FWD Option:        Pin 7
   REV Option:        Pin 8
   --
   Sensor Pin
   Sensor Counter:    Pin 9 (or Interrupt)
   --
   LCD Pin
   Waiting
*/

/*------OUTPUT TABLE--------
   Inverter Control Pin
   FWD Option:        Pin 11
   REV Option:        Pin 12
*/

/* MACRO DEFINE
*/

/*------VARIABLE TABLE-------
   Cycle target:                CycleTarget
   Rotation present:            RoPresent
   Temporary rotation present:  RoTmpPresent
   Temporary cycle target:      CycleTmpTarget

   Sensor state:                SensorState
   Last sensor state:           LastSensorState
   Sensor push counter:         SensorPushCounter

*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define START_BUTTON        2
#define STOP_BUTTON         3

#define PUSH_UP_BUTTON      10
#define PUSH_DOWN_BUTTON    8
#define PUSH_FWD_BUTTON     5
#define PUSH_REV_BUTTON     6
#define SENSOR_COUNTER      9

#define RUN_FWD             11
#define RUN_REV             12

/*DEBUG VAR*/
int32_t DeBug                 = -1;
int32_t DeBugSt               = -1;

/* VARIABLE DEFINE
*/

uint8_t CycleTmpTarget;

// Sensor Counter
uint32_t SensorState          = 0;
uint32_t LastSensorState      = 0;
uint32_t SensorPushCounter    = 0;

// Push Up Button State
uint32_t PushUpBtState        = 0;
uint32_t LastPushUpBtState    = 0;
int32_t PushUpBtCounter       = 0;

// Push Down Button State
uint32_t PushDownBtState      = 0;
uint32_t LastPushDownBtState  = 0;
int32_t PushDownBtCounter     = 0;

uint32_t ModeFwd = 0;
uint32_t ModeRev = 0;

void setup() {

  Serial.begin(115200);
  pinMode(START_BUTTON, INPUT_PULLUP);
  pinMode(STOP_BUTTON, INPUT_PULLUP);
  pinMode(PUSH_UP_BUTTON, INPUT_PULLUP);
  pinMode(PUSH_DOWN_BUTTON, INPUT_PULLUP);
  pinMode(PUSH_FWD_BUTTON, INPUT_PULLUP);
  pinMode(PUSH_REV_BUTTON, INPUT_PULLUP);

  pinMode(SENSOR_COUNTER, INPUT_PULLUP); 

  pinMode(RUN_FWD, OUTPUT);
  pinMode(RUN_REV, OUTPUT);

  /*LCD Init*/
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("VONG QUAY: ");
  lcd.setCursor(12, 0);
  lcd.print(CycleTmpTarget);
  lcd.print("  ");
}

void loop() {

  readPushUpBt();
  readPushDownBt();

  if (digitalRead(PUSH_FWD_BUTTON) == 0) {
    DeBugSt = 1;
    Serial.println("Start Button OK");
  }

  
  if (digitalRead(PUSH_REV_BUTTON) == 0) {
    DeBugSt = 2;
    Serial.println("Start Button OK");
  }

  /*Run Fwd*/
  if (digitalRead(START_BUTTON) == 0 && DeBugSt == 1) {
    
    lcd.setCursor(1, 0);
    lcd.print("VONG QUAY: ");
    lcd.setCursor(12, 0);
    lcd.print(CycleTmpTarget);

    digitalWrite(RUN_FWD, HIGH);
    digitalWrite(RUN_REV, LOW);
    Serial.println("Run FWD");
    ModeFwd = 1;
    DeBug = 0;
    
  }

  /*Run Rev*/
  if (digitalRead(START_BUTTON) == 0 && DeBugSt == 2) {
    lcd.setCursor(1, 0);
    lcd.print("VONG QUAY: ");
    lcd.setCursor(12, 0);
    lcd.print(CycleTmpTarget);

    digitalWrite(RUN_REV, HIGH);
    digitalWrite(RUN_FWD, LOW);
    Serial.println("Run REV");
    ModeRev = 1;
    DeBug = 0;
  }

  /*Safe Mode - Disable All*/
  if (digitalRead(STOP_BUTTON) == 0) {
    DeBug = -1;
    Serial.println("Stopped !");
  }

  if (DeBug == -1) {
    brakeFwd();
    brakeRev();
    ModeRev = 0;
    ModeFwd = 0;
  }
  if (ModeRev == 1 || ModeFwd == 1) {
    readCounter(CycleTmpTarget);
  }
}

void readCounter(uint32_t CycleTmpTarget) {
  
  SensorState = digitalRead(SENSOR_COUNTER);
  delay(50);
  if (SensorState != LastSensorState) {
    if (SensorState == 0) {
      SensorPushCounter++;
      Serial.print("Vong quay: ");
      Serial.println(SensorPushCounter);
      //lcd.setCursor(2,0);
      lcd.setCursor(7, 1);
      if (SensorState <= CycleTmpTarget + 1) {
        lcd.print(SensorPushCounter);
      }
    }
  }

  LastSensorState = SensorState;

  if (SensorPushCounter == CycleTmpTarget + 1) {
    SensorPushCounter = 0;
    Serial.println(SensorPushCounter);
    LastSensorState = 0;
    DeBug = -1;
    lcd.setCursor(7, 1);
    lcd.print("  ");
  }
}

void readPushUpBt() {
  PushUpBtState = digitalRead(PUSH_UP_BUTTON);
  if (PushUpBtState != LastPushUpBtState) {
    if (PushUpBtState == 0) {
      PushUpBtCounter++;
      //PushDownBtCounter--;

      delay(200);
      CycleTmpTarget = PushUpBtCounter;

      lcd.setCursor(1, 0);
      lcd.print("VONG QUAY: ");
      lcd.setCursor(12, 0);
      lcd.print(CycleTmpTarget);
    }
  }

  LastPushUpBtState = PushUpBtState;
}

void readPushDownBt() {
  PushDownBtState = digitalRead(PUSH_DOWN_BUTTON);
  if (PushDownBtState != LastPushDownBtState) {
    if (PushDownBtState == 0) {
      PushUpBtCounter--;
      if (PushUpBtCounter < 0) {
        PushUpBtCounter = 0;
      }
      CycleTmpTarget = PushUpBtCounter;

      delay(200);
      lcd.setCursor(1, 0);
      lcd.print("VONG QUAY: ");
      lcd.setCursor(12, 0);
      lcd.print(CycleTmpTarget);
      lcd.print("   ");

    }
  }

  LastPushDownBtState = PushDownBtState;
}


void brakeFwd() {
  digitalWrite(RUN_FWD, LOW);
}

void brakeRev() {
  digitalWrite(RUN_REV, LOW);
}
