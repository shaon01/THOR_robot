
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

        case 'w':
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

        case 'z':
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
			head.write(val);
			delay(15);
			break;
			
		case 'b':
			base.write(val);
			delay(15);
			break;
			

        
      }
}
