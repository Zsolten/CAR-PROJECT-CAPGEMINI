/**
 * This software component handles requests and state changes that influence the propper functioning 
 * and control of the on-board DCmotor.
 * Its directions of rotation are influenced by the switching of outputs on the "H-bridge"
 *    - for example switching: output1(on-board) --> 1 and output2(on-board) --> 0 
 *      will result in a FORWARDS motion and vice-versa for REVERSE.
 *    - also, switching both outputs on will result in the stopping of motor's rotor.
 * The SW has a very plain architecture: 
 *        main function{
 *                      call functions
 *                      }  
 *        functions
 * The main function will always be the one called by a task and the sepparate functions will be called 
 * according to a secific algorithm within the main function. 
 * Main function aka:"DrivState" checks first if there is a state of emergency active, in which it is not
 * allowed to action the motor or it is forced to stop immediately. 
 * Then DrivState checks what mode is it operating in : "AUTO/MANUAL"
 *     - if manual mode is active, then will change boolean values according to the desired direction 
 *       of movement and if no other canges occure in next itterations, it will start incrementing 
 *       an integer value that will later be passed as duty cycle for the I/O Handler SWC through a 
 *       virtual bus variable.
 *     - if there is a change of direction request, the "prev" flag changes values 
 *       and inside the source file the task responsable for calling the main function inside 
 *       DC_Motor SWC will be deactivated for a second.
 *     - if no action is sent to this SWC it will decrement the duty cycle of the motor until it comes to a stop.
 *     - auto mode will just receive commands from the ParkPilot SWC, as opposed to the manual mode where all 
 *       commands come from the Comm_Handler SWC, setting the duty cycle according to ParkPilot's algorithm.
*/

#include "DC_Motor.h"
#include <Arduino.h>

int i = 0;//increments the necessary duty cycle
bool f = false;//direction flag forward
bool r = false;//direction flag reverse
bool prev = false; //previous state change 
int step1 = 0 ;

void DrivState()
{
  if(1 == Rte_Call_ParkPilotSWC_ReadEmergencyFlag())
  {
    Stop();
  }
  if( (MANMODE == Rte_Call_Comm_HandSWC_ReadDriveMode()) && (0 == Rte_Call_ParkPilotSWC_ReadEmergencyFlag()))
  {
    //enters manual mode 
    if (FWD == Rte_Call_Comm_HandSWC_ReadDriveInput())
    {
      //set local state flag according to the direction of movement
      f = true;
      prev = false;

      if (r == true )
      {
        f = true;
        r = false;
        prev = true;
      }
      if (i == 0)
      {
        Forward();
      }
      Accelerate();
      
    }

    if (REV == Rte_Call_Comm_HandSWC_ReadDriveInput())
    {
      //set local state flag according to the direction of movement
      r = true;
      prev = false;
      Rte_Call_DCMotorSWC_WriteDirChange(prev);

      if (f == true)
      {
        r = true;
        f = false;
        prev = true;
        Rte_Call_DCMotorSWC_WriteDirChange(prev);
      }
      if (i == 0)
      {
        Reverse();
      }
      Accelerate();
    }
    if (0 == Rte_Call_Comm_HandSWC_ReadDriveInput())
    {
      Decelerate();
    }
  }

  if( (AUTOMODE == Rte_Call_Comm_HandSWC_ReadDriveMode()) && (0 == Rte_Call_ParkPilotSWC_ReadEmergencyFlag()))
  {
    //enters auto mode 
    if (FWD == Rte_Call_Comm_HandSWC_ReadDriveInput())
    {
      //set local state flag according to the direction of movement
      f = true;
      prev = false;
      Rte_Call_DCMotorSWC_WriteDirChange(prev);

      if (r == true )
      {
        f = true;
        r = false;
        prev = true;
        Rte_Call_DCMotorSWC_WriteDirChange(prev);
        Stop();
      }
      
      if (i == 0)
      {
        Forward();
      }
      SetValDutyCycle();
    }

    if (REV == Rte_Call_Comm_HandSWC_ReadDriveInput())
    {
      //set local state flag according to the direction of movement
      r = true;
      prev = false;
      Rte_Call_DCMotorSWC_WriteDirChange(prev);

      if (f == true )
      {
        r = true;
        f = false;
        
        prev = true;
        Rte_Call_DCMotorSWC_WriteDirChange(prev);
        
        Stop();
      }
      if (i == 0)
      {
        Reverse();
      }
      SetValDutyCycle();
    }
    
  }

}



int Accelerate()
{
  //when a certan direction is requested we increase speed
  if (i <= 255)
  {
    if(prev == false)//if previous action is the same as actual, increease speed by a factor of two 
    
      i += ++step1*2;
    
    else//if there was a change in states speed will increase normally

      i += ++step1;
    if(i > 254)
    {
      i = 255;
      step1 = 0;
    }
  }
  return Rte_Call_DCMotorSWC_WriteStep(i);
}  

int Decelerate()
{
  //when nop_ speed decreases by a factor of 4

  if ((i >= 0) && (i <= 255))
  {

    i -= ++step1*4;
    if (i <= 0)
    {
      i = 1;
      step1 = 0;
    }

  }
  return Rte_Call_DCMotorSWC_WriteStep(i);//write the increment value on the bus
}

void Forward()
{
  //when this function is called it switches the flag values so that I/O can change the 
  //output gates accordingly

  Rte_Call_Comm_HandSWC_WriteDirFlag(FWD);

}

void Reverse()
{
  //idem to the Forward function but the other way aroud

  Rte_Call_Comm_HandSWC_WriteDirFlag(REV);

}

void Stop()
{
  //when called it shorts out the motor pins, stopping it

  Rte_Call_Comm_HandSWC_WriteDirFlag(STOP);
  i = 0;
}

void SetValDutyCycle()
{
  //change 1024 to 100 after testing
  //maps out the values of the variable received from Parkpilot
  //sends data on the bus for IO SWC
 Rte_Call_DCMotorSWC_WriteSendDCY(map(Rte_Call_ParkPilotSWC_ReadDutyCycle(),0,100,0,255)); 
}

