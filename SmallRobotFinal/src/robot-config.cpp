#include "vex.h"
#include <iostream>

using namespace vex;
using signature = vision::signature;
using code = vision::code;
#define MAX_ENCODER_VALUE 250

brain Brain;

controller Controller1 = controller(primary);
motor RWheel = motor(PORT20, ratio18_1, false); /////Right Wheel
motor LWheel = motor(PORT18, ratio18_1, false); /////Left Wheel
// motor SSpinMotor = motor(PORT9, ratio18_1, true);  /////Smol Spinner
motor GSpinMotor = motor(PORT17, ratio18_1, true); /////Grand Spinner
motor CatMotor1 = motor(PORT13, ratio18_1, true);  /////Catapult Motor 2
motor CatMotor2 = motor(PORT16, ratio18_1, false); /////Catapult Motor
motor_group CatGroup = motor_group(CatMotor1, CatMotor2);

motor expa1 = motor(PORT14, ratio18_1, true);  /////Catapult Motor 2
motor expa2 = motor(PORT15, ratio18_1, false); /////Catapult Motor
motor_group expaGroup = motor_group(expa1, expa2);
// vex::encoder CatEncoder(Br);
limit CatLimit = limit(Brain.ThreeWirePort.A);
void Ex1() { expa1.stop(); }

void Ex2() { expa2.stop(); }

void ExpansionSystem() {
  expaGroup.resetRotation();

  expaGroup.stop();

  if (Controller1.ButtonR2.pressing() && Controller1.ButtonL2.pressing()) {

    expaGroup.stop();

    expaGroup.setMaxTorque(100, pct);
    expaGroup.setVelocity(100, pct);
    expaGroup.rotateFor(fwd, 90, deg);
  }
  // expaGroup.stop(brake);
}

void Controls() {

  RWheel.spin(forward,
              Controller1.Axis4.position() - Controller1.Axis3.position(), pct);
  LWheel.spin(forward,
              Controller1.Axis4.position() + Controller1.Axis3.position(), pct);
}

void releaseGrab() { GSpinMotor.stop(); }
void releaseCat() { CatGroup.stop(); }

void Grab() {
  if (Controller1.ButtonB.pressing()) {
    GSpinMotor.spin(fwd, 100, pct);
  }
}

void retractCatapult() {
  int target = 160;
  CatGroup.resetRotation();
  CatGroup.rotateTo(MAX_ENCODER_VALUE, vex::rotationUnits::deg, target,
                    vex::velocityUnits::pct);
  CatGroup.stop(vex::brakeType::hold);

  if (CatGroup.isSpinning()) {
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Encoder Value: %d : ", CatGroup.position(deg));
  }
}

void stopCat() { CatGroup.stop(); }

void testCat() {
  int target = 150;
  while (Controller1.ButtonR2.pressing()) {
    if (target <= 150)
      CatGroup.rotateFor(fwd, 100, deg);

    target = target + 10;
  }
}

void FindEncoder() {
  CatGroup.resetPosition();
  CatGroup.spin(forward, 5, percent);

  wait(2, seconds);
  CatGroup.stop(hold);

  while (CatGroup.isSpinning()) {
    int maxPosition = CatGroup.position(deg);
    Brain.Screen.print("maxpos : %d", maxPosition);
  }
}
void Reset() {
  Brain.Screen.clearScreen();

  CatGroup.rotateFor(fwd, 370, deg);
  if (CatGroup.isDone()) {
    Brain.Screen.setCursor(1, 2);
    Brain.Screen.print("Deg : %f", CatGroup.position(deg));
  }
}

void CatShooterStop() {
  Brain.Screen.print("this is Catshooterstop");
  CatGroup.spinFor(0.5, rev, 100, rpm, true);
  //CatGroup.stop(hold);
  //CatGroup.setVelocity(0, pct);
  //CatGroup.setMaxTorque(0, pct);
}
void CatShooter() {
  Brain.Screen.clearScreen();
  CatGroup.setMaxTorque(100, pct);
  CatGroup.setVelocity(100, pct);
  Brain.Screen.print("outside");

  if (Controller1.ButtonX.pressing()) { // int flag = 500;

    if (!CatLimit.pressing()) {
      Brain.Screen.print("1st else");
      CatGroup.spin(fwd, 10, pct);

    } else if (CatLimit.pressing()) {
      Brain.Screen.print("2nd else");
      CatGroup.stop(hold);
      // wait(5,msec);
    }

    // else if (Controller1.ButtonA.pressing() && CatLimit.pressing()) {
    // spinFor( double rotation, rotationUnits units, double velocity,
    // velocityUnits units_v, bool waitForCompletion=true );

    // CatGroup.spinFor( 1.5 , rev ,100 ,rpm, true);
    //}

    // CatGroup.spin(fwd,10,pct);

    // CatGroup.resetRotation();
  }
}

/*void RetractCatapult() {
   // Retrieve the motor object

   // Set the target position in degrees
   int targetPosition = 500;

   if (Controller1.ButtonY.pressing()){

   // Rotate the motor to the target position
   CatGroup.rotateTo(targetPosition, rotationUnits::deg);

    //Stop the motor once it reaches the target position
   CatGroup.stop(brakeType::brake);
   }
}
*/

void releaseCatFullSpeed() {
  CatGroup.setMaxTorque(100, pct);
  CatGroup.setVelocity(100, pct);
  CatGroup.rotateTo(10000, rotationUnits::deg);
}

void vexcodeInit(void) {

  Controller1.ButtonB.released(releaseGrab);
  Controller1.ButtonR1.pressed(releaseCat);
  Controller1.ButtonR2.released(stopCat);
  Controller1.ButtonX.released(CatShooterStop);
  // Controller1.ButtonY.released(releaseCatFullSpeed);

  while (1) {
    // expaGroup.stop(hold);

    vex::thread ControlsThread(Controls);
    thread Grabthread(Grab);
    thread Rev(Grab);
    thread ExpansionSystemThread(ExpansionSystem);
    thread CatShooterThread(CatShooter);
    // thread RetractCatapultThread(RetractCatapult);
    // thread testThread(test);

    if (Controller1.ButtonR1.pressing()) {
      thread FindEncoderThread(FindEncoder);
    }

    if (Controller1.ButtonR2.pressing()) {
      thread Resetthread(Reset);
    }

    vex::task::sleep(50);
  }
}

/////
