#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;


///////////////*Vision


/*vex-vision-config:end*/

// VEXcode generated functions
///******************



///*******************



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
//void vexcodeInit( void ) {
  // nothing to initialize
//}
///////////////*Vison

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor LeftDriveSmart = motor(PORT17, ratio18_1, false);
motor RightDriveSmart = motor(PORT16, ratio18_1, true);
motor_group RL = motor_group(LeftDriveSmart, RightDriveSmart);
inertial DrivetrainInertial = inertial(PORT1);
motor LSpinner = motor(PORT15); 
motor GSpinner = motor(PORT14); 
motor_group LGSpinner = motor_group(LSpinner, GSpinner);


smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, DrivetrainInertial, 319.19, 320, 40, mm, 1);
signature Vision10__SIG_1 = signature (1, 3247, 3787, 3517, -4489, -4153, -4321, 2.7, 0);
signature Vision10__SIG_2 = signature (2, 3121, 3773, 3447, -4569, -4035, -4302, 4.9, 0);
signature Vision10__SIG_3 = signature (3, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision10__SIG_4 = signature (4, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision10__SIG_5 = signature (5, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision10__SIG_6 = signature (6, 0, 0, 0, 0, 0, 0, 3, 0);
signature Vision10__SIG_7 = signature (7, 0, 0, 0, 0, 0, 0, 3, 0);
vision Vision10 = vision (PORT15, 50,Vision10__SIG_1, Vision10__SIG_2, Vision10__SIG_3, Vision10__SIG_4, Vision10__SIG_5, Vision10__SIG_6, Vision10__SIG_7);
code Vision10__Y = code (255,255,0);
//smartdrive Drivetrain = smartdrive(vex::motor &l, vex::motor &r, vex::guido &g)

// VEXcode generated functions

void redCallBack(){
  Brain.Screen.clearLine();
  Vision10.takeSnapshot(Vision10__SIG_2);
  if(Vision10.objectCount>0){
    Brain.Screen.print(" Object Found");
    Brain.Screen.newLine();
        Brain.Screen.print(  Vision10.takeSnapshot(Vision10__SIG_2));

    
  }
  else{
    Brain.Screen.print("No  Object Found");
    Brain.Screen.newLine();
    }
}
void Aut1() {
  //Drive forward until yellow disk is detected
  RightDriveSmart.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
  LeftDriveSmart.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);

  if(Vision10.takeSnapshot(Vision10__SIG_2)) {
    //Stop wheels
    RightDriveSmart.stop();
    LeftDriveSmart.stop();
    
    //Get the x-coordinate of the yellow disk
    
        Vision10.objects[0].centerX;

    //int x = Vision10.objects[0].centerX;

    /*
    //If the disk is on the right side of the frame, turn right
    if(x > Vision10.cameraConfig().width/2) {

      RightDriveSmart.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
      LeftDriveSmart.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
      vex::task::sleep(200);
    }
    //If the disk is on the left side of the frame, turn left
    else {
      RightDriveSmart.spin(vex::directionType::rev, 50, vex::velocityUnits::pct);
      LeftDriveSmart.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
      vex::task::sleep(200);
    }*/
    
    //Drive towards the disk
    RightDriveSmart.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
    LeftDriveSmart.spin(vex::directionType::fwd, 50, vex::velocityUnits::pct);
    vex::task::sleep(200);
    
    LGSpinner.spin(fwd,100,pct);




    
  }
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
    while(true){
    Aut1();
    redCallBack();
    wait(1,seconds);
     }
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain Inertial
  wait(200, msec);
  DrivetrainInertial.calibrate();
  Brain.Screen.print("Calibrating Inertial for Drivetrain");
  //while(1) {
    //Drivetrain.set
    //Drivetrain.turnToHeading( 90 , degrees );

    Drivetrain.turnFor( 90, degrees );
  
   // double x = DrivetrainInertial.gyroRate(xaxis, )
    //gyrorate(xaxis,degrees);
    
    //Brain.screen.print(inertial.gyrorate);
    
    //Drivetrain.turnToRotation( 500, degrees );
    
    //break;
    
    vex::task::sleep(100);
  //}
  // wait for the Inertial calibration process to finish
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
  
  

}