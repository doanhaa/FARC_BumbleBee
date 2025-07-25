#include <stdio.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define MIN_PWM 0
#define MAX_PWM 4095

// PWM channels of pca9685 0-16
#define PWM_CHANNEL1 8
#define PWM_CHANNEL2 9
#define PWM_CHANNEL3 10
#define PWM_CHANNEL4 11
#define PWM_CHANNEL5 12
#define PWM_CHANNEL6 13
#define PWM_CHANNEL7 14
#define PWM_CHANNEL8 15


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

void setServo(uint8_t channel, uint16_t pulse){
  pwm.setPWM(channel, 0, pulse);
}
void setPWMMotors(int c1, int c2, int c3, int c4)
{
  char dbg_str[30];
  sprintf(dbg_str,"C1: %d\tC2: %d\tC3: %d\tC4: %d",c1,c2,c3,c4);
  Serial.println(dbg_str);

  pwm.setPin(PWM_CHANNEL1, c1);
  pwm.setPin(PWM_CHANNEL2, c2);
  pwm.setPin(PWM_CHANNEL3, c3);
  pwm.setPin(PWM_CHANNEL4, c4);
}

void setPWMLinear_Slide(int c1, int c2){
  pwm.setPin(PWM_CHANNEL5, c1);
  pwm.setPin(PWM_CHANNEL6, c2);
}

void setPWMLinear_Slide_Gripper(int c1, int c2){
  pwm.setPin(PWM_CHANNEL7, c1);
  pwm.setPin(PWM_CHANNEL8, c2);
}

void setPWMLinear_and_Motors(int c1, int c2, int c3, int c4, int c5, int c6){
  pwm.setPin(PWM_CHANNEL1, c1);
  pwm.setPin(PWM_CHANNEL2, c2);
  pwm.setPin(PWM_CHANNEL3, c3);
  pwm.setPin(PWM_CHANNEL4, c4);
  pwm.setPin(PWM_CHANNEL5, c5);
  pwm.setPin(PWM_CHANNEL6, c6);
}
void initMotors()
{
  Wire.begin(); // SDA, SCL,400000);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);
  setPWMMotors(0, 0, 0, 0);
  setPWMLinear_Slide(0,0);
}
