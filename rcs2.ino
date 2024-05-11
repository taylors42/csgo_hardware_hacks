#include <hidboot.h>
#include <Mouse.h>

bool rcs_toggle = false;
const int ledPin = LED_BUILTIN;
const float sensitivity = 1.8;

// delaty factor's in ms
const int delay_factor_ak47 = 98;
const int delay_factor_m4a4 = 88;
const int delay_factor_galil = 90

// controller vars
int controller = 0;

// arrays for recoil control
const int ak47_rcs[][2] = {
  {-4 * sensitivity, 7 * sensitivity}, 
  {4 * sensitivity, 19 * sensitivity},  
  {-3 * sensitivity, 29 * sensitivity},  
  {-1 * sensitivity, 31 * sensitivity},  
  {13 * sensitivity, 31 * sensitivity}, 
  {8 * sensitivity, 28 * sensitivity},   
  {13 * sensitivity, 21 * sensitivity},  
  {-17 * sensitivity, 12 * sensitivity}, 
  {-42 * sensitivity, -3 * sensitivity}, 
  {-21 * sensitivity, 2 * sensitivity},  
  {12* sensitivity,  11 * sensitivity},  
  {-15 * sensitivity, 7 * sensitivity},  
  {-26 * sensitivity, -8 * sensitivity},   
  {-3 * sensitivity, 4 * sensitivity},    
  {40 * sensitivity, 1 * sensitivity},   
  {19 * sensitivity, 7 * sensitivity},   
  {14 * sensitivity, 10 * sensitivity},   
  {27 * sensitivity, 0 * sensitivity},   
  {33 * sensitivity, -10 * sensitivity},  
  {-21 * sensitivity, -2 * sensitivity},   
  {-7 * sensitivity, 3 * sensitivity},   
  {-8 * sensitivity, 4 * sensitivity},   
  {19 * sensitivity, -3 * sensitivity},    
  {5 * sensitivity, 6 * sensitivity},    
  {-20 * sensitivity, -1 * sensitivity},   
  {-33 * sensitivity, -4 * sensitivity},
  {-45 * sensitivity, -21 * sensitivity},
  {-14 * sensitivity, 1 * sensitivity}, 
  {-4 * sensitivity, 7 * sensitivity}  
};

const int m4a4_rcs[][2] = {
  {2 * sensitivity, 7 * sensitivity},
  {0 * sensitivity, 9 * sensitivity},
  {-6 * sensitivity, 16 * sensitivity},
  {7 * sensitivity, 21 * sensitivity},
  {-9 * sensitivity, 23 * sensitivity},
  {-5 * sensitivity, 27 * sensitivity},
  {16 * sensitivity, 15 * sensitivity},
  {11 * sensitivity, 13 * sensitivity},
  {22 * sensitivity, 5 * sensitivity},
  {-4 * sensitivity, 11 * sensitivity},
  {-18 * sensitivity, 6 * sensitivity},
  {-30 * sensitivity, -4 * sensitivity},
  {-24 * sensitivity, 0 * sensitivity},
  {-25 * sensitivity, -6 * sensitivity},
  {0 * sensitivity, 4 * sensitivity},
  {8 * sensitivity, 4 * sensitivity},
  {-11 * sensitivity, 1 * sensitivity},
  {-13 * sensitivity, -2 * sensitivity},
  {2 * sensitivity, 2 * sensitivity},
  {33 * sensitivity, -1 * sensitivity},
  {10 * sensitivity, 6 * sensitivity},
  {27 * sensitivity, 3 * sensitivity},
  {10 * sensitivity, 2 * sensitivity},
  {11 * sensitivity, 0 * sensitivity},
  {-12 * sensitivity, 0 * sensitivity},
  {6 * sensitivity, 5 * sensitivity},
  {4 * sensitivity, 5 * sensitivity},
  {3 * sensitivity, 1 * sensitivity},
  {4 * sensitivity, -1 * sensitivity}
};

const int mac10_rcs[][2] = {
  
}

const int galil_rcs[][2] = {
  {4 * sensitivity, 4 * sensitivity},
  {-2 * sensitivity, 5 * sensitivity},
  {6 * sensitivity, 10 * sensitivity},
  {12 * sensitivity, 15 * sensitivity},
  {-1 * sensitivity, 21 * sensitivity},
  {2 * sensitivity, 24 * sensitivity},
  {6 * sensitivity, 16 * sensitivity},
  {11 * sensitivity, 10 * sensitivity},
  {-4 * sensitivity, 14 * sensitivity},
  {-22 * sensitivity, 8 * sensitivity},
  {-30 * sensitivity, -3 * sensitivity},
  {-29 * sensitivity, -13 * sensitivity},
  {-9 * sensitivity, 8 * sensitivity},
  {-12 * sensitivity, 2 * sensitivity},
  {-7 * sensitivity, 1 * sensitivity},
  {0 * sensitivity, 1 * sensitivity},
  {4 * sensitivity, 7 * sensitivity},
  {25 * sensitivity, 7 * sensitivity},
  {14 * sensitivity, 4 * sensitivity},
  {25 * sensitivity, -3 * sensitivity},
  {31 * sensitivity, -9 * sensitivity},
  {6 * sensitivity, 3 * sensitivity},
  {-12 * sensitivity, 3 * sensitivity},
  {13 * sensitivity, -1 * sensitivity},
  {10 * sensitivity, -1 * sensitivity},
  {16 * sensitivity, -4 * sensitivity},
  {-9 * sensitivity, 5 * sensitivity},
  {-32 * sensitivity, -5 * sensitivity},
  {-24 * sensitivity, -3 * sensitivity},
  {-15 * sensitivity, 5 * sensitivity},
  {6 * sensitivity, 8 * sensitivity},
  {-14 * sensitivity, -3 * sensitivity},
  {-24 * sensitivity, -14 * sensitivity},
  {-13 * sensitivity, -1 * sensitivity}
}
const int mp7_rcs[][2] = {
  
}

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Mouse.begin();
}

void loop() {

  if (Serial.available() > 0) {
    char inputChar = Serial.read();

    if (rcs_toggle == true) {
      digitalWrite(ledPin, HIGH);
    } else { 
      digitalWrite(ledPin, LOW);
    }

    if (inputChar == 'x') {
      rcs_toggle = !rcs_toggle;
    } else {
      int index = inputChar - '1'; 
      if (contro && index < sizeof(movements) / sizeof(movements[0])) {
        if (rcs_toggle == true) {
          Mouse.move(movements[index][0], movements[index][1]);
          delay(90);
        } else {
          if (index < sizeof(movements2) / sizeof(movements2[0])) {
            Mouse.move(movements2[index][0], movements2[index][1]);
            delay(90);
          }
        }
      }
    }
  }
}
