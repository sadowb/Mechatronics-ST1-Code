#include "vex.h"
#include <iostream>

using namespace vex;
using signature = vision::signature;
using code = vision::code;
#define MAX_ENCODER_VALUE 250

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors

controller Controller1 = controller(primary);
motor RWheel = motor(PORT17, ratio18_1, false);    /////Right Wheel
motor LWheel = motor(PORT16, ratio18_1, false);    /////Left Wheel
motor SSpinMotor = motor(PORT9, ratio18_1, true);  /////Smol Spinner
motor GSpinMotor = motor(PORT20, ratio18_1, true); /////Grand Spinner
motor CatMotor1 = motor(PORT8, ratio18_1, false);   /////Catapult Motor
motor CatMotor2 = motor(PORT10, ratio18_1, true);   /////Catapult Motor
motor_group CatGroup = motor_group(CatMotor1,CatMotor2);
//vex::encoder CatEncoder(Br);

 void Controls(){ 
    RWheel.spin(forward,Controller1.Axis4.position() -
     Controller1.Axis3.position(), pct);
     LWheel.spin(forward,Controller1.Axis4.position() +
     Controller1.Axis3.position(), pct);

 }

void releaseGrab() {
  GSpinMotor.stop();
  SSpinMotor.stop();
}
void releaseCat() { CatGroup.stop(); }

void Grab() {
  if (Controller1.ButtonB.pressing()) {
    SSpinMotor.spin(fwd, 100, pct);
    GSpinMotor.spin(fwd, 100, pct);
  }
}

void Rev() {
  if (Controller1.ButtonX.pressing()) {
    SSpinMotor.spin(reverse, 100, pct);
    GSpinMotor.spin(reverse, 100, pct);
  }
}



# // replace this with the encoder value for the maximum position

/*void retractCatapult() {
CatGroup.rotateTo(MAX_ENCODER_VALUE, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Encoder Value: %d", CatGroup.position(vex::rotationUnits::rev));
    CatGroup.stop(vex::brakeType::hold);
}*/
void retractCatapult() {
    CatGroup.rotateTo(MAX_ENCODER_VALUE, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
    CatGroup.stop(vex::brakeType::hold);
    CatGroup.setStopping(vex::brakeType::hold);
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Encoder Value: %d", CatGroup.position(vex::rotationUnits::rev));
}

void FindEncoder(){
  //CatGroup.rotateFor(fwd, 30, deg);
  CatGroup.resetRotation();  
CatGroup.setMaxTorque(100, vex::percentUnits::pct);
//CatGroup.resetRotation();
CatGroup.setVelocity(70, pct);
CatGroup.rotateFor(fwd, 250, deg);
//CatGroup.stop(hold);

while(CatGroup.isSpinning()){
int maxPosition = CatGroup.rotation(vex::rotationUnits::deg);
Brain.Screen.print("maxpos : %d", maxPosition );
//CatGroup.resetPosition();
}

}
void Reset(){
  CatGroup.rotateFor(fwd, 370, deg);
}






//void retractCatapult() { double target = 145;
   //while(target>80){ 
            

  //  CatGroup.rotateTo(MAX_ENCODER_VALUE, vex::rotationUnits::deg, 100, vex::velocityUnits::pct);
   

    //CatGroup.stop(vex::brakeType::hold);
     
    //CatGroup.spinFor(fwd,70, deg, 40, rpm);
    //target = target - 10;

   //}
    
    //vex::task::sleep(500);
  
//}
void stopCat(){
  CatGroup.stop();
}

void vexcodeInit(void) {
  // Initialize the VEX system

  //init(vex::controllerType::primary);

  Controller1.ButtonB.released(releaseGrab);
  Controller1.ButtonR1.pressed(releaseCat);
  Controller1.ButtonR2.pressed(stopCat);

  while (1) {
    //Aut();
    //Brain.Screen.print()
    
    
    Controls();

    Grab();
    Rev();
    if(Controller1.ButtonR1.pressing()){
    //FindEncoder();
    FindEncoder();
    //retractCatapult();
    }

    if(Controller1.ButtonR2.pressing()){
      Reset();
    }
   
vex::task::sleep(100);
  }

 

}

////////////



/*#include "vex.h"

using namespace vex;

int main() {
  // Initialize the vex::brain object
  brain Brain;

  // Initialize the vex::motor objects for the two motors
  motor motor1 = motor(PORT1, gearSetting::ratio18_1, false);
  motor motor2 = motor(PORT2, gearSetting::ratio18_1, false);

  // Set the motor speeds to 100%
  motor1.spin(forward, 100, percent);
  motor2.spin(forward, 100, percent);

  // Wait for the motors to rotate to the hard part
  wait(2, seconds);

  // Stop the motors
  motor1.stop();
  motor2.stop();

  // Wait for 1 second
  wait(1, seconds);

  // Reverse the motors to retract the catapult
  motor1.spin(reverse, 100, percent);
  motor2.spin(reverse, 100, percent);

  // Wait for the motors to fully retract
  wait(2, seconds);

  // Stop the motors
  motor1.stop();
  motor2.stop();

  // Wait for 1 second
  wait(1, seconds);

  // End the program
  return 0;
}











///////////

///////
#include "vex.h"

using namespace vex;

// Initialize the motor
motor leftCatapultMotor = motor(PORT1, ratio18_1, false);
motor rightCatapultMotor = motor(PORT2, ratio18_1, false);

// Define the maximum position of the gear to be in the hard part
int maxPosition = 90;

// Function to retract the catapult to the maximum position
void retractCatapult() {
  // Retract the motors to the maximum position
  leftCatapultMotor.rotateFor(maxPosition, rotationUnits::deg, 100, velocityUnits::pct);
  rightCatapultMotor.rotateFor(maxPosition, rotationUnits::deg, 100, velocityUnits::pct);
}

// Function to shoot the catapult
void shootCatapult() {
  // Shoot the motors to the initial position
  leftCatapultMotor.rotateFor(-maxPosition, rotationUnits::deg, 100, velocityUnits::pct);
  rightCatapultMotor.rotateFor(-maxPosition, rotationUnits::deg, 100, velocityUnits::pct);
}

// Main function
int main() {
  // Initialize the controller
  controller controller1 = controller();

  while (true) {
    // Check if the R2 button is pressed
    if (controller1.ButtonR2.pressing()) {
      retractCatapult();
    }

    // Check if another button is pressed
    if (controller1.ButtonX.pressing()) {
      shootCatapult();
    }
  }

  return 0;
}
*/





/////


