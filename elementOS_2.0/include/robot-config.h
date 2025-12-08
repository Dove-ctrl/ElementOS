#pragma once
using namespace vex;

extern brain Brain;
extern controller Controller;

extern motor LF;
extern motor RF;
extern motor LB;
extern motor RB;
extern motor LM;
extern motor RM;

extern motor Intake;
extern motor Channel;

extern motor ArmL;
extern motor ArmR;

extern rotation EncoderL;
extern rotation EncoderR;

extern inertial Inertial;

extern vex::distance ChannelDistance;

extern digital_out ArmPiston;
extern digital_out PTO;
extern digital_out HookPiston;
extern digital_out BB7;