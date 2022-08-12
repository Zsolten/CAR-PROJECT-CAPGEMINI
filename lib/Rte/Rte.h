
#ifndef Rte_h_
#define Rte_h_
#include <stdint.h>

/* Global variable declaration */
extern unsigned short int Step_u;
extern bool driveMode_b;
extern unsigned short int DriveInput_u;
extern unsigned short int DirFlag_u;
extern bool EmergencyFlag_b;
extern bool HandBrake_b ; 
extern bool ParkDirect_b;
extern unsigned short int DutyCycle_i;
extern unsigned short int SendDCY_i;
extern uint16_t ServoAngle;
extern uint16_t leftSteering;
extern uint16_t rightSteering;
extern unsigned int AnalogData_i;
extern uint16_t LightMode, FlasherMode;
extern bool dirChange_b;

#define Rte_Call_DCMotorSWC_ReadStep() Step_u
#define Rte_Call_DCMotorSWC_WriteStep(STP) Step_u = STP
#define Rte_Call_Comm_HandSWC_ReadDriveMode() driveMode_b
#define Rte_Call_Comm_HandSWC_WriteDriveMode(DVM) driveMode_b = DVM 
#define Rte_Call_Comm_HandSWC_ReadDriveInput() DriveInput_u
#define Rte_Call_Comm_HandSWC_WriteDriveInput(DI) DriveInput_u = DI
#define Rte_Call_Comm_HandSWC_ReadDirFlag() DirFlag_u
#define Rte_Call_Comm_HandSWC_WriteDirFlag(DIF) DirFlag_u = DIF 
#define Rte_Call_ParkPilotSWC_ReadEmergencyFlag() EmergencyFlag_b
#define Rte_Call_ParkPilotSWC_WriteEmergencyFlag(EFL) EmergencyFlag_b = EFL
#define Rte_Call_DCMotorSWC_ReadHandBrake() HandBrake_b
#define Rte_Call_DCMotorSWC_WriteHandBrake(HBK) HandBrake_b = HBK
#define Rte_Call_ParkPilotSWC_ReadDutyCycle() DutyCycle_i
#define Rte_Call_ParkPilotSWC_WriteDutyCycle(DCY) DutyCycle_i = DCY
#define Rte_Call_DCMotorSWC_ReadSendDCY() SendDCY_i
#define Rte_Call_DCMotorSWC_WriteSendDCY(DC) SendDCY_i = DC
#define Rte_Call_Servo_MotorSWC_ReadServoAngle() ServoAngle
#define Rte_Call_Servo_MotorSWC_WriteServoAngle(SA) ServoAngle = SA
#define Rte_Call_Comm_HandSWC_ReadLeftSteering() leftSteering
#define Rte_Call_Comm_HandSWC_WriteLeftSteering(LS) leftSteering = LS
#define Rte_Call_Comm_HandSWC_ReadRightSteering() rightSteering
#define Rte_Call_Comm_HandSWC_WriteRightSteering(RS) rightSteering = RS
#define Rte_Call_IOHandSWC_ReadAnalogData() AnalogData_i
#define Rte_Call_IOHandSWC_WriteAnalogData(AD) AnalogData_i = AD
#define Rte_Call_DCMotorSWC_ReadDirChange() dirChange_b
#define Rte_Call_DCMotorSWC_WriteDirChange(DIC) dirChange_b = DIC
#define Rte_Call_Low_Beam_SWC_ReadLightData() LightMode
#define Rte_Call_Low_Beam_SWC_WriteLightData(arg) LightMode = arg  // 0-off, 1-on, 2-auto
#define Rte_Call_Flasher_SWC_ReadFlasherData() FlasherMode
#define Rte_Call_Flasher_SWC_WriteFlasherData(arg) FlasherMode = arg // 0-off, 1-left, 2-right, 3-avari


#endif 