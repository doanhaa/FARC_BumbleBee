
/* /////////////////////////////////////////////////////////////////////////////
//  CHƯƠNG TRÌNH ĐIỀU KHIỂN ROBOT BUMBLEBEE FARC 2025
//  Date: 19/7/2025
//  Modified and further developed by Doan Ha from the organizers' original 
    robot program: https://github.com/makerviet/via-k12maker/blob/release-2025/firmwares/example-ps2/makerbot-2025-ps2-motor-test/makerbot-2025-ps2-motor-test.ino
*/ ////////////////////////////////////////////////////////////////////////////
#include "motors.h"
#include "PS2_controller.h"

void setup()
{
  Serial.begin(115200);
  initMotors();
  setupPS2controller();
  Serial.println("Done setup!");
}

void loop()
{
  ps2x.read_gamepad(0, 0);
  Servo_Control();
  LinearSlide_Control();
  LinearSlideGripper_Control();
  Gripper_Control();
  Disable_Servo();
  PS2control();
  delay(50);
}
