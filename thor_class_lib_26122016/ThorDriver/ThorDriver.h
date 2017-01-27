/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef ThorDriver_h
#define ThorDriver_h

#include <Adafruit_MotorShield.h>
#include <Servo.h> 




class ThorDriver
{
  private:
    int m_moving_speed = 60;             //speed to move forward and backward
    int m_turn_speed = 40;               //speed to turn left or right

    uint8_t leftDir;   //wheel direction
    uint8_t rightDir;
    
    Adafruit_MotorShield* _AFMS ;
    Adafruit_DCMotor *backLeftWheel   = _AFMS->getMotor(4);  // back left wheel 
    Adafruit_DCMotor *backRightWheel  = _AFMS->getMotor(3);  // back right wheel
    Adafruit_DCMotor *frontLeftWheel  = _AFMS->getMotor(2); // front left wheel
    Adafruit_DCMotor *frontRightWheel = _AFMS->getMotor(1); //front right wheel
  
    
    
  
  public:
    ThorDriver(Adafruit_MotorShield* AFMS);
    void moveMotor();
    void direction(char dir);

    void set_moveSpeed(int moving_speed) { m_moving_speed = moving_speed;};
    void set_trunSpeed(int turn_speed) { m_turn_speed = turn_speed;};
    int get_moveSpeed() {return m_moving_speed;};
    int get_turnSpeed() {return m_turn_speed;};
  
  };
#endif
