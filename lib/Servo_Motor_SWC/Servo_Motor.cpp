/**
 * @page Servo_Motor
 * **Author:** Belean Marian - Daniel
 * 
 * **Date:** 20.07.2022
 * ## Module's Role
 * This module controls the angle of the servo motor.
 * 
 */
#include <Servo.h>
#include <Servo_Motor.h>
#include <Rte.h>
#include <Arduino.h>
/**
 * Servo Motor SWC
 * 
 * It works in two ways: auto and manual mode.
 * 
 * if we are in manual mode, we can control the angle of the servo,
 * through the buttons in the web interface
 * 
 * @param[in] Rte_Call_Comm_HandSWC_ReadLeftSteering
 * @param[in] Rte_Call_Comm_HandSWC_ReadRightSteering
 * @param[in] Rte_Call_Comm_HandSWC_ReadServoAngle
 * @param[in] Rte_Call_Comm_HandSWC_WriteLeftSteering
 * @param[in] Rte_Call_Comm_HandSWC_WriteRightSteering
 * @param[in] Rte_Call_Comm_HandSWC_
 */
uint16_t step = 0;
struct
{
  uint16_t lastSteering;
} req1, req2;

enum mode
{
  manualMode,
  autoMode
};

void driveMode()
{
  if (manualMode == Rte_Call_Comm_HandSWC_ReadDriveMode())
  {
    manualControl();
  }
  else if (autoMode == Rte_Call_Comm_HandSWC_ReadDriveMode())
  {
    automaticControl();
  }
}

void turn_servo_left()
{
  req2.lastSteering = LOW; 
  if (Rte_Call_Comm_HandSWC_ReadLeftSteering() != req1.lastSteering && Rte_Call_Comm_HandSWC_ReadRightSteering() != rightRequest)
  {
    if (Rte_Call_Comm_HandSWC_ReadLeftSteering() && ServoAngle < servo_max)
    {
      ServoAngle += ++step;
      Rte_Call_Servo_MotorSWC_WriteServoAngle(ServoAngle);
    }
  }
  if (req1.lastSteering == HIGH && Rte_Call_Comm_HandSWC_ReadRightSteering() != rightRequest)
  {
    ServoAngle += ++step * 2;
    if (ServoAngle > servo_max)
    {
      ServoAngle = servo_max;
      step = 0;
    }
    Rte_Call_Servo_MotorSWC_WriteServoAngle(ServoAngle);
  }
  req1.lastSteering = Rte_Call_Comm_HandSWC_ReadLeftSteering();
}

void turn_servo_right()
{
  req1.lastSteering = LOW;
  if (Rte_Call_Comm_HandSWC_ReadRightSteering() != req2.lastSteering && Rte_Call_Comm_HandSWC_ReadLeftSteering() != leftRequest)
  {

    if (ServoAngle > servo_min)
    {
      ServoAngle -= ++step;
      Rte_Call_Servo_MotorSWC_WriteServoAngle(ServoAngle);
    }
  }
  if (req2.lastSteering == HIGH && Rte_Call_Comm_HandSWC_ReadLeftSteering() != leftRequest)
  {
    ServoAngle -= ++step * 2;
    if (ServoAngle < servo_min)
    {
      ServoAngle = servo_min;
      step = 0;
    }
    Rte_Call_Servo_MotorSWC_WriteServoAngle(ServoAngle);
  }

  req2.lastSteering = Rte_Call_Comm_HandSWC_ReadRightSteering();
}

void manualControl()
{
  if (leftRequest == Rte_Call_Comm_HandSWC_ReadLeftSteering())
  {
    turn_servo_left();
  }
  if (rightRequest == Rte_Call_Comm_HandSWC_ReadRightSteering())
  {
    turn_servo_right();
  }
  if(leftRequest != Rte_Call_Comm_HandSWC_ReadLeftSteering() && rightRequest != Rte_Call_Comm_HandSWC_ReadRightSteering())
  {
    Rte_Call_Servo_MotorSWC_WriteServoAngle(default_pos);
  }
}

void automaticControl()
{
}