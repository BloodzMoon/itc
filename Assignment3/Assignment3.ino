#define D 2 
#define R 3
#define M 4
#define F 5
#define S 6
#define L 7
#define T 8
#define DD 9
#define speaker 13

int key[]={262,294,330,349,392,440,494,523};

void setup() {
  // put your setup code here, to run once:
  pinMode(D, INPUT_PULLUP);
  pinMode(R, INPUT_PULLUP);
  pinMode(M, INPUT_PULLUP);
  pinMode(F, INPUT_PULLUP);
  pinMode(S, INPUT_PULLUP);
  pinMode(L, INPUT_PULLUP);
  pinMode(T, INPUT_PULLUP);
  pinMode(DD, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(D)==LOW) 
  {
    tone(speaker, key[0]);
    delay(200);
    noTone(speaker);
  }
  if(digitalRead(R)==LOW) 
  {
    tone(speaker, key[1]);
    delay(200);
    noTone(speaker);
  }
  if(digitalRead(M)==LOW) 
  {
    tone(speaker, key[2]);
    delay(200);
    noTone(speaker);
  }
  if(digitalRead(F)==LOW) 
  {
    tone(speaker, key[3]);
    delay(200);
    noTone(speaker);
  }
  if(digitalRead(S)==LOW) 
  {
    tone(speaker, key[4]);
    delay(200);
    noTone(speaker);
  }
  if(digitalRead(L)==LOW) 
  {
    tone(speaker, key[5]);
    delay(200);
    noTone(speaker);
  }
  if(digitalRead(T)==LOW) 
  {
    tone(speaker, key[6]);
    delay(200);
    noTone(speaker);
  }
  if(digitalRead(DD)==LOW) 
  {
    tone(speaker, key[7]);
    delay(200);
    noTone(speaker);
  }
}
