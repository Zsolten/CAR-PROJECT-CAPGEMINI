

#include <Arduino.h>
#include "Rte.h"
#define Ena 5
#define low_beam_light 13 //D13
#define on_cycle_flasher 16
#define off_cycle_flasher 21
#define left_flasher 6
#define right_flasher 12
#define ON 255
#define OFF 0
#define light_sensor_margin 350
#define outPut1 7
#define outPut2 4


void servoInit();
void readAngle();




void Definition();
void readPinData();
void FlashData();
void read_sensors_1();
void read_sensors_2();
void motor_direction();
int out_sensors();
void store_light();

void flasher_mode_selector();
void flasher();
void low_beam_mode_selector();

struct senzori{
  int sw_distance = 0; 
};

extern struct senzori us0, us1, us2;
