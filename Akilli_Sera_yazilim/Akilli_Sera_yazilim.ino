#include <dht11.h>
dht11 DHT11;
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define DHT11PIN A0
#define su A3
#define toprak A1
#define gaz A2
#define suMotoru A5
#define fan A4
#define reZistans 6
int toprakNem,suSeviye,gazDeger,toprakNem1;
int sicaklik;
int maxSicaklik=30;
int nemReferans=20;
int gazReferans=130;
int suReferans=250;
int a=1;



void setup() 
{
   Serial.begin(9600);
   lcd.begin(16, 2);
   lcd.setCursor(2,0);
   lcd.print("AKILLI SERA");
   pinMode(toprak,INPUT);
   pinMode(su,INPUT);
   pinMode(gaz,INPUT);
   pinMode(fan,OUTPUT);
   pinMode(suMotoru,OUTPUT);
   pinMode(reZistans,OUTPUT);
   digitalWrite(reZistans,1);
   digitalWrite(fan,1);
   digitalWrite(suMotoru,1);
   delay(1500);
   lcd.clear();
   
   
}

void loop() 
{
    lcdyazdirma();
    serial_monitor();
    delay(100);
    toprakNem=analogRead(toprak);
    suSeviye=analogRead(su);
    gazDeger=analogRead(gaz);
    int chk=DHT11.read(DHT11PIN);
    sicaklik=DHT11.temperature;

    toprakNem1=map(toprakNem,0,1023,100,0);
///////////////// SICAKLIK VE REZİSTANS ////////////////////////
    if(sicaklik<maxSicaklik)
    {
      digitalWrite(reZistans,0);
    }
    else if(sicaklik>=maxSicaklik)
    {
      digitalWrite(reZistans,1);
    }
//////////////////// NEM VE SU MOTORU //////////////////////////

     if(nemReferans>toprakNem1)
     {
      if(a==1)
      {
        digitalWrite(suMotoru,0);
        delay(1000);
        digitalWrite(suMotoru,1);
        
      }
      
     }
  
//     else if(nemReferans<toprakNem1)
//    {
//      digitalWrite(suMotoru,1);
//    }
//////////////////// GAZ VE FAN ////////////////////////////////

    if(gazReferans<gazDeger||gazReferans+2<gazDeger||gazReferans-2<gazDeger)
    {
      digitalWrite(fan,0);
    }
    else if(gazReferans>=gazDeger||gazReferans+2>gazDeger||gazReferans-2>gazDeger)
    {
      digitalWrite(fan,1);
    }
/////////////////// SU SEVİYESİ ////////////////////////////////


     
}
//////////////////// SERIAL MONITOR ////////////////////////////////
void serial_monitor()
{
     suSeviye=analogRead(su);
//   Serial.print("Sicaklik (Celcius): ");
//   Serial.println((float)DHT11.temperature, DHT11PIN);
//   Serial.println(toprakNem);
   Serial.println(suSeviye);
//   Serial.println(gazDeger);
}

//////////////////// LCD YAZDIRMA /////////////////////////////
void lcdyazdirma()
{
     
     while(suSeviye<suReferans)
    {
      suSeviye=analogRead(su);
      lcd.clear();
      Serial.println(suSeviye);
      lcd.setCursor(2,0);
      lcd.print("SU SEVIYESI");
      lcd.setCursor(3,1);
      lcd.print("AZALIYOR...");
      delay(1000);
      
    }
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Sicaklik: ");
      lcd.setCursor(10,0);
      lcd.print(DHT11.temperature);
      lcd.setCursor(0,1);
      lcd.print("Nem:");
      lcd.setCursor(4,1);
      lcd.print(toprakNem1);
      lcd.setCursor(8,1);
      lcd.print("Gaz: ");
      lcd.setCursor(13,1);
      lcd.print(gazDeger);
      delay(1000);
}







