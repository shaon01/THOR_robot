
#include "ThorDriver.h"


ThorDriver::ThorDriver(Adafruit_MotorShield* AFMS )
	{
			_AFMS = AFMS;
						
			backLeftWheel   = _AFMS->getMotor(4);  // back left wheel 
			backRightWheel  = _AFMS->getMotor(3);  // back right wheel
			frontLeftWheel  = _AFMS->getMotor(2); // front left wheel
			frontRightWheel = _AFMS->getMotor(1); //front right wheel		
	
	}
	
	
void ThorDriver::moveMotor()
{
	int speedVal;

      (leftDir == rightDir) ?  speedVal = m_moving_speed : speedVal = m_turn_speed;

      frontLeftWheel  -> setSpeed(speedVal);
      frontRightWheel ->setSpeed(speedVal);
      backLeftWheel  -> setSpeed(speedVal);
      backRightWheel ->setSpeed(speedVal);

      frontLeftWheel -> run(rightDir);  // to move left FLW & BRW set backwards and vise versa
      backRightWheel -> run(rightDir);
      
      frontRightWheel-> run(leftDir);     
      backLeftWheel  -> run(leftDir);
      

      Serial.print("\n speed value :"); Serial.print(speedVal);
      //Serial.print("\n direciton of left wheel :"); Serial.print(leftDir, 'DEC');
      //Serial.print("\n direciton of right wheel :"); Serial.print(rightDir, 'DEC');

}

void ThorDriver::direction(char dir, int val)
{
	 switch (dir) {
		//driving backward due to motor issue its wrote as reverse
        case 'z':
          leftDir  = FORWARD;
          rightDir = FORWARD;
          moveMotor();
          break;

        case 'a':
          leftDir  = BACKWARD;
          rightDir = FORWARD;
          moveMotor();
          break;


        case 'd':
          leftDir  = FORWARD;
          rightDir = BACKWARD;
          moveMotor();
          break;
		//driving froward
        case 'w':
          leftDir  = BACKWARD;
          rightDir = BACKWARD;
          moveMotor();
          break;


        case 's':
          leftDir  = RELEASE;
          rightDir = RELEASE;
          moveMotor();
          break;

        case '+':
          set_moveSpeed(get_moveSpeed() + 5);
          moveMotor();
          break;

        case '-':
          set_moveSpeed(get_moveSpeed() - 5);
          moveMotor();
          break;
          
         case'h':
             m_servoDeg = max(0,val);
             m_servoDeg = min(val,80);
             head.write(m_servoDeg);
             delay(15);
             break;

         case 'b':
             m_servoDeg = max(20,val);
             m_servoDeg = min(val,150);
             Serial.print("\n in class base value :"); Serial.print(m_servoDeg);
             base.write(m_servoDeg);
             delay(15);
             break;


        
      }
}
