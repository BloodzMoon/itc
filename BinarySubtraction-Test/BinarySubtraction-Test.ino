#define sw1 13   // bit left
#define sw2 12   // bit mid
#define sw3 11   // bit right
#define sw4 10   // input button

#define g 7      // sign bit
#define r 4      // bit left
#define y 5      // bit mid
#define b 6      // bit right

#define wait 3   // decorate Light


////////////// Variables ////////////////////////
unsigned long long debounce = 0;
int inputState = 1;
bool num1[4], num2[4], result[4];
bool keep = 0;


////////////// Setup ///////////////////////////
void setup()
{
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
  pinMode(sw3, INPUT_PULLUP);
  pinMode(sw4, INPUT_PULLUP);

  pinMode(g, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(y, OUTPUT);
  pinMode(b, OUTPUT);

  pinMode(wait, OUTPUT);
  Serial.begin(9600);
}


/////////// Main loop /////////////////////////////////
void loop()
{

  // Show
  Serial.print(num1[0]); Serial.print(num1[1]); Serial.print(num1[2]); Serial.print(num1[3]); if (inputState == 1 or inputState == 2) Serial.print(" - "); else Serial.print(" + ");
  Serial.print(num2[0]); Serial.print(num2[1]); Serial.print(num2[2]); Serial.print(num2[3]); Serial.print(" = ");
  Serial.print(result[0]); Serial.print(result[1]); Serial.print(result[2]); Serial.println(result[3]);

  // bit Input
  if (inputState == 1 or inputState == 2)
  {
    // bit left
    if (digitalRead(sw1) == LOW)
    {
      digitalWrite(r, HIGH);
      if (inputState == 1) num1[1] = 1;
      else if (inputState == 2) num2[1] = 1;
    }
    else if (digitalRead(sw1) == HIGH)
    {
      digitalWrite(r, LOW);
      if (inputState == 1) num1[1] = 0;
      else if (inputState == 2) num2[1] = 0;
    }

    // bit mid
    if (digitalRead(sw2) == LOW)
    {
      digitalWrite(y, HIGH);
      if (inputState == 1) num1[2] = 1;
      else if (inputState == 2) num2[2] = 1;
    }
    else if (digitalRead(sw2) == HIGH)
    {
      digitalWrite(y, LOW);
      if (inputState == 1) num1[2] = 0;
      else if (inputState == 2) num2[2] = 0;
    }

    // bit right
    if (digitalRead(sw3) == LOW)
    {
      digitalWrite(b, HIGH);
      if (inputState == 1) num1[3] = 1;
      else if (inputState == 2) num2[3] = 1;
    }
    else if (digitalRead(sw3) == HIGH)
    {
      digitalWrite(b, LOW);
      if (inputState == 1) num1[3] = 0;
      else if (inputState == 2) num2[3] = 0;
    }

    // Input button
    if (digitalRead(sw4) == LOW and millis() - debounce > 300)
    {
      debounce = millis();
      if (inputState == 1) inputState = 2;
      else if (inputState == 2) inputState = 3;
    }
  }

  // blink!!
  if (inputState == 3)
  {
    digitalWrite(r, LOW); digitalWrite(y, LOW); digitalWrite(b, LOW);
    digitalWrite(wait, HIGH); delay(100); digitalWrite(wait, LOW); delay(100);
    digitalWrite(wait, HIGH); delay(100); digitalWrite(wait, LOW); delay(100);
    digitalWrite(wait, HIGH); delay(100); digitalWrite(wait, LOW); delay(1000);
    inputState = 4;
  }
  // calculate
  else if (inputState == 4)
  {
    //////// two complement the second number ///////////////////
    for (int i = 3; i >= 0; i--)
    {
      if (num2[i] == 1)
      {
        while (i > 0)
        {
          num2[i - 1] = !num2[i - 1];
          i--;
        }
      }
    }

    ////// calculate /////////////////
    for (int i = 3; i >= 0; i--)
    {
      if (keep == 0)
      {
        if (num1[i] == num2[i] and num1[i] == 0) result[i] = 0;
        else if (num1[i] == num2[i] and num1[i] == 1)
        {
          result[i] = 0;
          keep = 1;
        }
        else if (num1[i] != num2[i]) result[i] = 1;
      }
      else if (keep == 1)
      {
        if (num1[i] == num2[i] and num1[i] == 0)
        {
          result[i] = 1;
          keep = 0;
        }
        else if (num1[i] == num2[i] and num1[i] == 1)
        {
          result[i] = 1;
          keep = 1;
        }
        else if (num1[i] != num2[i])
        {
          result[i] = 0;
          keep = 1;
        }
      }
    }

    inputState = 5;
  }

  // show result
  if (inputState == 5)
  {
    if (result[0] == 1) digitalWrite(g, HIGH);
    if (result[1] == 1) digitalWrite(r, HIGH);
    if (result[2] == 1) digitalWrite(y, HIGH);
    if (result[3] == 1) digitalWrite(b, HIGH);

    // reset
    if (digitalRead(sw4) == LOW)
    {
      digitalWrite(g, LOW); digitalWrite(r, LOW); digitalWrite(y, LOW); digitalWrite(b, LOW);
      digitalWrite(wait, HIGH); delay(100); digitalWrite(wait, LOW); delay(100);
      digitalWrite(wait, HIGH); delay(100); digitalWrite(wait, LOW); delay(100);
      digitalWrite(wait, HIGH); delay(100); digitalWrite(wait, LOW); delay(1000);
      inputState = 1;
      keep = 0;
      for (int i = 0; i < 4; i++)
      {
        result[i] = 0; num1[i] = 0; num2[i] = 0;
      }
    }
  }

}
