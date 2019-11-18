long long timeRED, timeYELLOW, timeGREEN, timeSWR=0, timeSWY=0, timeSWG=0;

void setup() {
 
  #define RED 5
  #define YELLOW 4
  #define GREEN 3
  #define SWR 13
  #define SWY 12
  #define SWG 11

  pinMode( RED, OUTPUT);
  pinMode( YELLOW, OUTPUT);
  pinMode( GREEN, OUTPUT);
  pinMode( SWR, INPUT);
  pinMode( SWY, INPUT);
  pinMode( SWG, INPUT);
}

void loop() {
  
//RED
  if( digitalRead(SWR)==LOW && millis()-timeSWR>300 )
  {
    if( digitalRead(RED)==HIGH ) digitalWrite(RED, LOW);
    else 
    {
      digitalWrite(RED, HIGH);
      timeRED = millis();
    }
    timeSWR=millis();
  }
  if(millis()-timeRED>=3000) digitalWrite(RED,LOW);


//YELLOW
  if( digitalRead(SWY)==LOW && millis()-timeSWY>300 )
  {
    if( digitalRead(YELLOW)==LOW && digitalRead(RED)==LOW && digitalRead(GREEN)==LOW ) 
    {
      digitalWrite(YELLOW, HIGH);
      timeYELLOW = millis();
    }
  }
  if(millis()-timeYELLOW>=500 && millis()-timeYELLOW<=1000)digitalWrite(YELLOW,LOW);
  else if(millis()-timeYELLOW>=1000 && millis()-timeYELLOW<=1500) digitalWrite(YELLOW,HIGH);
  else if(millis()-timeYELLOW>=1500 && millis()-timeYELLOW<=2000) digitalWrite(YELLOW,LOW);
  


//GREEN
  if( digitalRead(SWG)==LOW && millis()-timeSWG>300 )
  {
    if( digitalRead(GREEN)==HIGH ) digitalWrite(GREEN, LOW);
    else if ( digitalRead(GREEN)==LOW && digitalRead(RED)==LOW )
    {
      digitalWrite(GREEN, HIGH);
      timeGREEN = millis();
    }
    timeSWG=millis();
  }
  if(millis()-timeGREEN>=3000) digitalWrite(GREEN,LOW);
      
}
