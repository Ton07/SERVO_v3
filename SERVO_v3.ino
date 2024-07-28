#include <Servo.h>
#include <SoftwareSerial.h>

#define SERVO_PIN_1 9
#define SERVO_PIN_2 10 

#define FSR_PIN_1 A0
#define FSR_PIN_2 A1

Servo servo1;
Servo servo2; 

bool isPressed1 = false;
bool isPressed2 = false;

int mode = 1;

void setup() {
  Serial.begin(9600);
  servo1.attach(SERVO_PIN_1);
  servo2.attach(SERVO_PIN_2); 
  servo1.write(0);  // Set servo1 to 0 degrees
  servo2.write(0);  // Set servo2 to 0 degrees
  pinMode(FSR_PIN_1, INPUT);
  pinMode(FSR_PIN_2, INPUT);
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read(); 
  }

  int fsrValue1 = analogRead(FSR_PIN_1);
  if (fsrValue1 < 500) {
    isPressed1 = true;
  } else {
    isPressed1 = false;
  }

  int fsrValue2 = analogRead(FSR_PIN_2);
  if (fsrValue2 < 500) {
    isPressed2 = true;
  } else {
    isPressed2 = false;
  }

  if (mode == 1) {
    if (!isPressed1 && !isPressed2) {
      if (servo1.read() <= 270)  {
        servo1.write(servo1.read() + 1);
        delay(1); // Adjusted delay for even faster speed
      } 
      else {
        servo1.write(1);
      }
      if (servo2.read() < 270) {
        servo2.write(servo2.read() + 1);
      } else {
        servo2.write(0);
      }
    } else {
      servo1.write(servo1.read());
      servo2.write(servo2.read());
    }
  } else if (mode == 0) {
    if (servo1.read() > 0) {
      servo1.write(servo1.read() - 1);
    }
    if (servo2.read() > 0) {
      servo2.write(servo2.read() - 1);
    }
  }

  Serial.print("FSR1 Value: ");
  Serial.print(fsrValue1);
  Serial.print(" | FSR2 Value: ");
  Serial.print(fsrValue2);
  Serial.print(" | Servo1 Angle: ");
  Serial.print(servo1.read());
  Serial.print(" | Servo2 Angle: ");
  Serial.print(servo2.read());
  Serial.print(" | Mode: ");
  Serial.println(mode);

  if (Serial.available()) {
    char c = Serial.read();
    if (c == '1') {
      mode = 1;
    } else if (c == '0') {
      mode = 0;
    }
  }
}
