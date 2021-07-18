/* Librarys Definitions */
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

/* LCD Objects Definitions */
LiquidCrystal_I2C lcd(0x27, 16, 2);

/* Pin Definitions */
#define Button 2
#define Potasiometer_R A0
#define Potasiometer_G A1
#define Potasiometer_B A2
#define Led_R 9
#define Led_G 10
#define Led_B 11
#define Buzzer 3
#define Bluetooth_RX 6  
#define Bluetooth_TX 7
#define SCL A5
#define SDA A4

/* Bluetooth Objects Definitions */
SoftwareSerial Bluetooth(Bluetooth_RX,Bluetooth_TX); 

/* Veriables Definitions */
int ButtonState=0;
int ValueR=0;
int ValueG=0;
int ValueB=0;
int Counter1 = 0; 
int Counter2 = 0;
int Counter3 = 0;
int DelayTime= 10;
char Data;

void setup()
{
  /* GPIO Configrations*/
pinMode(Led_R,OUTPUT);
pinMode(Led_G,OUTPUT);
pinMode(Led_B,OUTPUT);
pinMode(Buzzer,OUTPUT);

/* Bluetooth Configrations */
Bluetooth.begin(9600);

/* External İnterrupt Configrations */
attachInterrupt(0, ButtonFunction, RISING);

/* The leds are off at the start time */
analogWrite(Led_R,255);
analogWrite(Led_G,255);
analogWrite(Led_B,255);

/* Serial Communications Configrations*/
Serial.begin(9600);

/* LCD Configrations */
 lcd.begin();
 lcd.backlight();
 lcd.home();
}

void loop() 
{
  /* Evaluate Menu States According to the Button States */
  while(ButtonState==0)
  {
  lcd.setCursor(0,0);
  lcd.print("*  STATIK LED  *");
  lcd.setCursor(0,1);
  lcd.print("*     MODU     *");

  /* Convertion of size */
  ValueR=map(analogRead(Potasiometer_R),0,1023,0,255);
  ValueG=map(analogRead(Potasiometer_G),0,1023,0,255);
  ValueB=map(analogRead(Potasiometer_B),0,1023,0,255);

/* for the preventing arc of potansiometer */
  if(ValueR <= 20){
    ValueR=0;
  }
   if(ValueG <= 20){
    ValueG=0;
  }
   if(ValueB <= 20){
    ValueB=0;
  }

   /* LOGIC HIGH */
  analogWrite(Led_R,ValueR);
  analogWrite(Led_G,ValueG);
  analogWrite(Led_B,ValueB);

  }
  while(ButtonState==1){
  lcd.setCursor(0,0);
  lcd.print("*  FLASOR LED  *");
  lcd.setCursor(0,1);
  lcd.print("*     MODU     *");


    /* Convertion of size */
  ValueR=map(analogRead(Potasiometer_R),0,1023,0,255);
  ValueG=map(analogRead(Potasiometer_G),0,1023,0,255);
  ValueB=map(analogRead(Potasiometer_B),0,1023,0,255);

/* for the preventing arc of potansiometer */
  if(ValueR <= 15){
    ValueR=0;
  }
   if(ValueG <= 15){
    ValueG=0;
  }
   if(ValueB <= 15){
    ValueB=0;
  }

   /* LOGIC HIGH */
  analogWrite(Led_R,ValueR);
  analogWrite(Led_G,ValueG);
  analogWrite(Led_B,ValueB);

  delay(100);

  /* LOGIC LOW */
  analogWrite(Led_R,0);
  analogWrite(Led_G,0);
  analogWrite(Led_B,0); 

  }
  
  while(ButtonState==2){
    
  lcd.setCursor(0,0);
  lcd.print("*  RENK TUFANI *");
  lcd.setCursor(0,1);
  lcd.print("*  ANIMASYONU  *");

  for(;;)              // Black - Red
   {
   analogWrite(Led_R,Counter1);
   analogWrite(Led_G,Counter2);
   analogWrite(Led_B,Counter3);
   Counter1=Counter1+5;
   delay(DelayTime);
   if(Counter1 == 255)
      break;
   }
    
      for(;;)         // Red - Magenta
   {
   analogWrite(Led_R,Counter1);
   analogWrite(Led_G,Counter2);
   analogWrite(Led_B,Counter3);
   Counter3=Counter3+5;
   delay(DelayTime);
      if(Counter3 == 255)
          break;
   }
   
         for(;;)   // Magenta - Blue
   {
   analogWrite(Led_R,Counter1);
   analogWrite(Led_G,Counter2);
   analogWrite(Led_B,Counter3);
   Counter1=Counter1-5;
   delay(DelayTime);
         if(Counter1==0)
             break;
   }
   
            for(;;)  // Blue - Cyan
   {
   analogWrite(Led_R,Counter1);
   analogWrite(Led_G,Counter2);
   analogWrite(Led_B,Counter3);
   Counter2=Counter2+5;
   delay(DelayTime);
         if(Counter2 == 255)
             break;
   }
   
               for(;;) // Cyan - Green
   {
   analogWrite(Led_R,Counter1);
   analogWrite(Led_G,Counter2);
   analogWrite(Led_B,Counter3);
   Counter3=Counter3-5;
   delay(DelayTime);
         if(Counter3 == 0)
             break;
   }
   
                  for(;;)  // Green - Yellow
   {
   analogWrite(Led_R,Counter1);
   analogWrite(Led_G,Counter2);
   analogWrite(Led_B,Counter3);
   Counter1=Counter1+5;
   delay(DelayTime);
         if(Counter1 == 255)
              break;
   }
   
                     for(;;)  // Yellow - White
   {
   analogWrite(Led_R,Counter1);
   analogWrite(Led_G,Counter2);
   analogWrite(Led_B,Counter3);
   Counter3=Counter3+5;
   delay(DelayTime);
         if(Counter3 == 255)
               break;
   }

                        for(;;)  // White - Black
   {
   analogWrite(Led_R,Counter1);
   analogWrite(Led_G,Counter2);
   analogWrite(Led_B,Counter3);
   Counter1=Counter3-5;
   Counter2=Counter3-5;
   Counter3=Counter3-5;
   delay(DelayTime);

         if((Counter1 == 0 && Counter2 == 0 && Counter3 == 0)){
          break;      
    } 
   }
  }
  while(ButtonState==3){
  lcd.setCursor(0,0);
  lcd.print("*   BLUETOOTH  *");
  lcd.setCursor(0,1);
  lcd.print("*     MODU     *");

 /* Reading the Bluetooth Data's*/
  if(Bluetooth.available())   
  {
     Data = Bluetooth.read(); 
  }
/* Evaluate RGB Leds color According to the Bluetooth Data */
    switch(Data)
  {
     case 'K' : analogWrite(Led_R,255); analogWrite(Led_G,0); analogWrite(Led_B,0);          break; // Red
     case 'Y' : analogWrite(Led_R,0); analogWrite(Led_G,255);   analogWrite(Led_B,0);        break; // Green
     case 'M' : analogWrite(Led_R,0); analogWrite(Led_G,0); analogWrite(Led_B,255);          break; // Blue
     case 'P' : analogWrite(Led_R,255);   analogWrite(Led_G,0); analogWrite(Led_B,255);      break; // Magenta
     case 'S' : analogWrite(Led_R,255);   analogWrite(Led_G,255);   analogWrite(Led_B,0);    break; // Yellow
     case 'B' : analogWrite(Led_R,255);   analogWrite(Led_G,255);   analogWrite(Led_B,255);  break; // White
     case 'C' : analogWrite(Led_R,0); analogWrite(Led_G,255);   analogWrite(Led_B,255);      break; // Cyan
  } 
 }
}
/* External İnterrupt Handler Functions */
void ButtonFunction(){
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  
  if (interrupt_time - last_interrupt_time > 50) 
  {
    BuzzerFunction();
    ButtonState++;

    if(ButtonState==4){
      ButtonState=0;
    }

  }
  last_interrupt_time = interrupt_time;
}

/* Buzzer Notices Functions */
void BuzzerFunction(){
  digitalWrite(Buzzer,HIGH);
  delay(100);
  digitalWrite(Buzzer,LOW);
  delay(100);
}
