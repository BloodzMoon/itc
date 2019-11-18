#define s1 analogRead(A2)
#define s2 analogRead(A3)
#define s3 analogRead(A4)
#define s4 analogRead(A5)

#define left 3   // Active HIGH
#define right 2  //
#define green 12 // Active LOW
#define red 13   //


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
// black <= 200
// white >= 600

int state = 0;
bool b1, b2, b3, b4;

int motorspeed = 0;
int Ls = 0;
int Rs = 0;
int basespeed;
int maxspeed;
int error = 0;
int Kp;

void setup()
{
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(left , OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(red  , OUTPUT);
  pinMode(green, OUTPUT);


  Kp = 35; basespeed = 150; maxspeed = 255;
  digitalWrite(green, 0); // light up
  digitalWrite(red, 1);  // darken
  
  Serial.begin(9600);
}
void loop()
{
  check();

  if (state == 0)
  {
    if (b1 == false and b4 == true)
    {
      digitalWrite(right, 1);
      MOVE(-basespeed, -basespeed);
      delay(50);
      RESET();
      delay(50);
      state++;
    }
    MOVE(118, 100);
  }
  else if (state == 1) // first leaw
  {
    MOVE(0, 0);
    delay(50);
    ROTATE(-220, 300);
    while (1)
    {
      check();
      if (b2 == true and b3 == true)
      {
        MOVE(150, -150);
        delay(50);
        digitalWrite(right, 0);
        state++;
        break;
      }
      MOVE(-150, 150);
    }
  }
  else if (state == 2) // enter RED
  {
    if (b1 == true and b2 == true and b3 == true and b4 == true)
    {
      state++;
    }
    MOVE(155, 100);
  }
  else if (state == 3) // Backward
  {
    delay(200);
    digitalWrite(left, 1);
    digitalWrite(right, 1);
    MOVE(-basespeed, -basespeed);
    delay(50);
    RESET();
    delay(50);
    MOVE(0, 0);
    delay(50);

    while (1)
    {
      MOVE(-200, -165);
      delay(2800);
      digitalWrite(left, 0);
      state++;
      break;
    }
    MOVE(200, 165);
    delay(50);
    RESET();
    delay(50);
    MOVE(0, 0);

  }
  else if (state == 4)  //Second leaw
  {
    ROTATE(-255, 300);
    while (1)
    {
      check();
      if (b2 == true and b3 == true)
      {
        MOVE(150, -150);
        delay(50);
        digitalWrite(right, 0);
        state++;
        break;
      }
      MOVE(-155, 150);
    }
  }
  else if (state == 5)
  {
    MOVE(100, 100);
    if (b1 == true and b4 == true)
    {
      digitalWrite(left, 1);
      MOVE(-basespeed, -basespeed);
      delay(50);
      MOVE(0, 0);
      delay(50);
      ROTATE(150, 200);
      while (1)
      {
        check();
        if (b2 == true and b3 == true)
        {
          digitalWrite(left, 0);
          MOVE(-150, 150);
          delay(50);
          state++;
          break;
        }
        MOVE(150, -150);
      }
    }
  }
  else if (state == 6) // go froward |_|
  {
    if (b1 == true and b2 == true and b3 == true and b4 == true)
    {
      digitalWrite(left, 1);
      MOVE(-basespeed, -basespeed);
      delay(50);
      MOVE(0, 0);
      delay(50);
      state++;
    }
    MOVE(80, 80);

  }
  else if (state == 7) // Leaw to BLUE!!
  {
    ROTATE(150, 200);
    while (1)
    {
      check();
      if (b2 == true and b3 == true)
      {
        digitalWrite(left, 0);
        MOVE(-100, 100);
        delay(50);
        state++;
        break;
      }
      MOVE(100, -100);
    }
  }
  else if (state == 8)
  {
    MOVE(100, 100);
    if (b1 == true and b2 == true and b3 == true and b4 == true)
    {
      digitalWrite(right, 1);
      delay(50);
      MOVE(-basespeed, -basespeed);
      delay(50);
      MOVE(0, 0);
      delay(50);
      state++;
    }
  }
  else if (state == 9) // turn right BLUE
  {
    ROTATE(-80, 100);
    while (1)
    {
      check();
      if (b2 == true and b3 == true)
      {
        digitalWrite(right, 0);
        MOVE(150, -150);
        delay(50);
        state++;
        break;
      }
      MOVE(-150, 150);
    }
  }
  else if (state == 10) //backward to blue
  {
    while (1)
    {
      digitalWrite(right, 1);
      digitalWrite(left, 1);
      MOVE(-200, -165);
      delay(1800);
      MOVE(200, 165);
      delay(50);
      RESET();
      delay(50);
      MOVE(0, 0);
      digitalWrite(right, 0);
      digitalWrite(left, 0);
      MOVE(80, 220);
      delay(200);
      state++;
      break;
    }

  }
  else if (state == 11) //before finish!!
  {
    if (b1 == true and b2 == true and b3 == true and b4 == true)
    {
      state++;
    }
    MOVE(80, 80);
  }
  else if (state == 12)
  {
    if (b1 == true and b2 == true and b3 == true and b4 == true)
    {
      MOVE(-basespeed, -basespeed);
      delay(50);
      RESET();
      delay(50);
      state++;
    }
    MOVE(80, 80);
  }
  else if (state == 13) //forward finish
  {
    MOVE(80, 80);
    if (b1 == true and b2 == true and b3 == true and b4 == true)
    {
      MOVE(-basespeed, -basespeed);
      delay(50);
      RESET();
      delay(50);
      state++;
    }
  }
  else if (state == 14) // turn right to FINISH!!!
  {
    ROTATE(-150, 200);
    while (1)
    {
      check();
      if (b2 == true and b3 == true)
      {
        MOVE(150, -150);
        delay(50);
        state++;
        break;
      }
      MOVE(-150, 150);
    }
  }
  else if (state == 15)
  {
    while (1)
    {

      check();
      MOVE(100, 135);
      if (b1 == true and b2 == true and b3 == true and b4 == true)
      {
        digitalWrite(red, 0);
        digitalWrite(green, 1);
        delay(400);
        MOVE(-basespeed, -basespeed);
        delay(50);
        RESET();
        delay(50);
        state++;
        break;
      }
    }
  }
  else if (state == 16)
  {
    digitalWrite(in1, LOW); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW);
    analogWrite(enA, 0); analogWrite(enB, 0);
    delay(1000);
    while (1)
    {
      digitalWrite(left, 1);
      digitalWrite(green, 1);
      digitalWrite(red, 1);
      digitalWrite(right, 0);
      delay(20);
      digitalWrite(left, 0);
      digitalWrite(green, 0);
      digitalWrite(red, 1);
      digitalWrite(right, 0);
      delay(20);
      digitalWrite(left, 0);
      digitalWrite(green, 1);
      digitalWrite(red, 0);
      digitalWrite(right, 0);
      delay(20);
      digitalWrite(left, 0);
      digitalWrite(green, 1);
      digitalWrite(red, 1);
      digitalWrite(right, 1);
      delay(20);
      digitalWrite(left, 0);
      digitalWrite(green, 1);
      digitalWrite(red, 0);
      digitalWrite(right, 0);
      delay(20);
      digitalWrite(left, 0);
      digitalWrite(green, 0);
      digitalWrite(red, 1);
      digitalWrite(right, 0);
      delay(20);
    }

  }

  if (state != 3 or state != 10 /*or state!=11 or state!=12 or state!=13*/ or state != 15)
    PID();
}


///////////////////////////////////////////////////////////////
void ROTATE(int s, int d)
{
  MOVE(s, -s);
  delay(d);
  MOVE(-s, s);
  delay(100);
}

void RESET()
{
  Ls = basespeed;
  Rs = basespeed;
}
void STOP()
{
  while (1)
  {
    digitalWrite(in1, LOW); digitalWrite(in2, LOW); digitalWrite(in3, LOW); digitalWrite(in4, LOW);
    analogWrite(enA, 0); analogWrite(enB, 0);
  }
}

void MOVE(int l, int r)
{
  if (l > 0)
  {
    analogWrite(enA, l);
    digitalWrite(in2, LOW);
    digitalWrite(in1, HIGH);
  }
  else if (l < 0)
  {
    analogWrite(enA, l);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  }
  else
  {
    analogWrite(enA, l);
    digitalWrite(in2, LOW);
    digitalWrite(in1, LOW);
  }

  if (r > 0)
  {
    analogWrite(enB, r);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else if (r < 0)
  {
    analogWrite(enB, r);
    digitalWrite(in4, LOW);
    digitalWrite(in3, HIGH);
  }
  else
  {
    analogWrite(enB, r);
    digitalWrite(in4, LOW);
    digitalWrite(in3, LOW);
  }
}


void check()
{
  if (s1 < 200)b1 = true; else b1 = false;
  if (s2 < 200)b2 = true; else b2 = false;
  if (s3 < 200)b3 = true; else b3 = false;
  if (s4 < 200)b4 = true; else b4 = false;

  Serial.print(b1); Serial.print(b2); Serial.print(b3); Serial.println(b4);
}

void PID()
{
  digitalWrite(in2, LOW); digitalWrite(in3, LOW);

  if       (b2 == 0 and b3 == 1) error = 1;
  else if  (b2 == 1 and b3 == 1) error = 0;
  else if  (b2 == 1 and b3 == 0) error = -1;

  motorspeed = Kp  * error;
  Ls = basespeed - motorspeed;
  Rs = basespeed + motorspeed;

  if (Ls > maxspeed) Ls = maxspeed;
  if (Ls < 0) Rs = basespeed;
  if (Rs > maxspeed) Ls = maxspeed;
  if (Rs < 0) Rs = basespeed;

  analogWrite(enA, Ls);
  analogWrite(enB, Rs);

  Serial.print("Ls = "); Serial.print(Ls); Serial.print("    Rs = "); Serial.println(Rs);

  digitalWrite(in1, HIGH); digitalWrite(in4, HIGH);
}
