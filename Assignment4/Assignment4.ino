#include <LedControl.h>
#define analogX 0  //analog X-axis port 0

// Prototype =================================================
void drawBar(int);
void eraseBar(int);
void drawBall();
void eraseBall(int, int);
void checkGame();
void gameoverAnimation();
void startGame();

// Variables =================================================
LedControl lc = LedControl(12,10,11,1); //din, clk, cs
int HP=3, barPosition, ballX, ballY, ballMove, ballChangeDirect, ballSpeed;
unsigned long long barMoveDelay=0, ballMoveDelay=0;

byte HP3[8] ={ B00000000, B00011000, B00111100, B01111110, B11111111, B11111111, B01100110, B00000000, };
byte HP2[8] ={ B00000000, B00001000, B00011100, B00011110, B00001111, B00011111, B00000110, B00000000, };
byte HP1[8] ={ B00000000, B00001000, B00000100, B00000110, B00000011, B00000011, B00000110, B00000000, };

// Setup =====================================================
void setup() 
{
  Serial.begin(9600);
    //wake up device from saving power mode
    lc.shutdown(0, false);
    lc.setIntensity(0, 8);
    lc.clearDisplay(0);
    
    startGame();
    Serial.begin(9600);
}

// Main loop ================================================
void loop() 
{ 
  Serial.println(analogRead(analogX)); delay(100);
  //Reset timer anti variable error
  if(barMoveDelay>1000000) barMoveDelay=0;
  if(ballMoveDelay>1000000) ballMoveDelay=0;
  
  // Player Movement
  // Move left
  if(analogRead(analogX)<280 && barPosition<5 && millis()-barMoveDelay>100) 
  { 
    eraseBar(barPosition++); drawBar(barPosition); 
    barMoveDelay=millis(); 
  }
  // Move right
  if(analogRead(analogX)>650 && barPosition>0 && millis()-barMoveDelay>100) 
  { 
    eraseBar(barPosition--); drawBar(barPosition); 
    barMoveDelay=millis();  
  }

   // Ball Movement
   drawBall();

   // Check game();
   checkGame();
}

// function ====================================================
void drawBar(int x)
{
  lc.setLed(0, 0, x  , true);
  lc.setLed(0, 0, x+1, true);
  lc.setLed(0, 0, x+2, true);
}

void eraseBar(int x)
{
  lc.setLed(0, 0, x  , false);
  lc.setLed(0, 0, x+1, false);
  lc.setLed(0, 0, x+2, false);
}

void drawBall()
{
 /*   NW   N   NE       0     1
      W         E 
      SW   S   SE       2     3  */
      
  // Move NW
  if( ballMove==0 && ballX<7 && ballY<7 && millis()-ballMoveDelay>ballSpeed )
  {
    ballMoveDelay=millis();
    eraseBall(ballY,ballX); lc.setLed(0, ++ballY, ++ballX, true);
  }
  // Move NE
  else if( ballMove==1 && ballX>0 && ballY<7 && millis()-ballMoveDelay>ballSpeed )
  {
    ballMoveDelay=millis();
    eraseBall(ballY,ballX); lc.setLed(0, ++ballY, --ballX, true);
  }
  // Move SW
  else if( ballMove==2 && ballX<7 && ballY>0 && millis()-ballMoveDelay>ballSpeed )
  {
    ballMoveDelay=millis();
    eraseBall(ballY,ballX); lc.setLed(0, --ballY, ++ballX, true);
  }
  // Move SE
  else if( ballMove==3 && ballX>0 && ballY>0 && millis()-ballMoveDelay>ballSpeed )
  {
    ballMoveDelay=millis();
    eraseBall(ballY,ballX); lc.setLed(0, --ballY, --ballX, true);
  }
  else ballChangeDirect=1;

  // Ball hit wall and change Direction // if Ball hit bar >> increase Ball speed
  if( ballChangeDirect==1 && ballMove==0 && ballY==7 ) { ballMove=2; ballChangeDirect=0; }
  if( ballChangeDirect==1 && ballMove==0 && ballX==7 ) { ballMove=1; ballChangeDirect=0; }
  if( ballChangeDirect==1 && ballMove==1 && ballY==7 ) { ballMove=3; ballChangeDirect=0; }
  if( ballChangeDirect==1 && ballMove==1 && ballX==0 ) { ballMove=0; ballChangeDirect=0; }
  if( ballChangeDirect==1 && ballMove==2 && ballX==7 ) { ballMove=3; ballChangeDirect=0; }
  if( ballChangeDirect==1 && ballMove==2 && (ballX-barPosition<=3 && ballX-barPosition>=-1 && ballY==1) ) { ballMove=0; ballChangeDirect=0; if(ballSpeed>60) ballSpeed-=60; }
  if( ballChangeDirect==1 && ballMove==3 && ballX==0 ) { ballMove=2; ballChangeDirect=0; }
  if( ballChangeDirect==1 && ballMove==3 && (ballX-barPosition<=3 && ballX-barPosition>=-1 && ballY==1) ) { ballMove=1; ballChangeDirect=0; if(ballSpeed>60) ballSpeed-=60; }
}

void eraseBall(int y, int x)
{
  lc.setLed(0, ballY, ballX, false);
}

void startGame()
{
  lc.clearDisplay(0);
  showHP();
  
  // Reset Player
  barPosition=3; drawBar(barPosition);
  
  // Reset ball
  ballX=random(1,7), ballY=4, ballMove=random(0,2), ballChangeDirect=0, ballSpeed=480;
  
}
void checkGame()
{
  // Game Over animation
  if( ballY==0 ) 
  {
    if( HP==1 )
    {
      gameoverAnimation();
      delay(500);
      HP=3;
      startGame();
    }
    else if( HP==2 )
    {
      // dot fill until full screen
      for( int row=7; row>=0; row-- ) { for( int column=7; column>=0; column-- ) { lc.setLed(0, row, column, true); delay(10); } }
      delay(500); lc.clearDisplay(0);

      // HP2 to HP1 animation
      for(int i=0; i<5; i++ )
      {
         for(int row=0; row<8; row++) lc.setRow(0, row, HP2[row]);
         delay(200); lc.clearDisplay(0);
         for(int row=0; row<8; row++) lc.setRow(0, row, HP1[row]);
         delay(200); lc.clearDisplay(0);
      }
      HP=1; 
      startGame();
    }
    else if( HP==3 )
    {
      // dot fill until full screen
      for( int row=7; row>=0; row-- ) { for( int column=7; column>=0; column-- ) { lc.setLed(0, row, column, true); delay(10); } }
      delay(500); lc.clearDisplay(0);

      // HP3 to HP2 animation
      for(int i=0; i<5; i++ )
      {
         for(int row=0; row<8; row++) lc.setRow(0, row, HP3[row]);
         delay(200); lc.clearDisplay(0);
         for(int row=0; row<8; row++) lc.setRow(0, row, HP2[row]);
         delay(200); lc.clearDisplay(0);
      }
      HP=2; 
      startGame();
    }
  }
}

void showHP()
{
    if( HP==3 )
    {
      for(int i=0; i<3; i++ )
      {
        delay(500);
        for(int row=0; row<8; row++) lc.setRow(0, row, HP3[row]);
        delay(600); lc.clearDisplay(0);
      }
    }
    else if( HP==2 )
    {
      for(int i=0; i<3; i++ )
      {
        delay(500);
        for(int row=0; row<8; row++) lc.setRow(0, row, HP2[row]);
        delay(600); lc.clearDisplay(0);
      }
    }
    else if( HP==1 )
    {
      for(int i=0; i<3; i++ )
      {
        delay(500);
        for(int row=0; row<8; row++) lc.setRow(0, row, HP1[row]);
        delay(600); lc.clearDisplay(0);
      }
    }
}

void gameoverAnimation()
{
  // dot fill until full screen
  for( int row=7; row>=0; row-- ) { for( int column=7; column>=0; column-- ) { lc.setLed(0, row, column, true); delay(10); } }
  delay(500); lc.clearDisplay(0);

  // 'X' animation
  for( int i=0; i<3; i++ )
  {
     delay(500);
     for( int row=7; row>=0; row-- )
     {
       for( int column=7; column>=0; column-- )
       {
          if( row-column==0 || row+column==7) lc.setLed(0, row, column, true);
       }
     }
     delay(500); lc.clearDisplay(0);
  }
}

