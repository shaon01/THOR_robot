
#include <ThorDriver.h>
#include <Servo.h>

Servo base;
Servo head;


ThorDriver robot; //creating robot object

bool received = false;

void setup() {

  Serial.begin(9600);
  Serial.flush();

  base.attach(10); //servo1
  head.attach(9);  //servo2   

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
