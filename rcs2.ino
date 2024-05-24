#include <hidboot.h>
#include <Mouse.h>
#include <U8g2lib.h>
#include <Wire.h>
#define OLED_ADDRESS 0x3C

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
const float sensitivity = 1.7;
const float m4_sense = 1.20;
const float gl_sense = 0;
int controller = 0;
const float ak_sense = 1.07;
const int delay_factor_ak47 = 90;
const int delay_factor_m4a4 = 88;
const int delay_factor_galil = 90;

const int ak47_rcs[][2] = {
  {-4 * sensitivity * ak_sense, 7 * sensitivity * ak_sense}, 
  {4 * sensitivity * ak_sense, 19 * sensitivity * ak_sense},  
  {-3 * sensitivity * ak_sense, 29 * sensitivity * ak_sense},  
  {-1 * sensitivity * ak_sense, 31 * sensitivity * ak_sense},  
  {13 * sensitivity * ak_sense, 31 * sensitivity * ak_sense}, 
  {8 * sensitivity * ak_sense, 28 * sensitivity * ak_sense},   
  {13 * sensitivity * ak_sense, 21 * sensitivity * ak_sense},  
  {-17 * sensitivity * ak_sense, 12 * sensitivity * ak_sense}, 
  {-42 * sensitivity * ak_sense, -3 * sensitivity * ak_sense}, 
  {-21 * sensitivity * ak_sense, 2 * sensitivity * ak_sense},  
  {12* sensitivity * ak_sense,  11 * sensitivity * ak_sense},  
  {-15 * sensitivity * ak_sense, 7 * sensitivity * ak_sense},  
  {-26 * sensitivity * ak_sense, -8 * sensitivity * ak_sense},   
  {-3 * sensitivity * ak_sense, 4 * sensitivity * ak_sense},    
  {40 * sensitivity * ak_sense, 1 * sensitivity * ak_sense},   
  {19 * sensitivity * ak_sense, 7 * sensitivity * ak_sense},   
  {14 * sensitivity * ak_sense, 10 * sensitivity * ak_sense},   
  {27 * sensitivity * ak_sense, 0 * sensitivity * ak_sense},   
  {33 * sensitivity * ak_sense, -10 * sensitivity * ak_sense},  
  {-21 * sensitivity * ak_sense, -2 * sensitivity * ak_sense},   
  {-7 * sensitivity * ak_sense, 3 * sensitivity * ak_sense},   
  {-8 * sensitivity * ak_sense, 4 * sensitivity * ak_sense},   
  {19 * sensitivity * ak_sense, -3 * sensitivity * ak_sense},    
  {5 * sensitivity * ak_sense, 6 * sensitivity * ak_sense},    
  {-20 * sensitivity * ak_sense, -1 * sensitivity * ak_sense},   
  {-33 * sensitivity * ak_sense, -4 * sensitivity * ak_sense},
  {-45 * sensitivity * ak_sense, -21 * sensitivity * ak_sense},
  {-14 * sensitivity * ak_sense, 1 * sensitivity * ak_sense}, 
  {-4 * sensitivity * ak_sense, 7 * sensitivity * ak_sense}  
};

const int m4a4_rcs[][2] = { 
  {2 * sensitivity * m4_sense, 7 * sensitivity * m4_sense},
  {0 * sensitivity * m4_sense, 9 * sensitivity * m4_sense},
  {-6 * sensitivity * m4_sense, 16 * sensitivity * m4_sense},
  {7 * sensitivity * m4_sense, 21 * sensitivity * m4_sense},
  {-9 * sensitivity * m4_sense, 23 * sensitivity * m4_sense},
  {-5 * sensitivity * m4_sense, 27 * sensitivity * m4_sense},
  {16 * sensitivity * m4_sense, 15 * sensitivity * m4_sense},
  {11 * sensitivity * m4_sense, 13 * sensitivity * m4_sense},
  {22 * sensitivity * m4_sense, 5 * sensitivity * m4_sense},
  {-4 * sensitivity * m4_sense, 11 * sensitivity * m4_sense},
  {-18 * sensitivity * m4_sense, 6 * sensitivity * m4_sense},
  {-30 * sensitivity * m4_sense, -4 * sensitivity * m4_sense},
  {-24 * sensitivity * m4_sense, 0 * sensitivity * m4_sense},
  {-25 * sensitivity * m4_sense, -6 * sensitivity * m4_sense},
  {0 * sensitivity * m4_sense, 4 * sensitivity * m4_sense},
  {8 * sensitivity * m4_sense, 4 * sensitivity * m4_sense},
  {-11 * sensitivity * m4_sense, 1 * sensitivity * m4_sense},
  {-13 * sensitivity * m4_sense, -2 * sensitivity * m4_sense},
  {2 * sensitivity * m4_sense, 2 * sensitivity * m4_sense},
  {33 * sensitivity * m4_sense, -1 * sensitivity * m4_sense},
  {10 * sensitivity * m4_sense, 6 * sensitivity * m4_sense},
  {27 * sensitivity * m4_sense, 3 * sensitivity * m4_sense},
  {10 * sensitivity * m4_sense, 2 * sensitivity * m4_sense},
  {11 * sensitivity * m4_sense, 0 * sensitivity * m4_sense},
  {-12 * sensitivity * m4_sense, 0 * sensitivity * m4_sense},
  {6 * sensitivity * m4_sense, 5 * sensitivity * m4_sense},
  {4 * sensitivity * m4_sense, 5 * sensitivity * m4_sense},
  {3 * sensitivity * m4_sense, 1 * sensitivity * m4_sense},
  {4 * sensitivity * m4_sense, -1 * sensitivity * m4_sense}
};

const int galil_rcs[][2] = {
  {4 * sensitivity * gl_sense, 4 * sensitivity * gl_sense},
  {-2 * sensitivity * gl_sense, 5 * sensitivity * gl_sense},
  {6 * sensitivity * gl_sense, 10 * sensitivity * gl_sense},
  {12 * sensitivity * gl_sense, 15 * sensitivity * gl_sense},
  {-1 * sensitivity * gl_sense, 21 * sensitivity * gl_sense},
  {2 * sensitivity * gl_sense, 24 * sensitivity * gl_sense},
  {6 * sensitivity * gl_sense, 16 * sensitivity * gl_sense},
  {11 * sensitivity * gl_sense, 10 * sensitivity * gl_sense},
  {-4 * sensitivity * gl_sense, 14 * sensitivity * gl_sense},
  {-22 * sensitivity * gl_sense, 8 * sensitivity * gl_sense},
  {-30 * sensitivity * gl_sense, -3 * sensitivity * gl_sense},
  {-29 * sensitivity * gl_sense, -13 * sensitivity * gl_sense},
  {-9 * sensitivity * gl_sense, 8 * sensitivity * gl_sense},
  {-12 * sensitivity * gl_sense, 2 * sensitivity * gl_sense},
  {-7 * sensitivity * gl_sense, 1 * sensitivity * gl_sense},
  {0 * sensitivity * gl_sense, 1 * sensitivity * gl_sense},
  {4 * sensitivity * gl_sense, 7 * sensitivity * gl_sense},
  {25 * sensitivity * gl_sense, 7 * sensitivity * gl_sense},
  {14 * sensitivity * gl_sense, 4 * sensitivity * gl_sense},
  {25 * sensitivity * gl_sense, -3 * sensitivity * gl_sense},
  {31 * sensitivity * gl_sense, -9 * sensitivity * gl_sense},
  {6 * sensitivity * gl_sense, 3 * sensitivity * gl_sense},
  {-12 * sensitivity * gl_sense, 3 * sensitivity * gl_sense},
  {13 * sensitivity * gl_sense, -1 * sensitivity * gl_sense},
  {10 * sensitivity * gl_sense, -1 * sensitivity * gl_sense},
  {16 * sensitivity * gl_sense, -4 * sensitivity * gl_sense},
  {-9 * sensitivity * gl_sense, 5 * sensitivity * gl_sense},
  {-32 * sensitivity * gl_sense, -5 * sensitivity * gl_sense},
  {-24 * sensitivity * gl_sense, -3 * sensitivity * gl_sense},
  {-15 * sensitivity * gl_sense, 5 * sensitivity * gl_sense},
  {6 * sensitivity * gl_sense, 8 * sensitivity * gl_sense},
  {-14 * sensitivity * gl_sense, -3 * sensitivity * gl_sense},
  {-24 * sensitivity * gl_sense, -14 * sensitivity * gl_sense},
  {-13 * sensitivity * gl_sense, -1 * sensitivity * gl_sense}
};

void setup() {
  Serial.begin(9600);
  Mouse.begin();
  Wire.begin();
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.print("RCS System");
}

void loop() {

  u8g2.setFont(u8g2_font_logisoso32_tf);
  u8g2.setCursor(0, 50);

  if (Serial.available() > 0) {

    char inputChar = Serial.read();
    
    if (inputChar == 'x') {
      if (controller >= 3) {
        controller = 0;
      }
      controller++; 

      } else {
    u8g2.clearBuffer();
    switch(controller) {
      case 0: 
        u8g2.print("rcs off"); 
        break;
      case 1: 
        u8g2.print("AK47"); 
        break;
      case 2: 
        u8g2.print("M4A4"); 
        break;
      case 3:
        u8g2.print("GALIL"); 
        break;
      }
    u8g2.sendBuffer();
        
        int index = inputChar - '1'; 
        
        // if ( controller == 1 && index >= 0 && index < sizeof(ak47_rcs) / sizeof(ak47_rcs[0])) {
        //   Mouse.move(ak47_rcs[index][0], ak47_rcs[index][1]);
        //   delay(delay_factor_ak47);
        // } else if ( controller == 2 && index >= 0 && index < sizeof(m4a4_rcs) / sizeof(m4a4_rcs[0])) {
        //   Mouse.move(m4a4_rcs[index][0], m4a4_rcs[index][1]);
        //   delay(delay_factor_m4a4);
        // } else if ( controller == 3 && index >= 0 && index < sizeof(galil_rcs) / sizeof(galil_rcs[0])) {
        //   Mouse.move(galil_rcs[index][0], galil_rcs[index][1]);
        //   delay(delay_factor_galil);
        // } else {

        // }
    }
  }
}


