#include <SoftwareSerial.h>
#include <Wire.h>
SoftwareSerial xbee(4,5);

const int BUTTON_INT = 0;
const int SPEAKER = 8;

unsigned long off_time = 0;
unsigned long current_time = 0;

int temp = 0;

char data;

int temp_address=72;

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);
  Wire.begin();

  //인터럽트 발생 시 데이터 송신
  attachInterrupt(BUTTON_INT, send_Data, RISING);
}



void read_Temp(){
  Wire.beginTransmission(temp_address);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(temp_address, 1);

  while(Wire.available()==0);
  temp = Wire.read();
}


void send_Data(){
  Serial.println(temp);
  xbee.write(temp);
  
}

void Buzz(){
  tone(SPEAKER,131);
  off_time = millis() + 1000;
}

void loop() {
  //온도 값 읽기
  read_Temp();
  if(xbee.available()){
    data = xbee.read();
    if(data == '$')
      Buzz();
  }

  current_time = millis();

  if(off_time <= current_time){
    noTone(SPEAKER);
  }

}
