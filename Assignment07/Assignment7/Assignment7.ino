#define way1R 5
#define way1Y 6
#define way1G 7

#define way2R 8
#define way2Y 9
#define way2G 10

#define Walk   11
#define noWalk 12

#define walkIN 2
#define way1IN 3
#define way2IN 4

// Index ---------------
#define way1  0    
#define wait1 1   
#define way2  2   
#define wait2 3  
#define walk  4    
#define waitW 5   
// -------------------------------
struct state
{ unsigned long out ;
  unsigned long Time;
  unsigned long next[8];
};
typedef const struct state sType ;

sType FSM[7] =
{
  {B00110010, 2000, {way1  , wait1 , wait1 , wait1 , way1  , wait1 , wait1 , wait1 }},
  {B01010010, 1000, {way1  , walk  , way2  , way2  , way2  , walk  , way2  , way2  }},
  {B10000110, 2000, {way2  , wait2 , way2  , wait2 , wait2 , wait2 , wait2 , wait2 }},
  {B10001010, 1000, {way2  , walk  , way2  , walk  , way1  , way1  , way1  , walk  }},
  {B10010001, 2000, {walk  , walk  , 6     , 6     , 6     , 6     , 6     , 6     }},
  {B10010001, 1000, {waitW , way1  , way2  , way2  , way1  , way1  , way1  , way1  }},
  {B10010000, 300 , {5     , 5     , 5     , 5     , 5     , 5     , 5     , 5     }}
};

// -----------------------------------
void setup() 
{
  pinMode(way1R , OUTPUT);
  pinMode(way1Y , OUTPUT);
  pinMode(way1G , OUTPUT);
  
  pinMode(way2R , OUTPUT);
  pinMode(way2Y , OUTPUT);
  pinMode(way2G , OUTPUT);

   pinMode(Walk  , OUTPUT);
  pinMode(noWalk, OUTPUT);
  
  pinMode(walkIN, INPUT_PULLUP);
  pinMode(way1IN, INPUT_PULLUP);
  pinMode(way2IN, INPUT_PULLUP);
  
 

}
unsigned long s = way1;
unsigned long  input, input1, input2, input3;

void loop() 
{
  digitalWrite (way1R , !(FSM[s].out & B10000000));
  digitalWrite (way1Y , !(FSM[s].out & B01000000));
  digitalWrite (way1G , !(FSM[s].out & B00100000));
  digitalWrite (way2R , !(FSM[s].out & B00010000));
  digitalWrite (way2Y , !(FSM[s].out & B00001000));
  digitalWrite (way2G , !(FSM[s].out & B00000100));
  digitalWrite (noWalk, !(FSM[s].out & B00000010));
  digitalWrite (Walk  , !(FSM[s].out & B00000001));


  delay(FSM[s].Time);
  input1 = !digitalRead(walkIN);
  input2 = !digitalRead(way1IN);
  input3 = !digitalRead(way2IN);
  input  = (input1 * 4)  + (input2 * 2)  + input3;

  s = FSM[s].next[input];

}
