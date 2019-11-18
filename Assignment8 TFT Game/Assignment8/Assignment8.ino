#include <ST7735_TEE.h>
TEE_ST7735 lcd(9, 10, 11, 12, 13);   //CSK, SDA, A0, RST, CS

// Prototype ================================
void createBoder();
void drawHeart();
void drawPoint();
void drawBar();
void moveBar();
void drawBall();
void moveBall();

// Variable ==================================
int  x,  y,  ex,  ey;   // Player
int bx, by, ebx, eby;   // Ball

int  LeftOrRight, UpOrDown, ballSpeed=2;
char points ='0';
int  heart  = 3, wait;


// Setup ======================================
void setup() 
{
  lcd.init(lcd.VERTICAL);
  lcd.fillScreen(BLACK);
  createBoder();
  
// set bar position
  x = 50;  ex = 50;
  y = 145; ey = 145;
  
// ball position
  bx = 64; ebx = 60;
  by = 30; eby = 30;

  
// random ball direction
  randomSeed(analogRead(7));
  LeftOrRight = random(0,2); // 0 = left , 1 = right
  UpOrDown    = random(0,2); // 0 = up   , 1 = down
}

 
// Main Loop =============================
void loop() 
{
  while (by < 157 and points <= '9')
  {
    drawHeart();
    drawPoint();
    drawBar();
    moveBar();
    drawBall();
    moveBall();
  }
  if (points >'9') 
    Win();
  else if (heart != 1)
  {
    heart--;
    resetGame();
  }
  else 
    Lose();
    
  if(wait >= 4)
    resetGame();
}


// Function =================================

void drawHeart()
{
  if (heart >= 1)
  {
    lcd.fillCircle(112,10,2,RED);
    lcd.fillCircle(116,10,2,RED);
    lcd.fillCircle(114,12,2,RED);
  }
    
  if(heart >= 2)
  {
    lcd.fillCircle(102,10,2,RED);
    lcd.fillCircle(106,10,2,RED);
    lcd.fillCircle(104,12,2,RED);
  }
    
  if (heart >= 3)
  {
    lcd.fillCircle(92,10,2,RED);
    lcd.fillCircle(96,10,2,RED);
    lcd.fillCircle(94,12,2,RED);
  }
}

void drawPoint()
{
  lcd.fillRect(10,10,5,8,BLACK);
  lcd.drawChar(10,10,points,GREEN,1);
}

void drawBar()
{
  lcd.drawFastLine(ex, ey  , 25, BLACK, 0); // (x, y, size, color, Vertical/Horizontal)
  lcd.drawFastLine(ex, ey+1, 25, BLACK, 0);
  lcd.drawFastLine( x, y   , 25, GREEN, 0); 
  lcd.drawFastLine( x, y+1 , 25, GREEN, 0);
}

void moveBar()
{
  if (analogRead(0) > 540 and x < 99)    // Right
  {
    ex = x; 
    ey = y;
    x += 5;
  }
  else if (analogRead(0) < 220 and x > 3) // Left
  {
    ex = x;
    ey = y;
    x -= 5; 
  }
}

void drawBall()
{
  lcd.fillCircle(ebx, eby ,4, BLACK);
  lcd.fillCircle( bx,  by, 4, YELLOW);
}

void moveBall()
{
  if (LeftOrRight == 0)     // Left
  { 
    ebx = bx;
    bx -= ballSpeed;
    if (bx < 8) LeftOrRight = 1;
  }
  else if (LeftOrRight == 1) // Right
  {
    ebx = bx;
    bx += ballSpeed;
    if (bx > 120) LeftOrRight=0;
  }
  if (UpOrDown == 0)         // Up
  { 
    eby = by;
    by -= ballSpeed;
    if (by <= 7) UpOrDown = 1;
  }
  else if (UpOrDown == 1)    // Down
  { 
    eby = by;
    by += ballSpeed;
    if (by > y - 5 and (bx - x <= 30 and bx >= x))
    {
      UpOrDown = 0;
      ballSpeed++;
      points++;
    }
  }
}


void Win()
{
  if (points > '9')
  {
    lcd.fillScreen(BLACK);
    lcd.drawString(20, 80, "YOU WIN", YELLOW, 2);
    wait++;
    heart = 3;
  }
}

void Lose()
{
  lcd.fillScreen(BLACK);
  lcd.drawString(15, 80, "YOU LOSE", YELLOW, 2);
  wait++;
  heart = 3;
}

void resetGame()
{
  
// set base position
  x = 50;  ex = 50;
  y = 145; ey = 145;
  
// ball position
  bx = 64; ebx = 60;
  by = 30; eby = 30;
  
// random ball direction
  LeftOrRight = random(0,2); // 0 = left , 1 = right
  UpOrDown    = random(0,2); // 0 = up   , 1 = down

  wait = 0;
  points = '0';
  ballSpeed = 2;
  lcd.fillScreen(BLACK);
  createBoder();
}

void createBoder()
{
  lcd.drawRect    (0,0,128,160,RED);
  lcd.drawFastLine(0,1,128,RED,0);
  lcd.drawFastLine(0,158,128,RED,0);
  lcd.drawFastLine(1,0,160,RED,1);
  lcd.drawFastLine(126,0,160,RED,1);
  
  lcd.drawLine(0,0,20,0,BLUE);
  lcd.drawLine(0,1,20,1,BLUE);
  lcd.drawLine(108,0,128,0,BLUE);
  lcd.drawLine(108,1,128,1,BLUE);
  lcd.drawLine(0,159,20,159,BLUE);
  lcd.drawLine(0,158,20,158,BLUE);
  lcd.drawLine(108,159,128,159,BLUE);
  lcd.drawLine(108,158,128,158,BLUE);
  
  lcd.drawLine(0,0,0,20,BLUE);
  lcd.drawLine(1,1,1,20,BLUE);
  lcd.drawLine(126,0,126,20,BLUE);
  lcd.drawLine(127,0,127,20,BLUE);
  lcd.drawLine(0,139,0,159,BLUE);
  lcd.drawLine(1,139,1,159,BLUE);
  lcd.drawLine(126,139,126,159,BLUE);
  lcd.drawLine(127,139,127,159,BLUE);
}
