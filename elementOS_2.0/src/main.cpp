#include "elementOS_2.0.h"

using namespace vex;

competition Competition;

void autonomous(void) {
  waitUntil(eos::READY);
  AutoRoute();
}

void usercontrol(void) {
  waitUntil(eos::READY);
  if(eos::AUTODEBUG){
    AutoRoute();
  }else{
    while(true){
      wait(100, msec);
    }
  }
}

int main() {

  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  eos::SystemInitialize(&Brain , &Controller , &Competition);
  thread eos_main(EosMain);
  waitUntil(eos::READY);

  while (true) {
    wait(100, msec);
  }
  
}
