#ifndef Servo_Motor_h_
#define Servo_Motor_h_

#define servo_max 122   ///< The maximum angle of the servo
#define servo_min 65    ///< The minimum angle of the servo
#define default_pos 90  ///< Default position of servo
#define leftRequest 1   ///< Turn on left steering on manual control
#define rightRequest 1  ///< Turn on right steering on manual control


void turn_servo_left();
void turn_servo_right();
void manualControl();
void automaticControl();
void driveMode();
void readAngle();

#endif