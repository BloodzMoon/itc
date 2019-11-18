#include <Servo.h>

Servo motor1, motor2, motor3, motor4; 


int pos1 = 70;      // 70 to 0     turn right
int pos2 = 90;      // 90 to 40    up
int pos3 = 140;     // 100 to 140  up
int pos4 = 60;      // 60 to 180   catch
int Stop = 0;

void setup() 
{
  motor1.attach(9);  
  motor2.attach(8); 
  motor3.attach(7);
  motor4.attach(6);  

  motor1.write(pos1);
  motor2.write(pos2);
  motor3.write(pos3);
  motor4.write(pos4);
}

void loop() 
{
  if (Stop==0)
  {
    // Up
    for (pos2 = 90; pos2 >= 40; pos2--)
      { motor2.write(pos2); delay(15); }
  }
  
  if (Stop <4)
  {

    // Turn Right
    for (pos1 = 70; pos1 >= 0; pos1--)
      { motor1.write(pos1); delay(15); }

    // Down
    for (pos2 = 40; pos2 <= 145; pos2++)
      { motor2.write(pos2); delay(15); }

    // Catch
    for (pos4 = 60; pos4 <= 180; pos4++)
      { motor4.write(pos4); delay(15); }

    // Up
    for (pos2 = 145; pos2 >= 40; pos2--)
      { motor2.write(pos2); delay(15); }
      
    // Turn Left
    for (pos1 = 0; pos1 <= 70; pos1++)
      { motor1.write(pos1); delay(15); }
      
    // Release
    for (pos4 = 180; pos4 >= 60; pos4--)
      { motor4.write(pos4); delay(15); }

    Stop++;
  }
  if(Stop == 4)
  // Down
    for (pos2 = 40; pos2 <= 90; pos2++)
      { motor2.write(pos2); delay(15); Stop++;}
}
