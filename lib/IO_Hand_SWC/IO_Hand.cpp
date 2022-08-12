#include "IO_hand.h"
#include "Park_Pilot.h"
#include <Rte.h>
#include <Servo.h>
#include <Arduino.h>

int t0, t1, t2, sensor;         //var for sensors
int motor_val;          //input for motor direction command
bool outPut1, outPut2;  //output for mototr direction command
int light_buffer, light_read; //reads and store light
int counter = 0;                //counter for the flasher
boolean flasher_on = false;     //flasher flag on/off

Servo servo;


void servoInit() {
    servo.attach(3);
    ServoAngle = servo.read();
}

void readAngle() {
    servo.write(Rte_Call_Servo_MotorSWC_ReadServoAngle());
}

void Definition()
{ // definition of input/outpins & timer counter byte setup
    pinMode(Ena, OUTPUT);
    // pinMode(Rte_Call_DCMotorSWC_ReadStep(), INPUT);
    TCCR1B |= (1 << COM1B1) | (1 << COM1B0) | (1 << WGM10) | (1 << WGM13) | (1 << WGM11);
}

void FlashData()
{
    OCR1B = Rte_Call_DCMotorSWC_ReadStep();
    // flashh data from bus onto hardware
    analogWrite(Ena, OCR1B);
    // OCR0A = Rte_Call_DCMotorSWC_ReadStep();
}

void read_sensors_1() // it is called then will be store in buffer var
{
    MUX_v_updateMux_set1();
    t0 = us0.sw_distance;
    t1 = us1.sw_distance;
    t2 = us2.sw_distance;
}
void read_sensors_2() // it is called then will be store in buffer var
{
    MUX_v_updateMux_set2();
    t0 = us0.sw_distance;
    t1 = us1.sw_distance;
    t2 = us2.sw_distance;
}

void motor_direction() // NEEDS READING FORM RTE
{                      // reads the input command then outputs the driver positions
                       // read from rte command and store it in motor_val

    // switch(Rte_Call_Comm_HandSWC_ReadDirFlag()){
    //     case 1:
    //         digitalWrite(outPut1, LOW);
    //         digitalWrite(outPut2, HIGH);
    //         break;

    //     case 2:
    //         digitalWrite(outPut1, HIGH);
    //         digitalWrite(outPut2, LOW);
    //         Serial.println("cas2");
    //     break;
    //     case 3:
    //         digitalWrite(outPut1, HIGH);
    //         digitalWrite(outPut2, HIGH);
    //     break;
    // }
    if (1 == Rte_Call_Comm_HandSWC_ReadDriveInput())
    {
        digitalWrite(outPut1, LOW);
        digitalWrite(outPut2, HIGH);
    }
    else if (2 == Rte_Call_Comm_HandSWC_ReadDriveInput())
    {
        digitalWrite(outPut1, HIGH);
        digitalWrite(outPut2, LOW);
    }
    else if (3 == Rte_Call_Comm_HandSWC_ReadDriveInput())
    {
        digitalWrite(outPut1, HIGH);
        digitalWrite(outPut2, HIGH);
    }
}

void store_light() // NEEDS READING FORM RTE & TIMER
{                  // reads and stores light reading in buffer
    // read from rte light level
    light_buffer = light_read;
}

void flasher_mode_selector(){
    if(Rte_Call_Servo_MotorSWC_ReadServoAngle() < 85){
        Rte_Call_Flasher_SWC_WriteFlasherData(1);
    } else if(Rte_Call_Servo_MotorSWC_ReadServoAngle() > 95){
        Rte_Call_Flasher_SWC_WriteFlasherData(2);
    } else {
        Rte_Call_Flasher_SWC_WriteFlasherData(0);
    }

    if((1 == Rte_Call_ParkPilotSWC_ReadEmergencyFlag()) && (0 == Rte_Call_Comm_HandSWC_ReadDriveMode())){
        Rte_Call_Flasher_SWC_WriteFlasherData(3);
    }
}

void flasher(){

    if (0 == Rte_Call_Flasher_SWC_ReadFlasherData()) {  //off
        analogWrite(left_flasher, OFF); analogWrite(right_flasher, OFF);
        counter = 0;
        flasher_on = false;
    } else {
        counter++;

        if(!flasher_on){
            analogWrite(left_flasher, OFF); analogWrite(right_flasher, OFF);
        }

        if((3 == Rte_Call_Flasher_SWC_ReadFlasherData()) && (1 == flasher_on)){         //avari
            analogWrite(left_flasher, ON);  analogWrite(right_flasher, ON);
        } else if((1 == Rte_Call_Flasher_SWC_ReadFlasherData()) && (1 == flasher_on)){  //left
            analogWrite(left_flasher, ON);  analogWrite(right_flasher, OFF);
        } else if((2 == Rte_Call_Flasher_SWC_ReadFlasherData()) && (1 == flasher_on)){  //right
            analogWrite(left_flasher, OFF); analogWrite(right_flasher, ON);
        }

        if((counter > on_cycle_flasher) && (1 == flasher_on)){
            counter = 0;    flasher_on = false;
        }    

        if((counter > off_cycle_flasher) && (!flasher_on)){
            counter = 0;    flasher_on = true;
        }
    }
}

void low_beam_mode_selector(){

    int T_LIGHT_LEVEL_THRESHOLD = analogRead(A6);//A6 is the receiver port from the sensor

    if(2 == Rte_Call_Low_Beam_SWC_ReadLightData()){         // auto
        if(T_LIGHT_LEVEL_THRESHOLD < light_sensor_margin){
            analogWrite(low_beam_light, OFF); 
        } else { 
            analogWrite(low_beam_light, ON); 
        }
    } else if(1 == Rte_Call_Low_Beam_SWC_ReadLightData()){  // on
        analogWrite(low_beam_light, ON);
    } else {                                                //off
        analogWrite(low_beam_light, OFF);
    }
}
