#include <BleGamepad.h> 

BleGamepad bleGamepad;

// RIGHT-JOYSTICK
#define Rx 36
#define Ry 39
#define R_Trig 21

// D-PAD
#define B1 16
#define B2 17
#define B3 18
#define B4 19

#define TILT_ESPADA 22

int buttons[6] = {16,17, 18, 19, 21 ,22};

const int numberOfPotSamples = 5;     // Number of pot samples to take (to smooth the values)
const int delayBetweenSamples = 2;    // Delay in milliseconds between pot samples
const int delayBetweenHIDReports = 5; // Additional delay in milliseconds between HID reports
const int debounceDelay = 10;        // Delay in milliseconds between button press

int previousButton1State = HIGH;
int previousButton2State = HIGH;
int previousButton3State = HIGH;
int previousButton4State = HIGH;

int previousTiltBState = HIGH;

int previousR_TrigState = HIGH;

void setup() 
{
  Serial.begin(115200);
 // for (int i = 0; i < 7; i++) {
 for (int i = 0; i < 6; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
  }
  Serial.println("Starting BLE work!");
  bleGamepad.begin();
  // The default bleGamepad.begin() above is the same as bleGamepad.begin(16, 1, true, true, true, true, true, true, true, true, false, false, false, false, false);
  // which enables a gamepad with 16 buttons, 1 hat switch, enabled x, y, z, rZ, rX, rY, slider 1, slider 2 and disabled rudder, throttle, accelerator, brake, steering
  // Auto reporting is enabled by default. 
  // Use bleGamepad.setAutoReport(false); to disable auto reporting, and then use bleGamepad.sendReport(); as needed
}
void loop() {
if (bleGamepad.isConnected()) {
   
    int currentButton1State = digitalRead(B1);
    int currentButton2State = digitalRead(B2);
    int currentButton3State = digitalRead(B3);
    int currentButton4State = digitalRead(B4);

    int currentTiltBState = digitalRead(TILT_ESPADA);
    
    int currentR_TrigState = digitalRead(R_Trig);
                           
    if (currentButton1State != previousButton1State) {
      if (currentButton1State == LOW)
        bleGamepad.press(BUTTON_1);
      else
        bleGamepad.release(BUTTON_1);
    }
    previousButton1State = currentButton1State;

    if (currentButton2State != previousButton2State) {
      if (currentButton2State == LOW)
        bleGamepad.press(BUTTON_2);
      else
        bleGamepad.release(BUTTON_2);
    }
    previousButton2State = currentButton2State;

    if (currentButton3State != previousButton3State) {
      if (currentButton3State == LOW)
        bleGamepad.press(BUTTON_3);
      else
        bleGamepad.release(BUTTON_3);
    }
    previousButton3State = currentButton3State;

    if (currentButton4State != previousButton4State) {
      if (currentButton4State == LOW)
        bleGamepad.press(BUTTON_4);
      else
        bleGamepad.release(BUTTON_4);
    }
    previousButton4State = currentButton4State;

   if (currentTiltBState != previousTiltBState) {
      if (currentTiltBState == LOW)
        bleGamepad.press(BUTTON_5);
      else
        bleGamepad.release(BUTTON_5);
    }
    previousTiltBState = currentTiltBState;

    
 if (currentR_TrigState !=  previousR_TrigState) {
      if (currentR_TrigState == LOW)
        bleGamepad.press(BUTTON_6);
      else
        bleGamepad.release(BUTTON_6);
    }
    previousR_TrigState = currentR_TrigState;
    

    int potValues3[numberOfPotSamples];
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValues3[i] = analogRead(Rx);
      delay(delayBetweenSamples);
    }
    int potValue3 = 0;
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValue3 += potValues3[i];
    }
    potValue3 = potValue3 / numberOfPotSamples;
    int adjustedValue3 = map(potValue3, 0, 4095, 127, -127);


    int potValues4[numberOfPotSamples];
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValues4[i] = analogRead(Ry);
      delay(delayBetweenSamples);
    }
    int potValue4 = 0;
    for (int i = 0 ; i < numberOfPotSamples ; i++) {
      potValue4 += potValues4[i];
    }
    potValue4 = potValue4 / numberOfPotSamples;
    int adjustedValue4 = map(potValue4, 0, 4095, 127, -127);
 
        /*
      Serial.print(adjustedValue3);
      Serial.print(" || ");
      Serial.println(adjustedValue4);
    */
    bleGamepad.setAxes(adjustedValue3, adjustedValue4, 0, 0, 0, 0, 0, 0, DPAD_CENTERED);
//   bleGamepad.setRightThumb(adjustedValue3, adjustedValue4);
    delay(delayBetweenHIDReports);
  }
  }
