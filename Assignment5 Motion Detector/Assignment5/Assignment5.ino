#define speaker 8
#define switchStop 4
#define switchCal 5

bool sound;
int calX, calY, calZ;

void setup() 
{
  pinMode(A1, INPUT); //X-axis
  pinMode(A2, INPUT); //Y-axis
  pinMode(A3, INPUT); //Z-axis
  pinMode(speaker, OUTPUT);
  pinMode(switchStop, INPUT_PULLUP);
  pinMode(switchCal, INPUT_PULLUP);
  calX = analogRead(A1);
  calY = analogRead(A2);
  calZ = analogRead(A3);
}

void loop() 
{
  
// Switch ==============================

  if (digitalRead(switchStop)==0)
    {
      sound = false;
      tone(speaker, 900); delay(100); tone(speaker, 800); delay(100); tone(speaker, 600); delay(100);
      noTone(speaker);
      delay(200);
    }
    
  if (digitalRead(switchCal)==0)
  {
    calX = analogRead(A1);
    calY = analogRead(A2);
    calZ = analogRead(A3);

    tone(speaker, 700); delay(100); tone(speaker, 750); delay(100); tone(speaker, 800); delay(100);
    noTone(speaker);
    delay(200);
  }


// Accelerator ==========================

  if (analogRead(A1)>=calX+10 or analogRead(A1)<=calX-10)   // X- axis
    sound = true;
  if (analogRead(A2)>=calY+10 or analogRead(A2)<=calY-10)   // Y- axis
    sound = true;
  if (analogRead(A3)>=calZ+38 or analogRead(A3)<=calZ-38)   // Z- axis
    sound = true;


// Speaker ==============================

  if (sound)
  {
    tone(speaker, 1000); delay(50);
    noTone(speaker); delay(50);
  }
}
