#include <SoftwareSerial.h> 

#define Rock  7
#define Paper 8
#define Scis  9
#define RED    4
#define YELLOW 5
#define GREEN  6
// Light->Rock->Paper->Scissors 

String inputString = ""; 
char inChar, receive, Play, End;
bool played = false;
int waitTime=0;
SoftwareSerial mySerial(2,3); //Rx, Tx

void setup() 
{
    Serial.begin(4800);
    mySerial.begin(4800);

    pinMode(Rock,  INPUT_PULLUP);
    pinMode(Paper, INPUT_PULLUP);
    pinMode(Scis,  INPUT_PULLUP);

    pinMode(RED,    OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN,  OUTPUT);
    
}

void loop() 
{     
    // not play -> reset
    if(played)
      waitTime++;
    if(played and !End and waitTime>=800)
    {
      Play='\0';
      mySerial.print('z');
      receive='\0';
      played = false;
      End = false;
      waitTime = 0;
    }
    
    //input ================================
    if (digitalRead(Rock)==0 and !played)
    {
      mySerial.print('R');
      Play = 'R';
      played = true;
    }
    if (digitalRead(Paper)==0 and !played)
    {
      mySerial.print('P');
      Play = 'P';
      played = true;
    }
    if (digitalRead(Scis)==0 and !played)
    {
      mySerial.print('S');
      Play = 'S';
      played = true;
    }

    //check game =========================
    // draw
    if((Play == receive )and played)
    {
      digitalWrite(RED, HIGH); 
      digitalWrite(YELLOW, LOW);
      digitalWrite(GREEN, HIGH);
      End = true;
    }
    // lose
    if((Play == 'R' and receive == 'P') or (Play == 'P' and receive == 'S') or (Play == 'S' and receive == 'R') and played)
    {
        digitalWrite(RED, LOW); 
        digitalWrite(YELLOW, HIGH);
        digitalWrite(GREEN, HIGH);
        End = true;
    }
    // win
    if((Play == 'R' and receive == 'S') or (Play == 'P' and receive == 'R') or (Play == 'S' and receive == 'P') and played)
    {
        digitalWrite(RED, HIGH); 
        digitalWrite(YELLOW, HIGH);
        digitalWrite(GREEN, LOW);
        End = true;
    }

    if (End)
    {
      delay(4000);
      digitalWrite(RED, LOW); digitalWrite(YELLOW, HIGH); digitalWrite(GREEN, HIGH); delay(200);
      digitalWrite(RED, HIGH); digitalWrite(YELLOW, LOW); digitalWrite(GREEN, HIGH); delay(200);
      digitalWrite(RED, HIGH); digitalWrite(YELLOW, HIGH); digitalWrite(GREEN, LOW); delay(200);
      digitalWrite(RED, LOW); digitalWrite(YELLOW, LOW); digitalWrite(GREEN, LOW); delay(200);

      Play='\0';
      receive='\0';
      played = false;
      End = false;
    }

    attachInterrupt(0,SoftwareSerialEvent,FALLING);

}

void SoftwareSerialEvent() 
{      
  if(mySerial.available())
  {
    receive = (char)mySerial.read();
    Serial.print(receive);       
  }
}
