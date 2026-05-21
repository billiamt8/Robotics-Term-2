#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
#include  <Toggle.h>

LiquidCrystal_I2C lcd(0x27,16,2);  

const int s0 = 4;
const int s1 = 2;
const int s2 = 12;
const int s3 = 13;
const int out = 8;

const int LED1G = 5;
const int LED1R = 6;
const int LED2R = 10;
const int LED2G = 11;
  
int RedMin = 0;
int RedMax = 0;
int GreenMin = 0;
int GreenMax = 0;

int RedPw = 0; 
int GreenPw = 0;

int RedValue = 0;
int GreenValue = 0;

const byte btnPin = 9;
byte code;
Toggle btnSw(btnPin);

long randNumber;

void setup()
{
  Serial.begin(115200);
  lcd.init();                      // initialize the lcd 
  lcd.backlight();

  
  pinMode(LED1G, OUTPUT);
  pinMode(LED1R, OUTPUT);
  pinMode(LED2R, OUTPUT);
  pinMode(LED2G, OUTPUT);

  //Colour sensor pins
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  //button
  btnSw.begin(btnPin);

  randomSeed(analogRead(0));

  digitalWrite(s0,HIGH);  //Putting S0/S1 on HIGH/HIGH levels means the output frequency scaling is at 100%
  digitalWrite(s1,LOW);  //LOW/LOW is off HIGH/LOW is 20% and LOW/HIGH is 2%
}

void loop()
{ 
  LCD();
  //ColourSensor();
  ButtonPress();
}
 
void ColourSensor()
{  
  GetColours();
  analogWrite(LED1R,map(RedValue,11,32,255,0));
  analogWrite(LED1G,map(GreenValue,15,40,255,0));
  analogWrite(LED2R,map(RedValue,11,32,255,0));
  analogWrite(LED2G,map(GreenValue,18,40,255,0));    

}

void GetColours(){
  RedValue = GetRed();
  //RedValue = map(Red,)
  delay(50);
  GreenValue = GetGreen();
  delay(50);

  Serial.print("red value = ");
  Serial.print(RedValue);
  Serial.print("green value = ");
  Serial.println(GreenValue);
}
int GetRed() 
  {
  digitalWrite(s2, LOW);        //S2/S3  define photodiodes LOW/LOW is for RED, LOW/HIGH is for Blue, HIGH/HIGH is for green
  digitalWrite(s3, LOW);
  int RedPw;
  RedPw = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);  
  return RedPw;
  }
int GetGreen(){
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  int GreenPw;
  GreenPw = pulseIn(out,  digitalRead(out) == HIGH ? LOW : HIGH);
  return GreenPw;
}


void LCD()
{
  lcd.setCursor(0,0);
  lcd.print("Press the button");
}

void ButtonPress() 
{
 if (btnSw.onChange() == 2) {
  Serial.println("release");
} else if (btnSw.onChange() == 1) {
  PrintRand();
} else {

}

}

void PrintRand() 
{
    randNumber = random(1, 7);
    Serial.println(randNumber);
    lcd.setCursor(0,1);
    lcd.print(String("Number is ") + String(randNumber));
}