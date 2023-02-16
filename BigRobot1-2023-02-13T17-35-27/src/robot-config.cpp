#include "vex.h"

using namespace vex;

// A global instance of brain used for printing to the V5 brain screen
brain Brain;

// VEXcode device constructors

controller Controller1 = controller(primary);
motor FrontRightWheel = motor(PORT17, ratio18_1, false);    /////Right Wheel
motor FrontLefttWheel = motor(PORT17, ratio18_1, false);    /////Right Wheel
motor BackRightWheel = motor(PORT17, ratio18_1, false);    /////Right Wheel
motor BackLeftWheel = motor(PORT17, ratio18_1, false);    /////Right Wheel

motor Spinner = motor(PORT16, ratio18_1, false);    /////Left Wheel
motor SpinMotor1 = motor(PORT11, ratio18_1, false);  /////Right Spinner
motor SpinMotor2 = motor(PORT12, ratio18_1, true); /////Left Spinner
motor_group SpinGroup = motor_group(SpinMotor1, SpinMotor2);

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 *
 * This should be called at the start of your int main function.
 */
void vexcodeInit(void) {

  while(1){
    int LeftX = Controller1.Axis4.position();
    int LeftY = Controller1.Axis3.position();
    int RightX = Controller1.Axis1.position();

    int FrontLeftPower = RightX + LeftX + LeftY;
    int FrontRightPower = LeftY - RightX - LeftX;
    int BackLeftPower = LeftY - RightX + LeftX;
    int BackRightPower = LeftY + RightX -LeftX;

    FrontLefttWheel.spin(fwd,FrontLeftPower, voltageUnits::mV);
    FrontRightWheel.spin(fwd,FrontRightPower, voltageUnits::mV);
    BackLeftWheel.spin(fwd,BackLeftPower, voltageUnits::mV);
    BackRightWheel.spin(fwd,BackRightPower, voltageUnits::mV);

SpinGroup.setMaxTorque(100, pct);
SpinGroup.setVelocity(100,pct);
Spinner.setMaxTorque(100, pct);
Spinner.setVelocity(100,pct);

    while(Controller1.ButtonB.pressing()){
      SpinGroup.spin(fwd);
    }
    while(Controller1.ButtonX.pressing()){
      Spinner.spin(fwd);
    }
  }
  // Nothing to initialize
}

/*
#include "vex.h"

using namespace vex;

// Create a vex controller object
controller con;

// Create motor objects for the mecanum wheels
motor frontLeft = motor(PORT1);
motor frontRight = motor(PORT2);
motor backLeft = motor(PORT3);
motor backRight = motor(PORT4);

int main() {
  // Set the velocity of the mecanum wheels to 50%
  frontLeft.setVelocity(50, percent);
  frontRight.setVelocity(50, percent);
  backLeft.setVelocity(50, percent);
  backRight.setVelocity(50, percent);

  while (true) {
    // Get the value of the left joystick's X axis
    int leftX = con.Axis3.position();

    // Get the value of the left joystick's Y axis
    int leftY = con.Axis4.position();

    // Get the value of the right joystick's X axis
    int rightX = con.Axis1.position();

    // Calculate the power for each motor
    int frontLeftPower = leftY + rightX + leftX;
    int frontRightPower = leftY - rightX - leftX;
    int backLeftPower = leftY - rightX + leftX;
    int backRightPower = leftY + rightX - leftX;

    // Set the power of each motor
    frontLeft.spin(forward, frontLeftPower, voltageUnits::mV);
    frontRight.spin(forward, frontRightPower, voltage



*/