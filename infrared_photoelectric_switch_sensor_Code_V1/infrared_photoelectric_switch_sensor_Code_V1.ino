#include "Timer.h"
#define F_Sensor 13
#define B_Sensor 12
#define led 8
Timer Ft;
Timer Bt;
int i = 0 ;
int ReadSenD1 = 0; //อ่านขา D2
int ReadSenD2 = 0; //อ่านขา D2
int front = 0; ////เซ็นเซอร์ตัวหน้า
int back = 0; //เซ็นเซอร์ตัวหลัง
int statusOpen = 0; //เช็คค่าขาเข้า
int statusClose = 0; //เช็คค่าขาออก
int P_count; //จำนวณคน

void setup() {
  pinMode( F_Sensor , INPUT ); //กำหนดขา D1 ให้เป็นขาเข้า
  pinMode( B_Sensor , INPUT ); //กำหนดขา D2 ให้เป็นขาเข้า
  pinMode( led , OUTPUT ); //กำหนดขา D1 ให้เป็นขาเข้า
  //pinMode( Sensor, INPUT_PULLUP);
  Serial.begin( 9600 ); //กำหนดบอร์ดเรท

  Serial.println ( "-----------------------------------------------------" );
}

void loop() {
  ReadSenD1 = digitalRead( F_Sensor ); //อ่าน ลอจิกจากขา D1
  ReadSenD2 = digitalRead( B_Sensor ); //อ่าน ลอจิกจากขา D2
  //Serial.println( "หลอด 1" );
  //Serial.println( ReadSenD1 );
  //Serial.println( "หลอด 2" );
  //Serial.println( ReadSenD2 );
  checkSensor();

  delay(150);
}

void checkSensor() {
  if ( ReadSenD1 == 0 && ReadSenD2 == 1 && front == 0) {
    front = 1;
    //Serial.println( "print front" );
    Serial.println( front );
  }
  if (ReadSenD2 == 0 && ReadSenD1 == 1 && back == 0) {
    back = 1;
    //Serial.println( "print back" );
    Serial.println( back );
  }
  //======================================================การเพิ่มค่าตอนเข้า============================================
  if ( front == 1 && back == 0 ) {
    Serial.println( "front = 1 ");
    statusOpen = 1;
    Ft.every(1000, i++);

  }
  if ( back == 1 && statusOpen == 1 && i <= 10 ) {
    Serial.println( "Open" );
    delay(500);
    digitalWrite( led , HIGH );
    P_count = P_count + 1;
    Serial.print( "People : " );
    Serial.println( P_count );
    front = 0;
    back = 0;
    statusOpen = 0;
  }
  //======================================================การลดค่าตอนออก============================================
  if ( back == 1 && front == 0 ) {
    Serial.println( "back = 1 ");
    statusClose = 1;
    Bt.every(1000, i++);
  }
  if ( front == 1 && statusClose == 1 && i <= 10 ) {
    delay(500);
    if ( P_count > 0 ) {
      P_count = P_count - 1;
    }
    Serial.print( "People : " );
    Serial.println( P_count );
    if ( P_count == 0) {
      Serial.println( "Close" );
      digitalWrite( led , LOW );
    }
    front = 0;
    back = 0;
    statusClose = 0;
  }
  if ( i > 10 ) {
    i = 0 ;
    front = 0 ;
    back = 0;
    statusOpen = 0;
    statusClose = 0;
  }
}
