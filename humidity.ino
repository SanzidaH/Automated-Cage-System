#include<LiquidCrystal.h>
#include <SoftwareSerial.h>


SoftwareSerial SIM900A(8,10); // RX | TX

int tempPin = A1;
int tempsense = 0;
int tempc;  //variable to store temperature in degree Celsius

int rhPin = A2;
int rhsense = 0;
int rh = 0;

int gasPin = A0;
int GasSensorValue = 0;

int waterPin = A4;
int WaterSensorValue = 0;

int waterPin2 = A3;
int WaterSensorValue2 = 0;

int isObstaclePin = A5;
int isObstacle = HIGH;
int EggCount = 0;

const int bulb = 13;
const int IN1 = 7;   // Pin no Define//dc fan

const int IN2 = 8;   // Pin no Define//pump

const int IN3 = 9;   // Pin no Define//exhust fan

const int IN4 = 10;   // Pin no Define

const int EN1 = 6;    // Pin no Define


//int pin13 = 13;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
 Serial.begin(9600);
 lcd.begin(16,2);
 lcd.setCursor(0,0);
 lcd.print("Automated poltry");
 lcd.setCursor(0,1);
  lcd.print("cage system");
 
 SIM900A.begin(9600);
 
 //for mq 135 input
 pinMode( gasPin, INPUT);//0
 pinMode( tempPin, INPUT);//1
 pinMode( rhPin, INPUT);//2
 pinMode( waterPin, INPUT);//4
 pinMode( waterPin2, INPUT);//3
 pinMode( isObstaclePin, INPUT);//5
 

 
   pinMode(IN1,OUTPUT); // Pin 7 as output and connected to IN1
   pinMode(IN2,OUTPUT); // Pin 8 as output and connected to IN2
   pinMode(EN1,OUTPUT); // Pin 6  as ouput and connected to Enable1
   pinMode(IN3,OUTPUT); // Pin 9 as output and connected to IN1
   pinMode(IN4,OUTPUT); // Pin 10 as output and connected to IN2
  
   pinMode(bulb, OUTPUT);

}

void loop() {

 lcd.display();
 
GasSensorValue = analogRead(gasPin); 
tempsense = analogRead(tempPin);
rhsense = analogRead(rhPin);
WaterSensorValue = analogRead(waterPin); // read analog input pin 0
WaterSensorValue2 = analogRead(waterPin2);

tempc= ((tempsense*500)/1023);// Storing value in Degree Celsius
tempc = tempc+30;
rh = ((30.855*(rhsense/204.6))-11.504);
//WaterSensorValue= WaterSensorValue -19;

isObstacle = digitalRead(isObstaclePin);
if(tempc<0)
{
  tempc = (-1)*tempc;
 }
//Egg count
  if(isObstacle ==  LOW)
{
  Serial.println("Egg Detect!!");

  EggCount++;
  
  Serial.println("Egg count: ");
  Serial.println(EggCount);
  lcd.print("Egg detect!!");
  
  

  //irSensor ==  HIGH;
}
 else{
  Serial.println("No egg!!");
 }

  delay(1000);

Serial.print("Temperature: ");
Serial.print(tempc);
Serial.println(" C ");
Serial.println("Gas: ");
Serial.println(GasSensorValue, DEC);  // prints the value read
Serial.println("Water: ");
Serial.println(WaterSensorValue, DEC);
Serial.println("Water2: ");
Serial.println(WaterSensorValue2, DEC);

lcd.clear();




lcd.setCursor(0,0);
lcd.print("H=");
lcd.print(rh);
lcd.print("%");
lcd.print(", NH3=");
lcd.print(GasSensorValue);
lcd.setCursor(0,1);
//lcd.print("W:");
//lcd.print(WaterSensorValue);
lcd.print("Temp:");
lcd.print(tempc);
lcd.print(",Egg:");
lcd.print(EggCount);

delay(1000); //Delay of 1 second for ease of viewing in serial monitor






if(EggCount>5){
//digitalWrite(pin13, HIGH);  

SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
//delay(1000);  // Delay of 1 second
SIM900A.println("AT+CMGS=\"+8801521101748\"\r"); // Replace x with mobile number
//delay(1000);
SIM900A.println("ATTENTION, Egg dropped!");// The SMS text you want to send
SIM900A.println(EggCount);
//delay(10000);
SIM900A.println((char)26);

                                      
//delay(1000);
}
//
//else{
////  digitalWrite(pin13, LOW);
//lcd.print("Humidity: ");
//lcd.print(rh);
//lcd.println("% ");
//Serial.print("Humidity: ");
//Serial.print(rh);
//Serial.println("% ");                                          
////delay(1000);
//  }

  if(tempc>20 )
    { 
      
    // Forward Direction 
   digitalWrite(EN1,HIGH);  // Enable1 HIGH
    digitalWrite(IN1,HIGH);  // IN1 HIGH
     digitalWrite(IN3,HIGH);

    //digitalWrite(IN2,LOW);  //  IN2 LOw

  
    digitalWrite(bulb,LOW);
    

//   lcd.clear();
//   lcd.setCursor(0,0);
//   lcd.print("Fan ON            ");
//   lcd.setCursor(0,1);
//     lcd.print("H: ");
//     lcd.print(rh);
//     lcd.print("% ");
//     lcd.print("T: ");
//     lcd.print(tempc);
      
                                           
     delay(1000);
    //delay(10000);//wait for 10s
    }
 else if(tempc<15)
  {
    digitalWrite(bulb,HIGH);
    digitalWrite(IN1,LOW);
    digitalWrite(IN3,LOW);
  }
 else
 {
   digitalWrite(bulb,LOW);
    digitalWrite(IN1,LOW);
    digitalWrite(IN3,LOW);
  }
 
  if( GasSensorValue>210 )
  {
     digitalWrite(IN3,HIGH);
  }
  else{
       digitalWrite(IN3,LOW);
  }
     if(WaterSensorValue < 800 )
  { 
    digitalWrite(EN1,LOW);  // Enable1 HIGH
    digitalWrite(IN2,LOW);  //  IN2 LOw
    delay(10000);
   }
   else if(WaterSensorValue >900)
   {
      digitalWrite(IN2,HIGH);  //  IN2 LOw
   }

 //  lcd.clear();
 //  lcd.setCursor(0,0);
  // lcd.print("Water supplying            ");
  // lcd.setCursor(0,1);
    //  lcd.print("Water: ");
    // lcd.print(WaterSensorValue);
   //  lcd.print("% "); 
                                           
    // delay(1000);
   // delay(10000);//wait for 10s
   
}
