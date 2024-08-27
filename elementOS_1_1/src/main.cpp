#include "elementOS.h"
#include "mainOS.h"

using namespace vex;

competition Competition;

void pre_auton(void) {
  eos::SystemInitialize(&Brain , &Controller);
  vex::thread start_eos(eos::ELEMENTOS);
}

void autonomous(void) {
  
}

void usercontrol(void) {
  
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while (true) {
    wait(100, msec);
  }
}
