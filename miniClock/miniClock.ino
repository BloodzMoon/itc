#include <LedControl.h>
#include <FontLEDClock.h>

#define speaker 3
#define changeMode 4
#define rightSwitch 5
#define leftSwitch 6

// Prototype =================================================================
void setLight(int, int, bool);
void clearScreen();
void printChar(int, int, char);
char numTOstr(int);


// Variables =================================================================
LedControl lc=LedControl(12,10,11,4);                   // DIN,CLK,CS,Number of LED Module
int  second = 56, minute = 22, hours = 5, selected=0;    //mode 1, 2
bool AMtoPM;
int  second2, minute2;                                  //mode 3
int  savedMinute = 23, savedHours = 5, selected2 = 0;    //mode 4
bool AMtoPM2, Alarm = false, firstAlarm = true;

unsigned short mode=1;
bool startWatch = false, blinked, firstShow = true;
unsigned long long changeModeDelay, rightSwitchDelay, leftSwitchDelay;


// Setup =====================================================================
void setup() 
{
  pinMode(changeMode,  INPUT_PULLUP);
  pinMode(rightSwitch, INPUT_PULLUP);
  pinMode(leftSwitch,  INPUT_PULLUP);
  pinMode(speaker,     OUTPUT      );
  
  //wake up device from saving power mode
  for (int i=0; i<4; i++)
  {
    lc.shutdown(i, false);
    lc.setIntensity(i, 8);
    lc.clearDisplay(i);
  }

  noInterrupts();           // disable all interrupts
  TCCR1A = 0; TCCR1B = 0;
  TCNT1 = 3036;             // preload timer
  TCCR1B |= (1 << CS12);    // 256 prescaler 
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
  interrupts();             // enable all interrupts
}


// Loop =======================================================================
void loop() 
{
  Serial.print(Alarm);
  
// Time Rules
  if (second >= 60) { second = 0; minute++; firstAlarm = true;}
  if (minute >= 60) { minute = 0; hours++;                    }
  if (hours  >= 13) { hours  = 0; AMtoPM = !AMtoPM;           }
  
  if (second2 == 60) { second2 = 0; minute2++; }

  if (savedMinute >= 60) { savedMinute = 0; savedHours++;      }
  if (savedHours  >= 13) { savedHours  = 0; AMtoPM2 = !AMtoPM2;}


// Change Mode
  if (digitalRead(changeMode)==0 and millis()-changeModeDelay>200)
  {
    changeModeDelay = millis();
    if (mode==4) mode = 1;
    else         mode++;
    firstShow = true;
    clearScreen();
  }


// ALL Mode ------

  //#####################
  if (mode==1) // Show Time
  {
    setLight( 0, 0, true); setLight( 0, 1, true); setLight( 1, 0, true); setLight( 1, 1, true); // show mode
    
    // AM/PM --------
    if (AMtoPM)
      { printChar(2, 4, 'P'); printChar(2, 8, 'M'); }
    else
      { printChar(2, 4, 'A'); printChar(2, 8, 'M'); }
      
    // Hours --------
    char firstDigitHours = numTOstr(hours/10);
    char lastDigitHours  = numTOstr(hours%10);
    printChar( 2, 13, firstDigitHours);
    printChar( 2, 17, lastDigitHours);

    // Minutes --------
    char firstDigitMinute = numTOstr(minute/10);
    char lastDigitMinute  = numTOstr(minute%10);
    printChar( 2, 23, firstDigitMinute);
    printChar( 2, 27, lastDigitMinute);
  }


  //#####################
  if (mode==2) // Set Time
  {
    setLight( 2, 0, true); setLight( 2, 1, true); setLight( 3, 0, true); setLight( 3, 1, true); // show mode

    // AM/PM --------
    if (AMtoPM)
      { printChar(2, 4, 'P'); printChar(2, 8, 'M'); }
    else
      { printChar(2, 4, 'A'); printChar(2, 8, 'M'); }
      
    // button event --------
    if (digitalRead(leftSwitch)==0 and millis()-leftSwitchDelay>100) // increase time
    {
      leftSwitchDelay = millis();
      if (selected==0) minute++;
      else hours++;
    }
    if (digitalRead(rightSwitch)==0 and millis()-rightSwitchDelay>200) // switch between minute and hours
    {
      rightSwitchDelay = millis();
      if (selected==0) selected = 1;
      else selected = 0;
    }

    // blink display ------
    if (selected == 0)
    {
      // Hours --------
      char firstDigitHours = numTOstr(hours/10);
      char lastDigitHours = numTOstr(hours%10);
      printChar( 2, 13, firstDigitHours);
      printChar( 2, 17, lastDigitHours);

      // Minutes --------
      char firstDigitMinute = numTOstr(minute/10);
      char lastDigitMinute = numTOstr(minute%10);
      printChar( 2, 23, firstDigitMinute);
      printChar( 2, 27, lastDigitMinute);
      delay(20);
      printChar( 2, 23, ' ');
      printChar( 2, 27, ' ');
    }
    else if (selected == 1)
    {
      /// Hours --------
      char firstDigitHours = numTOstr(hours/10);
      char lastDigitHours = numTOstr(hours%10);
      printChar( 2, 13, firstDigitHours);
      printChar( 2, 17, lastDigitHours);
      delay(20);
      printChar( 2, 13, ' ');
      printChar( 2, 17, ' ');

      // Minutes --------
      char firstDigitMinute = numTOstr(minute/10);
      char lastDigitMinute = numTOstr(minute%10);
      printChar( 2, 23, firstDigitMinute);
      printChar( 2, 27, lastDigitMinute);
    }
  }


  //#####################
  if (mode==3)
  {
    setLight( 4, 0, true); setLight( 4, 1, true); setLight( 5, 0, true); setLight( 5, 1, true); // show mode

    // button event --------
    if (digitalRead(rightSwitch)==0 and millis()-rightSwitchDelay>200)
    {
      rightSwitchDelay = millis();
      startWatch = !startWatch;
    }
    if (digitalRead(leftSwitch)==0 and millis()-leftSwitchDelay>200)
    {
      leftSwitchDelay = millis();
      startWatch = false;
      second2 = 0;
      minute2 = 0;
      firstShow = true;
    }

    // Dot -----------
    if (startWatch)
    {
      setLight( 6, 16, blinked);
      delay(50);
      blinked = !blinked;
    }
    else setLight( 6, 16, true);

    // fix display not show when startup
    if (firstShow)
    {
      // Minutes --------
      char firstDigitMinute2 = numTOstr(minute2/10);
      char lastDigitMinute2 = numTOstr(minute2%10);
      printChar( 2, 8, firstDigitMinute2);
      printChar( 2, 12, lastDigitMinute2);

      // Second --------
      char firstDigitSecond2 = numTOstr(second2/10);
      char lastDigitSecond2 = numTOstr(second2%10);
      printChar( 2, 18, firstDigitSecond2);
      printChar( 2, 22, lastDigitSecond2);

      firstShow = false;
    }
  }

  //#####################
  if (mode==4) // Set Alarm
  {
    setLight( 6, 0, true); setLight( 6, 1, true); setLight( 7, 0, true); setLight( 7, 1, true); // show time
    
    // AM/PM --------
    if (AMtoPM2)
      { printChar(2, 4, 'P'); printChar(2, 8, 'M'); }
    else
      { printChar(2, 4, 'A'); printChar(2, 8, 'M'); }

    // button event
    if (digitalRead(leftSwitch)==0 and millis()-leftSwitchDelay>100)
    {
      leftSwitchDelay = millis();
      if (selected2==0) savedMinute++;
      else savedHours++;
    }
    if (digitalRead(rightSwitch)==0 and millis()-rightSwitchDelay>200)
    {
      rightSwitchDelay = millis();
      if (selected2==0) selected2 = 1;
      else selected2 = 0;
    }

    // blink display
    if (selected2 == 0)
    {
      // Hours --------
      char firstDigitHours = numTOstr(savedHours/10);
      char lastDigitHours = numTOstr(savedHours%10);
      printChar( 2, 13, firstDigitHours);
      printChar( 2, 17, lastDigitHours);

      // Minutes --------
      char firstDigitMinute = numTOstr(savedMinute/10);
      char lastDigitMinute = numTOstr(savedMinute%10);
      printChar( 2, 23, firstDigitMinute);
      printChar( 2, 27, lastDigitMinute);
      delay(20);
      printChar( 2, 23, ' ');
      printChar( 2, 27, ' ');
    }
    else if (selected2 == 1)
    {
      /// Hours --------
      char firstDigitHours = numTOstr(savedHours/10);
      char lastDigitHours = numTOstr(savedHours%10);
      printChar( 2, 13, firstDigitHours);
      printChar( 2, 17, lastDigitHours);
      delay(20);
      printChar( 2, 13, ' ');
      printChar( 2, 17, ' ');

      // Minutes --------
      char firstDigitMinute = numTOstr(savedMinute/10);
      char lastDigitMinute = numTOstr(savedMinute%10);
      printChar( 2, 23, firstDigitMinute);
      printChar( 2, 27, lastDigitMinute);
    }
  }

  // Alarm !!!
  if (minute==savedMinute and hours==savedHours and AMtoPM==AMtoPM2 and firstAlarm)
  {
    Alarm = true;
    mode = 1;
    firstShow = true;
    clearScreen();
  }
  if (Alarm)
  {
    tone(speaker,700);
    if(digitalRead(changeMode)==0)
      { noTone(speaker); Alarm = false; firstAlarm = false;}
  }
    
}


// Function ====================================================================
void setLight(int y, int x, bool lightUP) 
{
   // (y,x)
   // (0,0) ... (0,31)   LED position
   //  ...        ...
   // (7,0) ... (7,31)
   //select which module depending on the x coord
   
  int module;
  if (x >= 0 && x <= 7)   { module = 3; }
  if (x >= 8 && x <= 15)  { module = 2; x = x - 8; }
  if (x >= 16 && x <= 23) { module = 1; x = x - 16;}
  if (x >= 24 && x <= 31) { module = 0; x = x - 24;}

  if (lightUP) 
    lc.setLed(module, y, x, true);
  else 
    lc.setLed(module, y, x, false);
}

void clearScreen() 
{
  for (int module = 0; module < 4; module++)
    lc.clearDisplay(module);
}

void printChar(int y, int x, char c)
{
  int dots;
  if ((c >= 'A' && c <= 'Z') or (c >= 'a' && c <= 'z') ) 
    c &= 0x1F;  // A-Z maps to 1-26 
  else if (c >= '0' && c <= '9') 
    c = (c - '0') + 32;
  else if (c == ' ') 
    c = 0;      // space 
  else if (c == '.') 
    c = 27;     // full stop 
  else if (c == ':') 
    c = 28;     // colon 
  else if (c == '\'')
    c = 29;     // single quote mark 
  else if (c == '!')
    c = 30;     // single quote mark 
  else if (c == '?') 
    c = 31;     // single quote mark 

  for (int col = 0; col < 3; col++) {
    dots = pgm_read_byte_near(&mytinyfont[c][col]);
    for (int row = 0; row < 5; row++) {
      if (dots & (16 >> row))
        setLight(y + row, x + col, true);
      else
        setLight(y + row, x + col, false);
    }
  }
}

char numTOstr(int num)
{
  if (num == 0) return '0';
  else if (num == 1) return '1';
  else if (num == 2) return '2';
  else if (num == 3) return '3';
  else if (num == 4) return '4';
  else if (num == 5) return '5';
  else if (num == 6) return '6';
  else if (num == 7) return '7';
  else if (num == 8) return '8';
  else if (num == 9) return '9';
}

ISR(TIMER1_OVF_vect)        
{
  TCNT1 = 3036;   // preload timer 65536-16MHz/256/1Hz
  Serial.begin(9600);
  Serial.println(second++);
  
  if (mode==1)
  {
    // Second -----------
    if (second%2==0)
    { setLight( 3, 21, true); setLight( 5, 21, true); }
    else
    { setLight( 3, 21, false); setLight( 5, 21, false); }
  }

  if (startWatch)
  {
    second2++;
    if (mode==3)
    {
      // Minutes --------
      char firstDigitMinute2 = numTOstr(minute2/10);
      char lastDigitMinute2 = numTOstr(minute2%10);
      printChar( 2, 8, firstDigitMinute2);
      printChar( 2, 12, lastDigitMinute2);

      // Second --------
      char firstDigitSecond2 = numTOstr(second2/10);
      char lastDigitSecond2 = numTOstr(second2%10);
      printChar( 2, 18, firstDigitSecond2);
      printChar( 2, 22, lastDigitSecond2);
    }
  }
    
}
