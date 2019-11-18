#define a 2
#define b 3
#define c 4
#define dp 5
#define d 6
#define e 7
#define f 8
#define g 9
#define swA 11
#define swB 12

void startGame();
void showSelect();
void showRandom();
void gameWin();

int num=99, randnum=99;
unsigned long long timeA;
int NUM[48]={0,1,1,0,0,0,0,0,  1,1,0,0,1,1,0,1,  1,1,1,0,1,0,0,1,  0,1,1,0,0,0,1,1,  1,0,1,0,1,0,1,1,  1,0,1,0,1,1,1,1};

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(dp, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(swA, INPUT_PULLUP);
  pinMode(swB, INPUT_PULLUP);
}

void loop() {
  startGame();

// Select Number ==================================
  if(digitalRead(swA)==LOW && millis()-timeA>200)
  {
    timeA=millis();
    if(num==6) num=1;
    else num++;
    showSelect();
  }

// Random Number ===================================
  if(digitalRead(swB)==LOW && digitalRead(swA)==HIGH)
  {
    for(int i=1; i<=10; i++)
    {
       randnum = random(1,7);
       showRandom();
       delay(i*50);
    }
    digitalWrite(dp,LOW); delay(100); digitalWrite(dp,HIGH); delay(100); digitalWrite(dp,LOW); delay(100); digitalWrite(dp,HIGH);
  }
  
// Check result ======================================
  if(num==randnum)
  {
    for(int j=0; j<3;j++)
    {
      for(int i=2;i<=9;i++) digitalWrite(i,HIGH);
      delay(500);
      showRandom();
      delay(500);
    }
    
    for(int i=2;i<=9;i++) digitalWrite(i,HIGH);
    gameWin();
    num=99; randnum=99;
    delay(1000);
  }
  else if(num!=randnum && randnum!=99)
  {
    for(int j=0; j<3;j++)
    {
      for(int i=2;i<=9;i++) digitalWrite(i,HIGH);
      delay(500);
      showRandom();
      delay(500);
    }
    for(int i=2;i<=9;i++) digitalWrite(i,HIGH);
    gameLose();
    num=99; randnum=99;
    delay(1000);
  }
}

// function ============================================================
void showSelect()
{
  for(int i=(num*8)-8;i<=(num*8)-1;i++)
    {
      if(NUM[i]==1) digitalWrite((i%8)+2,LOW);
      else digitalWrite((i%8)+2,HIGH);
    }
}

void showRandom()
{
  for(int i=(randnum*8)-8;i<=(randnum*8)-1;i++)
  {
     if(NUM[i]==1) digitalWrite((i%8)+2,LOW);
     else digitalWrite((i%8)+2,HIGH);
  }
}

void startGame()
{
  if(num==99)
  {
    for(int i=2;i<=9;i++) digitalWrite(i,HIGH);
    digitalWrite(dp,LOW); delay(200); digitalWrite(dp,HIGH); delay(200); digitalWrite(dp,LOW); delay(200); digitalWrite(dp,HIGH);
    num=0;
  }
}

void gameWin()
{
  for(int j=0; j<3;j++)
    {
      for(int i=2;i<=8;i++)
      {
        if(i!=5) 
        {
           digitalWrite(i, LOW);
           delay(100);
           digitalWrite(i, HIGH);
        }
      }
    }
}

void gameLose()
{
  for(int i=0;i<4;i++)
    {
      digitalWrite(9,LOW);
      delay(500);
      digitalWrite(9,HIGH);
      delay(500);
    }
}

