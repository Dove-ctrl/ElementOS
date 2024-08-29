#include "vex.h"
#include "elementOS.h"
#include "opfunction.h"

using namespace vex;

competition Competition;

void autonomous(void) {
  waitUntil(INITIALIZE_DONE);
  switch (PROGRAMFLAG)
  {

  case 1://tournament
    tournament_route(&Competition);
    break;
  case 2://skill
    skill_route(&Competition);
    break;
  default:
    break;

  }
}

void usercontrol(void) {
  waitUntil(INITIALIZE_DONE);
  switch (PROGRAMFLAG)
  {
  case 1://tournament
    Brain.Screen.printAt(100,100,"tournament");
    break;
  case 2://skill
    Brain.Screen.printAt(100,100,"skill");
    break;
  case 3://driver_debug
    Brain.Screen.printAt(100,100,"driver_debug");
    vex::thread(op_move , &Competition);
    break;
  case 4://auto_skill_debug
    Brain.Screen.printAt(100,100,"auto_skill_debug");
    skill_route(&Competition);
    break;
  case 9://auto_tournament_debug
    Brain.Screen.printAt(100,100,"auto_tournament_debug");
    tournament_route(&Competition);
  break;
  case 8://check
    
    break;
  default:
    break;
  }
}

int main() {
  chassis::GetInstance();
  thread chassis(chassis_drive_thread);

  eos::SystemInitialize(&Brain , &Controller);
  thread main_elementOS(elementOS , &Competition);
  
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  while (true) {
    wait(100, msec);
  }
}