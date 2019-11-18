// motor one 
int enA = 10; 
int in1 = 9; 
int in2 = 8; 




//motor two
int in3 = 7; 
int in4 = 6; 
int enB = 5; 
 
void setup() 
{ 
  // set all the motor control pins to outputs 
  pinMode(enA, OUTPUT); 
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(enB, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT); 
} 
void loop() 
{ 
  analogWrite(enA, 150);   // Speed Control 
  analogWrite(enB, 200); // Speed Control 

    
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); 
  digitalWrite(in4, HIGH); 
  delay(1200); 

  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay( 700);
  
  digitalWrite(in1, HIGH); 
  digitalWrite(in2, LOW);
  delay( 330);

  digitalWrite(in1, LOW); 
  digitalWrite(in2, LOW); 
  digitalWrite(in3, LOW); 
  digitalWrite(in4, LOW); 
  delay( 700);
}                                                                                                                                                                                                                                    
