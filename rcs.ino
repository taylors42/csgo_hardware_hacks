#include <hidboot.h>
#include <Mouse.h>
#include <U8g2lib.h>
#include <Wire.h>

#define OLED_ADDRESS 0x3C

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
int controller = 0;
const float baseSensitivity = 1.0f;
float ak47Sensitivity = baseSensitivity * 1.20f;
float m4a4Sensitivity = baseSensitivity * 1.10f;
float galilSensitivity = baseSensitivity * 1.30f;
float m4a1sSensitivity = baseSensitivity * 0.95f;
float famasSensitivity = baseSensitivity;
float umpSensitivity = baseSensitivity;

const int delayFactors[] = {
    90, // ak47
    88, // m4a4
    90, // galil
    87, // m4a1s
    88, // famas
    90  // ump
};

const std::pair<int, int> recoilCompensationPatterns[][30] = {
    // ... recoil patterns for each weapon ...
};

const int numPatterns[] = {
    sizeof(recoilCompensationPatterns[0]) / sizeof(recoilCompensationPatterns[0][0]),
    // ... number of patterns for each weapon ...
};

void setup() {
    Serial.begin(9600);
    Mouse.begin();
    Wire.begin();
    u8g2.begin();
}

void loop() {

    u8g2.setFont(u8g2_font_logisoso20_tf);
    u8g2.setCursor(0, 50);

    if (Serial.available() > 0) {

        char input = Serial.read();

        switch (input) {
            case 'x':
                controller = (controller + 1) % sizeof(recoilCompensationPatterns) / sizeof(recoilCompensationPatterns[0]);
                break;
            case 'z':
                controller = 0;
                break;
            case 'v':
                if (controller > 0 && controller <= sizeof(recoilCompensationPatterns) / sizeof(recoilCompensationPatterns[0])) {
                    switch (controller) {
                        case 1:
                            ak47Sensitivity += 0.1f;
                            break;
                        case 2:
                            m4a4Sensitivity += 0.1f;
                            break;
                        case 3:
                            galilSensitivity += 0.1f;
                            break;
                        case 4:
                            m4a1sSensitivity += 0.1f;
                            break;
                        case 5:
                            famasSensitivity += 0.1f;
                            break;
                        case 6:
                            umpSensitivity += 0.1f;
                            break;
                    }
                }
                break;
            default:
                int index = input -
