#include "Timer.h"    //ประกาศ header file 
#define F_Sensor 13   //ประกาศตัวแปร ชื่อ F_Sensor ให้เป็นขาที่ 13 
#define B_Sensor 12   //ประกาศตัวแปร ชื่อ B_Sensor ให้เป็นขาที่ 12 
#define led 8         //ประกาศตัวแปร ชื่อ led ให้เป็นขาที่ 8
Timer Ft;             //ประกาศตัวแปร ของ Timer ชื่อ Ft
Timer Bt;             //ประกาศตัวแปร ของ Timer ชื่อ Ft
int i = 0 ;           //ประกาศตัวแปร
int ReadSenD1 = 0;    //อ่านขา 13
int ReadSenD2 = 0;    //อ่านขา 12
int front = 0;        //เซ็นเซอร์ตัวหน้า
int back = 0;         //เซ็นเซอร์ตัวหลัง
int statusOpen = 0;   //เช็คค่าขาเข้า
int statusClose = 0;  //เช็คค่าขาออก
int P_count;          //จำนวณคน

void setup() {
  pinMode( F_Sensor , INPUT );  //กำหนดขา D1 ให้เป็นขาเข้า
  pinMode( B_Sensor , INPUT );  //กำหนดขา D2 ให้เป็นขาเข้า
  pinMode( led , OUTPUT );      //กำหนดขา D1 ให้เป็นขาเข้า
  Serial.begin( 9600 );         //กำหนดบอร์ดเรท
  Serial.println ( "-----------------------------------------------------" ); //แสดงข้อความ บน Serial Monitor
}

void loop() {
  ReadSenD1 = digitalRead( F_Sensor );  //อ่าน ลอจิกจากตัวแปร F_Sensor
  ReadSenD2 = digitalRead( B_Sensor );  //อ่าน ลอจิกจากตัวแปร B_Sensor
  checkSensor();  //เรียกใช้ฟังก์ชั่น
  //delay(150);     //กำหนดค่าดีเลย์
}

void checkSensor() { //สร้างฟังก์ชั่น
  if ( ReadSenD1 == 1 && ReadSenD2 == 0 && front == 0) { //สร้างเงื่อนไข
    front = 1;               //กำหนดให้ front มีค่าเป็น 1
    Serial.println( front ); //แสดงค่าของ front บน Serial Monitor
  } //จบเงื่อนไข
  if (ReadSenD2 == 1 && ReadSenD1 == 0 && back == 0) { //สร้างเงื่อนไข
    back = 1;               //กำหนดให้ back มีค่าเป็น 1
    Serial.println( back ); //แสดงค่าของ back บน Serial Monitor
  } //จบเงื่อนไข

  //======================================================การเพิ่มค่าตอนเข้า============================================//

  if ( front == 1 && back == 0 ) { //สร้างเงื่อนไข
    Serial.println( "front = 1 ");
    statusOpen = 1;       //กำหนดให้ statusOpen มีค่าเป็น 1
    Ft.every(1000, i++);  //กำหนดให้ทุกๆ 1วินาที จะให้ ตัวแปร i เพิ่มค่าทีละ 1
  } //จบเงื่อนไข
  if ( back == 1 && statusOpen == 1 && i <= 60 ) { //สร้างเงื่อนไข
    Serial.println( "Open" );         //แสดงข้อความ บน Serial Monitor
    //delay(500);                       //กำหนดค่าดีเลย์
    digitalWrite( led , HIGH );       //ให้ led ติด
    P_count = P_count + 1;            //ให้ตัวแปร P_count บวก 1
    Serial.print( "People : " );      //แสดงข้อความ บน Serial Monitor
    Serial.println( P_count );        //แสดงค่าของ P_count บน Serial Monitor
    front = 0;                        //กำหนดค่าของ front เป็น 0
    back = 0;                         //กำหนดค่าของ back เป็น 0
    statusOpen = 0;                   //กำหนดค่าของ statusOpen เป็น 0
  } //จบเงื่อนไข
  //======================================================การลดค่าตอนออก============================================//
  if ( back == 1 && front == 0 ) { //สร้างเงื่อนไข
    Serial.println( "back = 1 ");     //แสดงข้อความ บน Serial Monitor
    statusClose = 1;                  //กำหนดค่าของ statusClose เป็น 1
    Bt.every(1000, i++);              //กำหนดให้ทุกๆ 1วินาที จะให้ ตัวแปร i เพิ่มค่าทีละ 1
  } //จบเงื่อนไข
  if ( front == 1 && statusClose == 1 && i <= 60 ) { //สร้างเงื่อนไข
    //delay(500);                       //กำหนดค่าดีเลย์
    if ( P_count > 0 ) { //สร้างเงื่อนไข
      P_count = P_count - 1;          //ให้ตัวแปร P_count ลบ 1
    } //จบเงื่อนไข
    Serial.print( "People : " );      //แสดงข้อความ บน Serial Monitor
    Serial.println( P_count );        //แสดงค่าของ P_count บน Serial Monitor
    if ( P_count == 0) { //สร้างเงื่อนไข
      Serial.println( "Close" );      //แสดงข้อวคาม บน Serial Monitor
      digitalWrite( led , LOW );      //ให้ led ดับ
    } //จบเงื่อนไข
    front = 0;                        //กำหนดค่าของ front เป็น 0
    back = 0;                         //กำหนดค่าของ back เป็น 0
    statusClose = 0;                  //กำหนดค่าของ statusClose เป็น 0
  } //จบเงื่อนไข
  if ( i > 60 ) { //สร้างเงื่อนไข
    i = 0 ;                           //กำหนดค่าของ i เป็น 0
    front = 0 ;                       //กำหนดค่าของ front เป็น 0
    back = 0;                         //กำหนดค่าของ back เป็น 0
    statusOpen = 0;                   //กำหนดค่าของ statusOpen เป็น 0
    statusClose = 0;                  //กำหนดค่าของ statusClose เป็น 0
  } //จบเงื่อนไข
} //จบฟังก์ชั่น
