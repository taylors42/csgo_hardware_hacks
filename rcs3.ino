// #include <hidboot.h>
#include <Mouse.h>
#include <U8g2lib.h>
// #include <Wire.h>
// #include <Keyboard.h>
#define OLED_ADDRESS 0x3C

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int controller = 0;
const float sensitivity = 1.7;
float m4_sense = 1.20;
float gl_sense = 1.3;
float ak_sense = 1.07;
float m4a1s_sense = 0.95;
float famas_sense = 1;
float ump_sense = 1;
const int delay_factor_ak47 = 90;
const int delay_factor_m4a4 = 88;
const int delay_factor_m4a1s = 87;
const int delay_factor_galil = 90;
const int delay_factor_famas = 88;
const int delay_factor_ump = 90;

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

const int m4a1s_rcs[][2] = {
{1*sensitivity * m4a1s_sense, 5*sensitivity * m4a1s_sense},
{0*sensitivity * m4a1s_sense, 9*sensitivity * m4a1s_sense},
{-13*sensitivity * m4a1s_sense, 17*sensitivity * m4a1s_sense},
{10*sensitivity * m4a1s_sense, 18*sensitivity * m4a1s_sense},
{-13*sensitivity * m4a1s_sense, 23*sensitivity * m4a1s_sense},
{-10*sensitivity * m4a1s_sense, 27*sensitivity * m4a1s_sense},
{19*sensitivity * m4a1s_sense, 15*sensitivity * m4a1s_sense},
{12*sensitivity * m4a1s_sense, 13*sensitivity * m4a1s_sense},
{-10*sensitivity * m4a1s_sense, 11*sensitivity * m4a1s_sense},
{-25*sensitivity * m4a1s_sense, -4*sensitivity * m4a1s_sense},
{-24*sensitivity * m4a1s_sense, 0*sensitivity * m4a1s_sense},
{-25*sensitivity * m4a1s_sense, -6*sensitivity * m4a1s_sense},
{0*sensitivity * m4a1s_sense, 4*sensitivity * m4a1s_sense},
{8*sensitivity * m4a1s_sense, 4*sensitivity * m4a1s_sense},
{-11*sensitivity * m4a1s_sense, 1*sensitivity * m4a1s_sense},
{-13*sensitivity * m4a1s_sense, -2*sensitivity * m4a1s_sense},
{2*sensitivity * m4a1s_sense, 2*sensitivity * m4a1s_sense},
{33*sensitivity * m4a1s_sense, -1*sensitivity * m4a1s_sense},
{10*sensitivity * m4a1s_sense, 6*sensitivity * m4a1s_sense},
{27*sensitivity * m4a1s_sense, 3*sensitivity * m4a1s_sense},
{10*sensitivity * m4a1s_sense, 2*sensitivity * m4a1s_sense},
{11*sensitivity * m4a1s_sense, 0*sensitivity * m4a1s_sense},
{-12*sensitivity * m4a1s_sense, 0*sensitivity * m4a1s_sense},
{6*sensitivity * m4a1s_sense, 5*sensitivity * m4a1s_sense},
{4*sensitivity * m4a1s_sense, 5*sensitivity * m4a1s_sense},
{3*sensitivity * m4a1s_sense, 1*sensitivity * m4a1s_sense},
{4*sensitivity * m4a1s_sense, -1*sensitivity * m4a1s_sense}
};

const int famas_rcs [][2] = {
{-4 * sensitivity * famas_sense, 5 * sensitivity * famas_sense},
{1 * sensitivity  * famas_sense, 4 * sensitivity * famas_sense},
{-6 * sensitivity * famas_sense, 10 * sensitivity * famas_sense},
{-1 * sensitivity * famas_sense, 17 * sensitivity * famas_sense},
{0 * sensitivity * famas_sense, 20 * sensitivity * famas_sense},
{14 * sensitivity * famas_sense, 18 * sensitivity * famas_sense},
{16 * sensitivity * famas_sense, 12 * sensitivity * famas_sense},
{-6 * sensitivity * famas_sense, 12 * sensitivity * famas_sense},
{-20 * sensitivity * famas_sense, 8 * sensitivity * famas_sense},
{-16 * sensitivity * famas_sense, 5 * sensitivity * famas_sense},
{-13 * sensitivity * famas_sense, 2 * sensitivity * famas_sense},
{4 * sensitivity * famas_sense, 5 * sensitivity * famas_sense},
{23 * sensitivity * famas_sense, 4 * sensitivity * famas_sense},
{12 * sensitivity * famas_sense, 6 * sensitivity * famas_sense},
{20 * sensitivity * famas_sense, -3 * sensitivity * famas_sense},
{5 * sensitivity * famas_sense, 0 * sensitivity * famas_sense},
{15 * sensitivity * famas_sense, 0 * sensitivity * famas_sense},
{3 * sensitivity * famas_sense, 5 * sensitivity * famas_sense},
{-4 * sensitivity * famas_sense, 3 * sensitivity * famas_sense},
{-25 * sensitivity * famas_sense, -1 * sensitivity * famas_sense},
{-3 * sensitivity * famas_sense, 2 * sensitivity * famas_sense},
{11 * sensitivity * famas_sense, 0 * sensitivity * famas_sense},
{15 * sensitivity * famas_sense, -7 * sensitivity * famas_sense},
{15 * sensitivity * famas_sense, -10 * sensitivity * famas_sense}
};

const int ump_rcs[][2] = {
{-1 * sensitivity  * ump_sense, 6 * sensitivity * ump_sense},
{-4 * sensitivity  * ump_sense, 8 * sensitivity * ump_sense},
{-2 * sensitivity  * ump_sense, 18 * sensitivity * ump_sense},
{-4 * sensitivity  * ump_sense, 23 * sensitivity * ump_sense},
{-9 * sensitivity  * ump_sense, 23 * sensitivity * ump_sense},
{-3 * sensitivity  * ump_sense, 26 * sensitivity * ump_sense},
{11 * sensitivity  * ump_sense, 17 * sensitivity * ump_sense},
{-4 * sensitivity  * ump_sense, 12 * sensitivity * ump_sense},
{9 * sensitivity  * ump_sense, 13 * sensitivity * ump_sense},
{18 * sensitivity * ump_sense, 8 * sensitivity * ump_sense},
{15 * sensitivity * ump_sense, 5 * sensitivity * ump_sense},
{-1 * sensitivity * ump_sense, 3 * sensitivity * ump_sense},
{5 * sensitivity * ump_sense, 6 * sensitivity * ump_sense},
{0 * sensitivity * ump_sense, 6 * sensitivity * ump_sense},
{9 * sensitivity * ump_sense, -3 * sensitivity * ump_sense},
{5 * sensitivity * ump_sense, -1 * sensitivity * ump_sense},
{-12 * sensitivity * ump_sense, 4 * sensitivity * ump_sense},
{-19 * sensitivity * ump_sense, 1 * sensitivity * ump_sense},
{-1 * sensitivity   * ump_sense, -2 * sensitivity * ump_sense},
{15 * sensitivity * ump_sense, -5 * sensitivity * ump_sense},
{17 * sensitivity * ump_sense, -2 * sensitivity * ump_sense},
{-6 * sensitivity   * ump_sense, 3 * sensitivity * ump_sense},
{-20 * sensitivity  * ump_sense, -2 * sensitivity * ump_sense},
{-3 * sensitivity   * ump_sense, -1 * sensitivity * ump_sense}
};


void setup() {
  Serial.begin(9600);
  Mouse.begin();
  // Wire.begin();
  u8g2.begin();
}

void loop() {

  u8g2.setFont(u8g2_font_logisoso20_tf);
  u8g2.setCursor(0, 50);

  if (Serial.available() > 0) {

  char input = Serial.read();
    if (input == 'x') {
      if (controller >= 6) {
        controller = 0;
      } else {
        controller++; 
      }
      u8g2.clearBuffer();
      switch(controller) {
        case 0: 
          u8g2.clearBuffer();
          break;
        case 1: 
          u8g2.print("ak47"); 
          // u8g2.println(ak_sense);
          break;
        case 2: 
          u8g2.print("m4a4"); 
          break;
        case 3:
          u8g2.print("galil");
          // u8g2.println(gl_sense);
          break;
        case 4:
          u8g2.print("m4a1s");
          // u8g2.println(m4a1s_sense);
          break;
        case 5:
          u8g2.print("famas");
          // u8g2.println(famas_sense);
          break;
        case 6:
          u8g2.print("ump");
          // u8g2.println(ump_sense);
          break;
        }
      u8g2.sendBuffer();

      } else if (input == 'z') {
        controller = 0;
      } else if (input == 'v') {
        switch(controller) {
        case 1: 
          ak_sense = ak_sense + 0.1;
          break;
        case 2: 
          m4_sense = m4_sense + 0.1;
          break;
        case 3:
          gl_sense = gl_sense + 0.1;
          break;
        case 4:
          m4a1s_sense = m4a1s_sense + 0.1;
          break;
        case 5:
          famas_sense = famas_sense + 0.1;
          break;
        case 6:
          ump_sense = ump_sense + 0.1;
          break;
        }
      } else {
        int index = input - '1'; 
        
        if ( controller == 1 && index >= 0 && index < sizeof(ak47_rcs) / sizeof(ak47_rcs[0])) {
          Mouse.move(ak47_rcs[index][0], ak47_rcs[index][1]);
          delay(delay_factor_ak47);
        } else if ( controller == 2 && index >= 0 && index < sizeof(m4a4_rcs) / sizeof(m4a4_rcs[0])) {
          Mouse.move(m4a4_rcs[index][0], m4a4_rcs[index][1]);
          delay(delay_factor_m4a4);
        } else if ( controller == 3 && index >= 0 && index < sizeof(galil_rcs) / sizeof(galil_rcs[0])) {
          Mouse.move(galil_rcs[index][0], galil_rcs[index][1]);
          delay(delay_factor_galil);
        } else if ( controller == 4 && index >= 0 && index < sizeof(m4a1s_rcs) / sizeof(m4a1s_rcs[0])) {
          Mouse.move(m4a1s_rcs[index][0], m4a1s_rcs[index][1]);
          delay(delay_factor_m4a1s);
        } 
        else if ( controller == 5 && index >= 0 && index < sizeof(famas_rcs) / sizeof(famas_rcs[0])) {
          Mouse.move(famas_rcs[index][0], famas_rcs[index][1]);
          delay(delay_factor_famas);
        } else if ( controller == 6 && index >= 0 && index < sizeof(ump_rcs) / sizeof(ump_rcs[0])) {
          Mouse.move(ump_rcs[index][0], ump_rcs[index][1]);
          delay(delay_factor_ump);
        }
      
    } 
  }
}


