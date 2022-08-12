#ifndef PARK_PILOT_H
#define PARK_PILOT_H
#include "Rte.h"

void transfer();

#include <Arduino.h>

#define ON_S 1
#define OFF_S 0
#define SOUND_SPEED 0.034
#define ROAD_NUMBER 2

void transfer();
void MUX_v_updateMux_set1();
void MUX_v_updateMux_set2();
void MUX_v_setAdress(int ui_s0, int ui_s1, int ui_s2, int ui_s3);
void MUX_v_setTrig(int sw_trigPin);

void auto_parking();
void stepOne();
int parking_direction();
void park_left();
void park_right();

#endif