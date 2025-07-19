#include <PS2X_lib.h>

PS2X ps2x; // create PS2 Controller Class object
#define BEBUG_CTRL

// calibration for different kinds of PS2 controller, this value only suitable for the PS2 controller comes with VRC2023 K12 Maker kit 
#define X_JOY_CALIB 127
#define Y_JOY_CALIB 128

#define PS2_DAT 12 // MOSI  19
#define PS2_CMD 13 // MISO  23
#define PS2_SEL 15 // SS     5
#define PS2_CLK 14 // SLK   18

#define TOP_SPEED 4095
#define NORM_SPEED 2048
#define SERVO_POS_100_DEGREES 274 // Giá trị xung cho góc 100 độ
#define SERVO_POS_180_DEGREES 410 // Giá trị xung cho góc 180 độ
#define SERVO_1_CHANNEL 2
#define SERVO_2_CHANNEL 3
#define TURNING_FACTOR 1

#define SINGLE_HAND_DRIVING 0
#define TWO_HAND_DRIVING 1
bool driving_mode = SINGLE_HAND_DRIVING;
void setupPS2controller()
{
  int err = -1;
  while (err != 0)
  {
    err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  }

}

void Servo_Control(){
   if(ps2x.Button(PSB_L1)){
    setServo(SERVO_1_CHANNEL, SERVO_POS_100_DEGREES);
  }
  else if(ps2x.Button(PSB_L2)){
    setServo(SERVO_2_CHANNEL, SERVO_POS_180_DEGREES);
  }
}

void LinearSlide_Control(){
  if(ps2x.Button(PSB_GREEN)){
    setPWMLinear_Slide(TOP_SPEED, 0);
  }
  else if(ps2x.Button(PSB_BLUE)){
    setPWMLinear_Slide(0, TOP_SPEED);
  }
  else{
    setPWMLinear_Slide(0,0);
  }
}

bool PS2control()
{
  int speed = NORM_SPEED;
  Servo_Control();
  LinearSlide_Control();
  if (ps2x.Button(PSB_R2))
    speed = TOP_SPEED;
   if (ps2x.ButtonPressed(PSB_SELECT))
    driving_mode =! driving_mode;

  int nJoyX = X_JOY_CALIB - ps2x.Analog(PSS_RX); // read x-joystick
  int nJoyY = Y_JOY_CALIB - (driving_mode ? ps2x.Analog(PSS_LY) :ps2x.Analog(PSS_RY)); // read y-joystick
  int nMotMixL;                          // Motor (left) mixed output
  int nMotMixR;                          // Motor (right) mixed output

  if(nJoyX == -1 && nJoyY == 0) // in case of lost connection with the wireless controller, only used in VRC2023 PS2 wireless controller 
  {
    setPWMMotors(0, 0, 0, 0);
    return 0;
  }

  bool temp = (nJoyY * nJoyX > 0);
  if (nJoyX) // Turning
  {
    nMotMixL = -nJoyX + (nJoyY * temp);
    nMotMixR = nJoyX + (nJoyY * !temp);
  }
  else // Forward or Reverse
  {
    nMotMixL = nJoyY;
    nMotMixR = nJoyY;
  }
  #ifdef BEBUG_CTRL
  Serial.print(F("Calculated value from joystick: "));
  Serial.print(nMotMixL);
  Serial.print("\t");
  Serial.println(nMotMixR);
  #endif
  int c1 = 0, c2 = 0, c3 = 0, c4 = 0;

  if (nMotMixR > 0)
  {
    c3 = nMotMixR;
    c3 = map(c3, 0, 128, 0, speed);
  }

  else if (nMotMixR < 0)
  {
    c4 = abs(nMotMixR) + 1;
    c4 = map(c4, 0, 128, 0, speed);
  }

  if (nMotMixL > 0)
  {
    c1 = nMotMixL;
    c1 = map(c1, 0, 128, 0, speed);
  }
  else if (nMotMixL < 0)
  {
    c2 = abs(nMotMixL);
    c2 = map(c2, 0, 128, 0, speed);
  }
  setPWMMotors(c1, c2, c3, c4);
  return 1;
}
