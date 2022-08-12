/**
  * when a task is defined, its order in the scheduler 
  * should correspond to the order of its specific calling period in the array
*/
#include <TaskScheduler.h>
#include <Comm_Hand.h>
#include <DC_Motor.h>
#include <Flasher.h>
#include <IO_Hand.h>
#include <Light_Sensor.h>
#include <Low_Beam.h>
#include <Park_Pilot.h>
#include <Servo_Motor.h>
#include <Rte.h>

#define PERIOD 20 
#define PERIOD1 20
#define PERIOD2 500
#define PERIOD3 20
#define PERIOD4 20
#define PERIOD5 20
#define PERIOD6 50
#define PERIOD7 300
#define PERIOD6 30

Scheduler ts;
void taskFunctions20ms();
void HoldOneSec(int per);
void prototype();

int hold_time = 0;
bool flip = true;//activates or deactivates a task
unsigned short pos = 0;// current position of an exeuted task in the array
int const maxVal = 5;//how many periods there are
int periods[maxVal] = {PERIOD4,PERIOD,PERIOD1,PERIOD3,PERIOD5};//array containing task execution periods
int sum = 0;//current period sum 
int rem = 0;//reminder untill base time 
int const tim = 1000;//base time 

Task tCommHand(PERIOD4 * TASK_MILLISECOND, TASK_FOREVER, &commHand, &ts, true);
Task tBlink1(PERIOD *TASK_MILLISECOND,TASK_FOREVER, &taskFunctions20ms, &ts ,true);
Task tCallDrive(PERIOD * TASK_MILLISECOND, TASK_FOREVER, &DrivState, &ts, flip);
Task tPrototype(PERIOD1 * TASK_MILLISECOND, TASK_FOREVER, &prototype, &ts, true);
Task tBlink2(PERIOD3 * TASK_MILLISECOND, TASK_FOREVER, &readAngle, &ts, true);
Task tSwitch(PERIOD5 * TASK_MILLISECOND, TASK_FOREVER, &motor_direction, &ts, true);
Task tAuto(PERIOD6 *TASK_MILLISECOND, TASK_FOREVER, &auto_parking, &ts, true);


void setup() {
  // put your setup code here, to run once:
  Definition();
  servoInit();
  flasherInit();
  Serial.begin(115200);
   
}

void loop() {
  // put your main code here, to run repeatedly:
  ++pos;
  ts.execute();
  HoldOneSec(periods[pos]);

  //reset position values in array after the last task 
  if(pos>=maxVal)
 {
  pos = 0;
 }
 
}

void prototype()
{
  //first we read data from IO 
  //readPinData();
  //send it to parkpilot 
  //transfer();
  //send duty cycle for processing to DC_Motor_SWC
  //SetValDutyCycle();
  //send processed data to IO for flashing 
  FlashData();
} 

void taskFunctions20ms()
{

  driveMode();
  readAngle();
  //check if flasher is needed to be on/off
  flasher_mode_selector();
  flasher();
  //check if low beam needed to be on/off
  low_beam_mode_selector();
}

void HoldOneSec(int per)
{
  int period = per;
  if (true == Rte_Call_DCMotorSWC_ReadDirChange())
  {
    if (rem >= 0)
    {
      flip = false;
      sum += period;
      rem = tim - sum;
    }
    else
    {
      flip = true;
      Rte_Call_DCMotorSWC_WriteDirChange(false);
      rem = 0;
      sum = 0;
        
    }
  }
 
}




