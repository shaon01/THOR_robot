
#include <ThorDriver.h>
//#include <Adafruit_MotorShield.h>
//#include <Servo.h>

Servo base;
Servo head;

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

bool received = false;

/*
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


ThorDriver::ThorDriver(Adafruit_MotorShield* AFMS )
  {
      _AFMS = AFMS;
      //_AFMS->begin();
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

void ThorDriver::direction(char dir)
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

        
      }
}

*/

void setup() {

  Serial.begin(9600);
  Serial.flush();

  base.attach(10); //servo1
  head.attach(9);  //servo2   

  AFMS.begin();

}

ThorDriver robot = ThorDriver(&AFMS); //creating robot object

void loop() {


  byte msg[10];                        //massage storing variable;
  int count = 0, val = 0;


  while (Serial.available() > 0) {

    byte inByte = (byte)Serial.read(); //reading serial
    msg[count] = inByte;

    count++;
    received = true;
    //Serial.print("got it");

  }

  if (count > 1) {                      ///converting byte to a integer

    for (int i = 1; i < count; i++) {
      val = 10 * val + (msg[i] - '0');

    }

  }


  if (received) {

    Serial.print("\n received direction :"); Serial.write(msg[0]);
    Serial.print("\n received value :"); Serial.print(val);

   if(msg[0] == 'h')
   {
          head.write(val);
          delay(15);
          Serial.println('d');
   }
          

    else if (msg[0] == 'g')
    {
          base.write(val);
          delay(15);
          Serial.println('d');
    }
    else
    {
    robot.direction(msg[0]);
    }
  }
  received = false;
  delay(10);
  Serial.flush();

}
