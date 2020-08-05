#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32_BT.h>

#include "ESP32_ISR_Servo.h"

#define MIN_MICROS      500
#define MAX_MICROS      2500

int servoIndex1  = -1;
int servoIndex2  = -1;

int servo_1_pin  = 12;
int servo_2_pin  = 14;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YOUR1TOKEN";

BLYNK_WRITE(V1) {
    int x = param[0].asInt();
    int y = param[1].asInt();

    ESP32_ISR_Servos.setPulseWidth(servoIndex2, (x * 2) + 1244);
}

BLYNK_WRITE(V2) {
    int x = param[0].asInt();
    int y = param[1].asInt();

    ESP32_ISR_Servos.setPulseWidth(servoIndex1, ((255 - y) * 6) + 500);
}

void setup(){
    Serial.begin(115200);
    Serial.print("Setup begin");
    delay(10);

    ESP32_ISR_Servos.useTimer(USE_ESP32_TIMER_NO);

    servoIndex1 = ESP32_ISR_Servos.setupServo(servo_1_pin, MIN_MICROS, MAX_MICROS);
    servoIndex2 = ESP32_ISR_Servos.setupServo(servo_2_pin, MIN_MICROS, MAX_MICROS);

    ESP32_ISR_Servos.setPulseWidth(servoIndex1, 1500);
    ESP32_ISR_Servos.setPulseWidth(servoIndex2, 1500);


    if (servoIndex1 != -1)
      Serial.println("Setup Servo1 OK");
    else
      Serial.println("Setup Servo1 failed");

    if (servoIndex2 != -1)
      Serial.println("Setup Servo2 OK");
    else
      Serial.println("Setup Servo2 failed");

    Serial.print("start login");

    Blynk.setDeviceName("Blynk");
    Blynk.begin(auth);

    Serial.print("login done");
}


void loop() {
    Blynk.run();
}

