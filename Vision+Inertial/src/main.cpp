/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\milad                                            */
/*    Created:      Wed Feb 01 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Drivetrain           drivetrain    3, 4, 1         
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
}

////////Autonomous
#include "vex.h"

vex::brain Brain;
vex::controller Controller1 = vex::controller();
vex::motor RightWheel = vex::motor(PORT1);
vex::motor LeftWheel = vex::motor(PORT2);
vex::vision VisionSensor = vex::vision(PORT3);
vex::inertial InertialSensor = vex::inertial(PORT4);




int main() {
  setup();
  while(1) {
    loop();
  }
  return 0;
}



////////////
