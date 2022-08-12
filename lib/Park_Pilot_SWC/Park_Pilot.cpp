#include "Park_Pilot.h"
#include "IO_Hand.h"
#include <Arduino.h>
#include "Rte.h"

long int sl_duration = 0; // stores the pulse duration
int distance;
int t0, t1, t2;                                                       // var for sensors
int buff_t0_1, buff_t1_1, buff_t2_1, buff_t0_2, buff_t1_2, buff_t2_2; // buffers for sensors
int threshold = 20;
int counter_interations = 0;
bool direction;
bool flag_dist = false;
bool flag_toggle = true;
bool flag_step1 = true;
bool flag_step2 = false;
bool flag_step3 = false;
bool flag_step4 = false;
bool flag_step5 = false;

void auto_parking()
{
  if (Rte_Call_Comm_HandSWC_ReadDriveMode() == 0)
  {
    // buffers for the first reading
    MUX_v_updateMux_set1();
    buff_t1_1 = t1;
    buff_t2_1 = t2;
    MUX_v_updateMux_set2();
    buff_t1_2 = t1;
    buff_t2_2 = t2;

    stepOne();

    if (direction == 0)
    {
      void park_left();
    }
    else if (direction == 1)
    {
      void park_right();
    }
    // check values for succesfull termination
  }
}

void stepOne()
{
  if (flag_step1 == true)
  {
    Rte_Call_Comm_HandSWC_WriteDirFlag(2);
    Rte_Call_DCMotorSWC_WriteStep(50);
    MUX_v_updateMux_set1();
    if (t2 <= 15)
    {
      Rte_Call_Comm_HandSWC_WriteDirFlag(3);
      flag_step1 = false;
      flag_step2 = true;
      direction = 1;
    }

    MUX_v_updateMux_set2();
    if (t1 <= 15)
    {
      Rte_Call_Comm_HandSWC_WriteDirFlag(3);
      flag_step1 = false;
      flag_step2 = true;
      direction = 0;
    }
  }
}

int parking_direction()
{
  if (buff_t2_1 < buff_t1_2) // do we have a car on the left?
  {
    return 2; // park to the left
  }
  else
  {
    return 1; // park to the right
  }
}

void park_left()
{
  if (flag_step2 == true)
  {
    Rte_Call_Servo_MotorSWC_WriteServoAngle(65); // step 2
    Rte_Call_Comm_HandSWC_WriteDirFlag(1);

    if (flag_toggle == true)
    {
      Rte_Call_ParkPilotSWC_WriteDutyCycle(50);
    }

    MUX_v_updateMux_set2();
    if (t0 < 25)
    {
      Rte_Call_Comm_HandSWC_WriteDirFlag(3);
      flag_toggle == false;
      flag_step2 = false;
      flag_step3 = true;
    }
  }

  //////////////////////////////////////////////////////////////////
  if (flag_step3 == true)
  {
    Rte_Call_Servo_MotorSWC_WriteServoAngle(93); // step 3
    Rte_Call_Comm_HandSWC_WriteDirFlag(1);

    if (flag_toggle == true)
    {
      Rte_Call_ParkPilotSWC_WriteDutyCycle(50);
    }

    MUX_v_updateMux_set2();
    if (t0 < 15)
    {
      Rte_Call_Comm_HandSWC_WriteDirFlag(3);
      flag_toggle == false;
      flag_step3 = false;
      flag_step4 = true;
    }
  }
  /////////////////////////////////////////////////////////////////
  if (flag_step4 == true)
  {
    Rte_Call_Servo_MotorSWC_WriteServoAngle(122); // step 4
    Rte_Call_Comm_HandSWC_WriteDirFlag(1);

    if (flag_toggle == true)
    {
      Rte_Call_ParkPilotSWC_WriteDutyCycle(50);
    }

    MUX_v_updateMux_set2();
    if (t0 < 15 || t1 < 15 || t2 < 15)
    {
      Rte_Call_Comm_HandSWC_WriteDirFlag(3);
      flag_toggle == false;
      flag_step4 = false;
      flag_step5 = true;
    }
  }
  //////////////////////////////////////////////////////////////
  if (flag_step5 == true)
  {
    Rte_Call_Servo_MotorSWC_WriteServoAngle(93); // step 5
    Rte_Call_Comm_HandSWC_WriteDirFlag(2);
    if (flag_toggle == true)
    {
      Rte_Call_ParkPilotSWC_WriteDutyCycle(50);
    }

    MUX_v_updateMux_set1();
    if (t0 < 15)
    {
      Rte_Call_Comm_HandSWC_WriteDirFlag(3);
      flag_toggle == false;
    }
  }
}
void park_right()
{
  if (flag_step2 == true)
  {
    Rte_Call_Servo_MotorSWC_WriteServoAngle(122); // step 2
    Rte_Call_Comm_HandSWC_WriteDirFlag(1);

    if (flag_toggle == true)
    {
      Rte_Call_ParkPilotSWC_WriteDutyCycle(50);
    }

    MUX_v_updateMux_set2();
    if (t0 < 25)
    {
      Rte_Call_Comm_HandSWC_WriteDirFlag(3);
      flag_toggle == false;
      flag_step2 = false;
      flag_step3 = true;
    }
  }

  //////////////////////////////////////////////////////////////////
  if (flag_step3 == true)
  {
    Rte_Call_Servo_MotorSWC_WriteServoAngle(93); // step 3
    Rte_Call_Comm_HandSWC_WriteDirFlag(1);

    if (flag_toggle == true)
    {
      Rte_Call_ParkPilotSWC_WriteDutyCycle(50);
    }

    MUX_v_updateMux_set2();
    if (t0 < 15)
    {
      Rte_Call_Comm_HandSWC_WriteDirFlag(3);
      flag_toggle == false;
      flag_step3 = false;
      flag_step4 = true;
    }
  }
  /////////////////////////////////////////////////////////////////
  if (flag_step4 == true)
  {
    Rte_Call_Servo_MotorSWC_WriteServoAngle(65); // step 4
    Rte_Call_Comm_HandSWC_WriteDirFlag(1);

    if (flag_toggle == true)
    {
      Rte_Call_ParkPilotSWC_WriteDutyCycle(50);
    }

    MUX_v_updateMux_set2();
    if (t0 < 15)
    {
      Rte_Call_Comm_HandSWC_WriteDirFlag(3);
      flag_toggle == false;
      flag_step4 = false;
      flag_step5 = true;
    }
  }
  //////////////////////////////////////////////////////////////
  if (flag_step5 == true)
  {
    Rte_Call_Servo_MotorSWC_WriteServoAngle(93); // step 5
    Rte_Call_Comm_HandSWC_WriteDirFlag(2);
    if (flag_toggle == true)
    {
      Rte_Call_ParkPilotSWC_WriteDutyCycle(50);
    }

    MUX_v_updateMux_set1();
    if (t0 < 15)
    {
      Rte_Call_Comm_HandSWC_WriteDirFlag(3);
      flag_toggle == false;
    }
  }
}

void transfer()
{
  // transfer data from a variable to another on the bus
  Rte_Call_ParkPilotSWC_WriteDutyCycle(Rte_Call_IOHandSWC_ReadAnalogData());
}

void MUX_v_updateMux_set1()
{
  /*Call function for sending trigger on A0 for FC sensor*/
  MUX_v_setTrig(A0);
  /*Set the adress on MUX for opening channel C15*/
  MUX_v_setAdress(ON_S, ON_S, ON_S, ON_S);
  /*Calculate the duration of the regitered pulse*/
  sl_duration = pulseIn(2, HIGH, 0);
  /*Calculate the distance of the object by multiplying distance with speed of sound and divide by the number of trips the signal made*/
  distance = (sl_duration * SOUND_SPEED) / ROAD_NUMBER;
  if (distance < 10)
  {
    Rte_Call_ParkPilotSWC_WriteEmergencyFlag(1);
  }

  Rte_Call_ParkPilotSWC_WriteSWdistance(distance);
  t0 = Rte_Call_ParkPilotSWC_ReadSWdistance();

  /*print to serial the distance*/
  //      Serial.println(sw_distance);

  /*Call function for sending trigger on A1 for FL sensor*/
  MUX_v_setTrig(A1);
  /*Set the adress on MUX for opening channel C14*/
  MUX_v_setAdress(OFF_S, ON_S, ON_S, ON_S);
  /*Calculate the duration of the regitered pulse*/
  sl_duration = pulseIn(2, HIGH, 0);
  /*Calculate the distance of the object by multiplying distance with speed of sound and divide by the number of trips the signal made*/
  distance = (sl_duration * SOUND_SPEED) / ROAD_NUMBER;
  if (distance < 10)
  {
    Rte_Call_ParkPilotSWC_WriteEmergencyFlag(1);
  }
  Rte_Call_ParkPilotSWC_WriteSWdistance(distance);
  t1 = Rte_Call_ParkPilotSWC_ReadSWdistance();
  /*print to serial the distance*/
  //     Serial.println(sw_distance);

  /*Call function for sending trigger on A2 for FR sensor*/
  MUX_v_setTrig(A4);
  /*Set the adress on MUX for opening channel C13*/
  MUX_v_setAdress(ON_S, OFF_S, ON_S, ON_S);
  /*Calculate the duration of the regitered pulse*/
  sl_duration = pulseIn(2, HIGH, 0);
  /*Calculate the distance of the object by multiplying distance with speed of sound and divide by the number of trips the signal made*/
  distance = (sl_duration * SOUND_SPEED) / ROAD_NUMBER;
  if (distance < 10)
  {
    Rte_Call_ParkPilotSWC_WriteEmergencyFlag(1);
  }
  Rte_Call_ParkPilotSWC_WriteSWdistance(distance);
  t2 = Rte_Call_ParkPilotSWC_ReadSWdistance();
  /*print to serial the distance*/
  //     Serial.println(sw_distance);
}
void MUX_v_updateMux_set2()
{
  /*Call function for sending trigger on A30 for RC sensor*/
  MUX_v_setTrig(A3);
  /*Set the adress on MUX for opening channel C12*/
  MUX_v_setAdress(OFF_S, OFF_S, ON_S, ON_S);
  /*Calculate the duration of the regitered pulse*/
  sl_duration = pulseIn(2, HIGH, 0);
  /*Calculate the distance of the object by multiplying distance with speed of sound and divide by the number of trips the signal made*/
  distance = (sl_duration * SOUND_SPEED) / ROAD_NUMBER;
  if (distance < 10)
  {
    Rte_Call_ParkPilotSWC_WriteEmergencyFlag(1);
  }
  Rte_Call_ParkPilotSWC_WriteSWdistance(distance);
  t0 = Rte_Call_ParkPilotSWC_ReadSWdistance();
  /*print to serial the distance*/
  //      Serial.println(sw_distance);

  /*Call function for sending trigger on A4 for RL sensor*/
  MUX_v_setTrig(A5);
  /*Set the adress on MUX for opening channel C11*/
  MUX_v_setAdress(ON_S, ON_S, OFF_S, ON_S);
  /*Calculate the duration of the regitered pulse*/
  sl_duration = pulseIn(2, HIGH, 0);
  /*Calculate the distance of the object by multiplying distance with speed of sound and divide by the number of trips the signal made*/
  distance = (sl_duration * SOUND_SPEED) / ROAD_NUMBER;
  if (distance < 10)
  {
    Rte_Call_ParkPilotSWC_WriteEmergencyFlag(1);
  }
  Rte_Call_ParkPilotSWC_WriteSWdistance(distance);
  t1 = Rte_Call_ParkPilotSWC_ReadSWdistance();
  /*print to serial the distance*/
  //     Serial.println(sw_distance);

  /*Call function for sending trigger on A5 for RR sensor*/
  MUX_v_setTrig(A2);
  /*Set the adress on MUX for opening channel C10*/
  MUX_v_setAdress(OFF_S, ON_S, OFF_S, ON_S);
  /*Calculate the duration of the regitered pulse*/
  sl_duration = pulseIn(2, HIGH, 0);
  /*Calculate the distance of the object by multiplying distance with speed of sound and divide by the number of trips the signal made*/
  distance = (sl_duration * SOUND_SPEED) / ROAD_NUMBER;
  if (distance < 10)
  {
    Rte_Call_ParkPilotSWC_WriteEmergencyFlag(1);
  }
  Rte_Call_ParkPilotSWC_WriteSWdistance(distance);
  t2 = Rte_Call_ParkPilotSWC_ReadSWdistance();
  /*print to serial the distance*/
  //    Serial.println(sw_distance);
}

void MUX_v_setAdress(int ui_s0, int ui_s1, int ui_s2, int ui_s3)
{
  if (ui_s0 == 1)
  {
    digitalWrite(8, HIGH);
  }
  else
  {
    digitalWrite(8, LOW);
  }

  if (ui_s1 == 1)
  {
    digitalWrite(9, HIGH);
  }
  else
  {
    digitalWrite(9, LOW);
  }

  if (ui_s2 == 1)
  {
    digitalWrite(10, HIGH);
  }
  else
  {
    digitalWrite(10, LOW);
  }

  digitalWrite(11, LOW);
}

void MUX_v_setTrig(int sw_trigPin)
{
  digitalWrite(sw_trigPin, LOW); // nu transmite

  delayMicroseconds(2);

  digitalWrite(sw_trigPin, HIGH); // transmite pentru 20ms

  delayMicroseconds(20);

  digitalWrite(sw_trigPin, LOW); // incheie transmisia
}
