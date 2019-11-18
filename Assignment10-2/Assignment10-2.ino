// motor one 
int enA = 10; 
int in1 = 9; 
int in2 = 8; 

//motor two
int in3 = 7; 
int in4 = 6; 
int enB = 5; 

// sensor Left to Right
// A2 to A5
// 200 = black
// 600 = white
int state =0;

 
void setup() 
{ 
  // set all the motor control pins to outputs 
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(enB, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 

  // set sensor
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);

  Serial.begin(9600);
} 
void loop() 
{ 
  analogWrite(enA, 150);   // Speed Control 
  analogWrite(enB, 150);   // Speed Control 

  /*
  Serial.println(analogRead(A2));
  Serial.println(analogRead(A3));
  Serial.println(analogRead(A4));
  Serial.println(analogRead(A5));
  Serial.println(" ");
  delay(500);*/
  

  if (analogRead(A3) <= 200 and analogRead(A4) <= 200)
  {
    state =0;
  }
  if (analogRead(A2) <= 200)
  {
    state = 1;
  }
  if (analogRead(A5) <= 200)
  {
    state = 2;
  }

  if(state ==0)
  {
    Serial.println("motor1,2");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if(state ==1)
  {
    Serial.println("motor2");
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if(state ==2)
  {
    Serial.println("motor1");
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

}                                                                                                                                                                                                                                    
