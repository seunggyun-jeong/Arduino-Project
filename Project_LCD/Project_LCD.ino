#include <SoftwareSerial.h>
SoftwareSerial xbee(4,5);
#include <TimerOne.h>

unsigned long off_time = 0;
unsigned long current_time = 0;

const int BUTTON_INT = 0;

//LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(6, 7, 8, 9, 10, 11);

String data;

//O 모양 정의
byte degree[8]={
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
};

int i = 1;

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);
  lcd.begin(16,2);

  lcd.createChar(0, degree);

  lcd.setCursor(0,1);
  lcd.print("Current:");
  lcd.setCursor(10,1);
  lcd.write((byte)0);
  
  lcd.setCursor(11,1);
  lcd.print("C");
  
  lcd.setCursor(0,0);
  lcd.print("SeungGyun's LCD");

  attachInterrupt(BUTTON_INT, send_Button_Signal, RISING);

}


void print_temp(){
  data=xbee.read();
  //Serial.println(data);
  lcd.setCursor(8,1);
  lcd.print(data);
  off_time = millis() + 1000;
}

void send_Button_Signal() {
  xbee.write('$');
}

void loop() {
  if(xbee.available()){
    print_temp();
  }
  
  current_time = millis();

  if(off_time <= current_time){
    lcd.setCursor(8,1);
    lcd.print("  ");
  }
}
