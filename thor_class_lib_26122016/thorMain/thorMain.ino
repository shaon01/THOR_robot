#include <ThorDriver.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

ThorDriver robot = ThorDriver(&AFMS); //creating robot object

bool received = false;

void setup() {

  Serial.begin(9600);
  Serial.flush();

  robot.base.attach(10); //servo1  setting base servo
  robot.head.attach(9);  //servo2  setting head servo

  AFMS.begin();

}



void loop() {


  byte msg[10];                        //massage storing variable;
  int count = 0, val = 0;


  while (Serial.available() > 0) {

    byte inByte = (byte)Serial.read(); //reading serial
    msg[count] = inByte;

    count++;
    received = true;

  }

  if (count > 1) {                      ///converting byte to a integer

    for (int i = 1; i < count; i++) {
      val = 10 * val + (msg[i] - '0');

    }

  }


  if (received) {

    //Serial.print("\n received direction :");
    Serial.write(msg[0]);
    //Serial.print("\n received value :");Serial.print(val);
  
    robot.direction(msg[0],val);

  }
  received = false;
  delay(10);
  Serial.flush();

}
