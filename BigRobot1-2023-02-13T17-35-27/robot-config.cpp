#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor leftMotorA = motor(PORT20, ratio18_1, false);
motor leftMotorB = motor(PORT10, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT3, ratio18_1, true);
motor rightMotorB = motor(PORT5, ratio18_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 319.19, 295, 40, mm, 1);
controller Controller1 = controller(primary);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

int Piloting() {

  while (true) {

    leftMotorA.spin(forward,
                    (Controller1.Axis3.value() + Controller1.Axis1.value() +Controller1.Axis4.value())*0.5, pct);
    leftMotorB.spin(forward,
                    (-Controller1.Axis3.value() + Controller1.Axis1.value()+Controller1.Axis4.value())*0.5, pct);
    rightMotorA.spin(
        forward, (-Controller1.Axis3.value() - Controller1.Axis1.value() +Controller1.Axis4.value() )*0.5, pct);
    rightMotorB.spin(
        forward, (Controller1.Axis3.value() - Controller1.Axis1.value() + Controller1.Axis4.value())*0.5, pct);

    // if ((Controller1.Axis3.value() + Controller1.Axis4.value()) == 0) {
    //   leftMotorA.spin(reverse, Controller1.Axis1.value(), pct);
    //   leftMotorB.spin(reverse, -Controller1.Axis1.value(), pct);
    //   rightMotorA.spin(reverse, -Controller1.Axis1.value(), pct);
    //   rightMotorB.spin(reverse, Controller1.Axis1.value(), pct);
    // }

    //std::cout << "Axis4: " << Controller1.Axis4.value() << "\n";
    

    

    wait(20, msec);
  }

  /**/
  return 0;
}

void vexcodeInit(void) {
  Piloting();
  // task Piloting(Piloting);
}