/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Anas                                             */
/*    Created:      Mon Jan 23 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// PneumaticA           led           A               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void printencoder(void);
void clearencoder(void);

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  led PneumaticA = led(Brain.ThreeWirePort.A);

     while(true){
     
     
       if(Controller1.ButtonA.pressing()){

            PneumaticA.on();
            Brain.Screen.print(" pneumatic A extend Mode ");
            Brain.Screen.newLine();
       }
     else if(Controller1.ButtonB.pressing()){
       PneumaticA.off();
       Brain.Screen.print(" pneumatic A retract Mode ");
        Brain.Screen.newLine();
     }
    
   }
}
