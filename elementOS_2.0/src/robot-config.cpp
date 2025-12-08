#include "elementOS_2.0.h"

using namespace vex;

brain Brain;
controller Controller = controller(primary);

motor LF = motor(PORT3 , ratio6_1 , true);
motor LM = motor(PORT2, ratio6_1 , false);
motor LB = motor(PORT1 , ratio6_1 , true);
motor RF = motor(PORT17 , ratio6_1 , false);
motor RM = motor(PORT20 , ratio6_1 , true);
motor RB = motor(PORT19 , ratio6_1 , false);

motor Intake = motor(PORT5 , ratio6_1 , true);
motor Channel = motor(PORT18 , ratio6_1 , true);

motor ArmL = motor(PORT4 , ratio18_1 , true);
motor ArmR = motor(PORT7 , ratio18_1 , false);

rotation EncoderL = rotation(PORT9 , true);
rotation EncoderR = rotation(PORT10 , true);

inertial Inertial = inertial(PORT8);

vex::distance ChannelDistance = vex::distance(PORT6);

digital_out ArmPiston = digital_out(Brain.ThreeWirePort.A);
digital_out PTO = digital_out(Brain.ThreeWirePort.C);
digital_out HookPiston = digital_out(Brain.ThreeWirePort.B);
digital_out BB7 = digital_out(Brain.ThreeWirePort.D);