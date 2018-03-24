#include <LiquidCrystal.h>


//key input pins
short int btn_1 = A0;
short int btn_2 = A1;
short int btn_3 = A2;
short int btn_4 = A3;
short int btn_5 = A4;
short int btn_6 = A5;
short int btn_7 = A6;
short int btn_8 = A7;
short int btn_9 = 8;
short int btn_0 = 9;

//signal output pin
short int sig_led = 13;
short int sig_beeb = 10;
short int sig_unused= 6;
short int sig_trigger = 7;

//key state to only trigger on LOW to HIGH
short int btn_1_state = LOW;
short int btn_2_state = LOW;
short int btn_3_state = LOW;
short int btn_4_state = LOW;
short int btn_5_state = LOW;
short int btn_6_state = LOW;
short int btn_7_state = LOW;
short int btn_8_state = LOW;
short int btn_9_state = LOW;
short int btn_0_state = LOW;

//keyword 
short int keyword_length = 4;
String keyword = "";

//countdown constants
short int countdown_seconds = 0;
short int countdown_minutes = 5;


// initialize lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() 
{
  //pinMode(btn_9, INPUT);
  //pinMode(btn_0, INPUT);
  pinMode(sig_led, OUTPUT);
  pinMode(sig_beeb, OUTPUT);
  pinMode(sig_unused, OUTPUT);
  pinMode(sig_trigger, OUTPUT);

  lcd.begin(16, 2);
}

short int getPressedButton()
{
  short int btn = -1;
  
  if(digitalRead(btn_0) && btn_0_state != HIGH) 
  {
    btn = 0;
    btn_0_state = HIGH;
  }
  else if(analogRead(btn_1)>500 && btn_1_state != HIGH) 
  {
    btn = 1;
    btn_1_state = HIGH;
  }
  else if(analogRead(btn_2)>500 && btn_2_state != HIGH)
  {
    btn = 2;
    btn_2_state = HIGH;
  }
  else if(analogRead(btn_3)>500 && btn_3_state != HIGH)
  {
    btn = 3;
    btn_3_state = HIGH;
  }
  else if(analogRead(btn_4)>500 && btn_4_state != HIGH)
  {
    btn = 4;
    btn_4_state = HIGH;
  }
  else if(analogRead(btn_5)>500 && btn_5_state != HIGH)
  {
    btn = 5;
    btn_5_state = HIGH;
  }
  else if(analogRead(btn_6)>500 && btn_6_state != HIGH)
  {
    btn = 6;
    btn_6_state = HIGH;
  }
  else if(analogRead(btn_7)>500 && btn_7_state != HIGH)
  {
    btn = 7;
    btn_7_state = HIGH;
  }
  else if(analogRead(btn_8)>500 && btn_8_state != HIGH)
  {
    btn = 8;  
    btn_8_state = HIGH;
  }
  else if(digitalRead(btn_9) && btn_9_state != HIGH)
  {
    btn = 9;
    btn_9_state = HIGH;
  }

  if(!digitalRead(btn_0) && btn_0_state == HIGH) 
  {
    btn_0_state = LOW;
  }
  if(analogRead(btn_1)<300  && btn_1_state == HIGH) 
  {
    btn_1_state = LOW;
  }
  if(analogRead(btn_2)<300 && btn_2_state == HIGH)
  {
    btn_2_state = LOW;
  }
  if(analogRead(btn_3)<300 && btn_3_state == HIGH)
  {
    btn_3_state = LOW;
  }
  if(analogRead(btn_4)<300 && btn_4_state == HIGH)
  {
    btn_4_state = LOW;
  }
  if(analogRead(btn_5)<300 && btn_5_state == HIGH)
  {
    btn_5_state = LOW;
  }
  if(analogRead(btn_6)<300 && btn_6_state == HIGH)
  {
    btn_6_state = LOW;
  }
  if(analogRead(btn_7)<300 && btn_7_state == HIGH)
  {
    btn_7_state = LOW;
  }
  if(analogRead(btn_8)<300 && btn_8_state == HIGH)
  {
    btn_8_state = LOW;
  }
  if(!digitalRead(btn_9) && btn_9_state == HIGH)
  {
    btn_9_state = LOW;
  }

  return btn;
}

void plantBomb()
{ 
  lcd.clear();
  
  //promt keyword 
  lcd.setCursor(0, 0);
  lcd.print("PLANT (" + String(keyword_length) + " DIGITS)");
  lcd.setCursor(0, 1);

  digitalWrite(sig_beeb, HIGH);
  delay(80);
  digitalWrite(sig_beeb, LOW);
  delay(80);
  digitalWrite(sig_beeb, HIGH);
  delay(80);
  digitalWrite(sig_beeb, LOW);
        
  //reset keyword
  keyword = "";
  short int key_count = 0;

  //map keys to keyword position
  while(key_count < keyword_length)
  {
    short int btn = getPressedButton();
    if(btn>=0)
    {
      lcd.print(btn);
      keyword += String(btn);
      key_count ++;
    }
    
  }

  delay(500);
  
  //hide keyword
  lcd.setCursor(0, 1);
  for(int i = 0; i<keyword_length; i++)
  {
    lcd.print("*");
  }
}

bool defuseBomb()
{
  lcd.clear();
  
  //promt keyword 
  lcd.setCursor(0, 0);
  lcd.print("DEFUSE");
  //hide keyword
  lcd.setCursor(0, 1);
  for(int j = 0; j<keyword_length; j++)
  {
    lcd.print("*");
  }
  lcd.setCursor(0, 1);

  unsigned long countdown = countdown_seconds*1000 + countdown_minutes*60000;
  unsigned long timer = 0;
  
  short int sig_state = LOW;

  while (true)
  {
    int i = 0;
    
    while (i < keyword_length)
    {   
      delay(10);
      countdown -= 10;
      timer += 10;

      if ( (timer*100 >= countdown || timer >= 1500) && sig_state == LOW)
      {
        sig_state = HIGH;

        digitalWrite(sig_led, sig_state);
        digitalWrite(sig_beeb, sig_state);

        timer = 0;
      }
      if ( (timer*100 >= countdown || timer >= 200) && sig_state == HIGH)
      {
          sig_state = LOW;

        digitalWrite(sig_led, sig_state);
        digitalWrite(sig_beeb, sig_state);

        timer = 0;
      }

      if (countdown <= 0)
      {
        digitalWrite(sig_led, LOW);
        digitalWrite(sig_beeb, LOW);
        return false;
      }
    
      
      String tmp = "";
      tmp += keyword.charAt(i);
      short int val = tmp.toInt();
  
      short int btn = getPressedButton();
      if(btn == val)
      {
        lcd.print(btn);
        i++;
      }
      else if (btn >= 0)
      {
        //hide keyword
        lcd.setCursor(0, 1);
        for(int j = 0; j<keyword_length; j++)
        {
          lcd.print("*");
        }
        lcd.setCursor(0, 1);
        break;
      }
    }

    if(i == keyword_length) 
    {
      digitalWrite(sig_led, LOW);
      digitalWrite(sig_beeb, LOW);
      return true;
    }
  }
}

void triggerResult(bool trigger)
{
  lcd.clear();
  
  if(trigger)
  {
    lcd.setCursor(0, 0);
    lcd.print("BOMB DEFUSED");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("BOMB DETONATED");

    /*
    digitalWrite(sig_trigger, HIGH);
    delay(500);
    digitalWrite(sig_trigger, LOW);
    */
  }
}

void loop() 
{
  plantBomb();
  
  delay(500);
  
  bool result = defuseBomb();

  delay(500);
  
  triggerResult(result);

  while(true)
  {
    delay(1000);
  }
}

