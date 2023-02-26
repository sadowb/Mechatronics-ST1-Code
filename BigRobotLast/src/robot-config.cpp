#include "vex.h"

using namespace vex;

brain Brain;


controller Controller1 = controller(primary);
//motor FrontRightWheel = motor(PORT3, ratio18_1, false);    /////Right Wheel
//motor FrontLefttWheel = motor(PORT5, ratio18_1, false);    /////Right Wheel
//motor BackRightWheel = motor(PORT20, ratio18_1, true);    /////Right Wheel
//motor BackLeftWheel = motor(PORT10, ratio18_1, true);    /////Right Wheel

motor leftTopMotor = motor(PORT14, ratio18_1, false);
motor leftBottomMotor = motor(PORT12, ratio18_1, false);
motor rightTopMotor = motor(PORT15, ratio18_1, true);
motor rightBottomMotor = motor(PORT13, ratio18_1, true);


motor Mot1 = motor(PORT2, ratio18_1, false);    /////Right Wheel
motor Mot2 = motor(PORT17, ratio18_1, false);    /////Right Wheel





motor Spinner1 = motor(PORT16, ratio18_1, false); 
motor Spinner2 = motor(PORT2, ratio18_1, false);
motor_group SpinGroup = motor_group(Spinner1, Spinner2);   /////Left Wheel
motor SpinMotor1 = motor(PORT11, ratio18_1, false);  /////Right Spinner
motor SpinMotor2 = motor(PORT12, ratio18_1, true); /////Left Spinner
//motor_group SpinGroup = motor_group(SpinMotor1, SpinMotor2);


void StopMot1(){
 //Mot1.setReversed(true);
 Mot1.rotateFor(fwd, -67, deg); 

 }

void RotateMot(){
  int flag = 0 ;
  Mot1.resetPosition();
  Mot1.setVelocity(30, pct );
  Mot1.setMaxTorque(30, pct);
  if(Controller1.ButtonA.pressing()){
    Mot1.setReversed(false);
    Mot1.rotateFor(fwd, 30, deg);
    //flag = 1;

  }
  //else if (Controller1.ButtonA.released(StopMot1) && flag ==1 ){
    
      //Mot1.setReversed(true);

      //Mot1.rotateFor(fwd, 30, deg);

    //  flag = 0;

  //}
  //else 
//Mot1.stop(hold);
    
}




void RotateMotRev(){
  Mot1.rotateFor(fwd, 50, deg);
}

void StopMot(){
  Mot1.rotateFor(fwd,-50,deg);
  Mot1.setStopping(hold);
}
void StopGroupSpinner(){
  SpinGroup.stop();
}
void StopSpinner(){
  SpinGroup.stop(hold);

}

void Shooter(){
  while(Controller1.ButtonL1.pressing()){

      SpinGroup.spin(fwd);
      SpinGroup.setVelocity(100, pct);
       //vex::this_thread::sleep_for(50);


    }
   
}
void Controls(){
  //BackRightWheel.spin(forward,
      //              (Controller1.Axis3.value() - Controller1.Axis1.value() +Controller1.Axis4.value()), pct);
    //BackLeftWheel.spin(forward,
        //            (-Controller1.Axis3.value() - Controller1.Axis1.value()+Controller1.Axis4.value()), pct);
    //FrontRightWheel.spin(
      //  forward, (-Controller1.Axis3.value() + Controller1.Axis1.value() +Controller1.Axis4.value() ), pct);
    //FrontLefttWheel.spin(
      //  forward, (Controller1.Axis3.value() + Controller1.Axis1.value() + Controller1.Axis4.value()), pct);
       rightTopMotor.spin(vex::directionType::fwd, 
                   -Controller1.Axis3.position() - Controller1.Axis1.position() + Controller1.Axis4.position(), 
                   vex::velocityUnits::pct);
rightBottomMotor.spin(vex::directionType::fwd, 
                      Controller1.Axis3.position() - Controller1.Axis1.position() + Controller1.Axis4.position(), 
                      vex::velocityUnits::pct);
leftBottomMotor.spin(vex::directionType::fwd, 
                     Controller1.Axis3.position() + Controller1.Axis1.position() + Controller1.Axis4.position(), 
                     vex::velocityUnits::pct);
leftTopMotor.spin(vex::directionType::fwd, 
                  Controller1.Axis3.position() + Controller1.Axis1.position() + Controller1.Axis4.position(), 
                  vex::velocityUnits::pct);


}
void SpinMotFWD(){
  while(Controller1.ButtonR1.pressing()){
      SpinGroup.spin(fwd);
      SpinGroup.setVelocity(100, pct);

    }

}


void vexcodeInit(void) {
  leftTopMotor.setVelocity(100, pct );
  leftBottomMotor.setVelocity(100, pct );
  rightBottomMotor.setVelocity(100, pct );
  rightTopMotor.setVelocity(100, pct );

  SpinGroup.setVelocity(100,pct);

//Controller1.ButtonA.released(StopMot1);
//Controller1.ButtonL1.released(StopGroupSpinner);
//Controller1.ButtonR1.released(StopSpinner);
Controller1.ButtonA.released(StopMot1);
Controller1.ButtonL1.released(StopGroupSpinner);
Controller1.ButtonR1.released(StopSpinner);

  while(1){
  
vex::thread RotateMotThread(RotateMot);
vex::thread ControlsThread(Controls);
vex::thread ShooterThread(Shooter);
vex:: thread SpinnerThread(SpinMotFWD);

  if(Controller1.ButtonY.pressing()){
      thread RotateMotRevThread(RotateMotRev);
    }

    

SpinGroup.setMaxTorque(100, pct);
SpinGroup.setVelocity(100,pct);
SpinGroup.setMaxTorque(100, pct);
SpinGroup.setVelocity(100,pct);

    
    
  }
  vex::this_thread::sleep_for(50);
}


/*
#include "vex.h"

using namespace vex;

brain Brain;

controller Controller1 = controller(primary);
motor Mot1 = motor(PORT2, ratio18_1, false);

void rotateMot1() {
  Mot1.rotateTo(30, degrees);
  Mot1.stop(hold);
}

void stopMot1() {
  Mot1.stop(hold);
}

void vexcodeInit(void) {
  Controller1.ButtonA.pressed(rotateMot1);
  Controller1.ButtonA.released(stopMot1);
}


*/

