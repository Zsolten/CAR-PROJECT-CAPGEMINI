#include <Rte.h>
#include <stdint.h>

unsigned short int Step_u;
bool driveMode_b;
unsigned short int DriveInput_u;
unsigned short int  DirFlag_u;
bool DirFlagREV_b;
bool EmergencyFlag_b;
bool HandBrake_b;
unsigned short int DutyCycle_i;
unsigned short int SendDCY_i;

uint16_t ServoAngle;
uint16_t leftSteering;
uint16_t rightSteering;

uint16_t LightMode, FlasherMode;

unsigned int AnalogData_i;
bool dirChange_b;
