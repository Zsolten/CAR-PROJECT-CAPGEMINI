#include <Arduino.h>
#include "Rte.h"


// #define dirDriv 7
// #define reverse 4
// #define ena 5 //pwm
#define MANMODE 0
#define AUTOMODE 1
#define FWD 2 //10
#define REV 1 //01
#define STOP 3 //11

void DrivState();
void Forward();
void Reverse();
void Stop();
int Accelerate();
int Decelerate();
int ForcedDec();
void SetValDutyCycle();