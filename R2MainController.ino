
/* Doc Snyders Tool Droid MainController Arduino Mega 2560 */
String cmd; //Consolen Input
byte debug; //Debug function
String data; //Serial Data


int Mode = 0; // Default Mode  0 = Input Wifi and Coin
              // RC Mode       1 = Input RC and Coin
              // RC Show       2 = RC only


#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

///Relais Bridge for MOVE/Drive
///Set Pins as Output

const int REL1 =  42;  
const int REL2 =  43;  
const int REL3 =  44;  
const int REL4 =  45;  

///Input Channels for RC Controller

////Taster

int CH11 = 8;  ///Level
int CH12 = 9;  ///Execute
int CH13 = 10;
int CH14 = 11;

///Schalter Statisch
int CH5  = 4;
int CH6  = 5;
int CH9  = 6;
int CH10 = 7;

/// Hebel/Poti
int CH4 = 22; ///ARM Panel 1
int CH8 = 23;
int CH7 = 24;



Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

#define MIN_PULSE_WIDTH       500
//650
#define MAX_PULSE_WIDTH       2000
//2350
#define DEFAULT_PULSE_WIDTH   1500
//1500
#define FREQUENCY             50
//50

// PCM Ports
// 0 = Servo Arm rechts auf ab
// 1 = Servo Hand
// 2 = Servo Arm Links auf ab
// 3 = Servo Schrauber an/aus
// 4 = 
// 6 =
// 7 =
// 8 =
// 9 =
//10 =
//11 = P-1 Tür links
//12 = P-2 Tür links mitte
//13 = P-3 Kleine Tür oben rechts Charge Bay 
//14 = P-4 Kleine Tür unten rechts
//15 = P-5 Tür rechts

//Klappen Servos und Position
//Nummer  0   1  2  3  4  5
int KlappeAuf[] = {0,60,20,90,20,170}; //vorher 60 P4
//Nummer  0   1  2   3   4  5
int KlappeZu[] = {0,170,180,190,190,50};

//SCHUBA 0 1 2 3 4
int SchubaAuf[] = {0, 80, 80, 80, 80};
//SCHUBA 0 1 2 3 4
int SchubaZu[] = {0, 190, 190, 190, 190};


int GripAuf = 90;
int GripZu = 62;

int ServosAus() {
      //Alle Klappenservos aus
      for (int thisKlappe = 1; thisKlappe <= 5; thisKlappe++) {
          int port = thisKlappe +10;
         pwm.setPWM(port, 0, 4096); ///Servo Abschalten
      }

      //Alle Schuba Servos aus
      pwm.setPWM(4, 0, 4096); ///Servo Abschalten
      pwm.setPWM(5, 0, 4096); ///Servo Abschalten
      pwm.setPWM(6, 0, 4096); ///Servo Abschalten
      pwm.setPWM(7, 0, 4096); ///Servo Abschalten
  
}

 

int Sysreset(){
       
      
       
       pwm.setPWM(0, 0, pulseWidth(30));///Arm 1 zurück
       delay(200);
        pwm.setPWM(1, 0, pulseWidth(GripAuf));///Gripper Auf
       delay(1000);
       pwm.setPWM(1, 0, pulseWidth(GripZu));///Gripper ZU
       delay(200);
       pwm.setPWM(2, 0, pulseWidth(30));///Arm 2 zurück
       delay(200);
       pwm.setPWM(3, 0, pulseWidth(30));///Schrauber aus
       delay(200);
       
      for (int thisKlappe = 1; thisKlappe <= 5; thisKlappe++) {
    
         int port = thisKlappe +10;
         pwm.setPWM(port, 0, pulseWidth(KlappeZu[thisKlappe]));//Klappe x      
         
      }

       
      
      pwm.setPWM(7, 0, pulseWidth(SchubaZu[1]));///Schuba S1
      delay(50);
      pwm.setPWM(6, 0, pulseWidth(SchubaZu[2]));///Schuba S2
      delay(50);
      pwm.setPWM(5, 0, pulseWidth(SchubaZu[3]));///Schuba S3
      delay(50);
      pwm.setPWM(4, 0, pulseWidth(SchubaZu[4]));///Schuba S4

      delay(200);
      
      ServosAus();    
      
}


int CloseAll() {
  
      pwm.setPWM(0, 0, pulseWidth(30));///Arm 1 zurück
       delay(200);
       pwm.setPWM(1, 0, pulseWidth(GripZu));///Gripper ZU
       delay(200);
       pwm.setPWM(2, 0, pulseWidth(30));///Arm 2 zurück
       delay(200);
       pwm.setPWM(3, 0, pulseWidth(30));///Schrauber aus
       delay(200);
       
      for (int thisKlappe = 1; thisKlappe <= 5; thisKlappe++) {
    
         int port = thisKlappe +10;
         pwm.setPWM(port, 0, pulseWidth(KlappeZu[thisKlappe]));//Klappe 1
  
      }
   
      delay(50);
      pwm.setPWM(7, 0, pulseWidth(SchubaZu[1]));///Schuba S1
      delay(50);
      pwm.setPWM(6, 0, pulseWidth(SchubaZu[2]));///Schuba S1
      delay(50);
      pwm.setPWM(5, 0, pulseWidth(SchubaZu[3]));///Schuba S1
      delay(50);
      pwm.setPWM(4, 0, pulseWidth(SchubaZu[4]));///Schuba S1

      delay(200);

      ServosAus();

  
}


int OpenAll() {
      
      for (int thisKlappe = 1; thisKlappe <= 5; thisKlappe++) {
    
         int port = thisKlappe +10;
         pwm.setPWM(port, 0, pulseWidth(KlappeAuf[thisKlappe]));//Klappe 1
          
      }
      pwm.setPWM(7, 0, pulseWidth(SchubaAuf[1]));///Schuba S1
      delay(50);
      pwm.setPWM(6, 0, pulseWidth(SchubaAuf[2]));///Schuba S1
      delay(50);
      pwm.setPWM(5, 0, pulseWidth(SchubaAuf[3]));///Schuba S1
      delay(50);
      pwm.setPWM(4, 0, pulseWidth(SchubaAuf[4]));///Schuba S1
      delay(200);
      
      ServosAus();
      
}

int Smirk() {

       //Function Arm reset evtl auslagern 
       pwm.setPWM(0, 0, pulseWidth(30));///Arm 1 zurück
       delay(50);
       pwm.setPWM(1, 0, pulseWidth(GripZu));///Gripper ZU
       delay(50);
       pwm.setPWM(2, 0, pulseWidth(30));///Arm 2 zurück
       delay(50);
       pwm.setPWM(3, 0, pulseWidth(30));///Schrauber aus
       delay(50);
       
      for (int thisKlappe = 1; thisKlappe <= 5; thisKlappe++) {   
         int port = thisKlappe +10;        
         pwm.setPWM(port, 0, pulseWidth(KlappeAuf[thisKlappe]));//Klappe x    
         delay(100);         
      }
      
      for (int thisKlappe = 1; thisKlappe <= 5; thisKlappe++) {   
         int port = thisKlappe +10;       
         pwm.setPWM(port, 0, pulseWidth(KlappeZu[thisKlappe]));//Klappe x    
         delay(100);          
      }     
       
      pwm.setPWM(7, 0, pulseWidth(SchubaAuf[1]));///Schuba S1
      delay(150);
      pwm.setPWM(6, 0, pulseWidth(SchubaAuf[2]));///Schuba S1
      delay(150);
      pwm.setPWM(5, 0, pulseWidth(SchubaAuf[3]));///Schuba S1
      delay(150);
      pwm.setPWM(4, 0, pulseWidth(SchubaAuf[4]));///Schuba S1
      delay(150);
      pwm.setPWM(7, 0, pulseWidth(SchubaZu[1]));///Schuba S1
      delay(150);
      pwm.setPWM(6, 0, pulseWidth(SchubaZu[2]));///Schuba S1
      delay(150);
      pwm.setPWM(5, 0, pulseWidth(SchubaZu[3]));///Schuba S1
      delay(150);
      pwm.setPWM(4, 0, pulseWidth(SchubaZu[4]));///Schuba S1
      delay(200);
      
      ServosAus();    
 
}

int Wave() {

       //Function Arm reset evtl auslagern 
       pwm.setPWM(0, 0, pulseWidth(30));///Arm 1 zurück
       delay(50);
       pwm.setPWM(1, 0, pulseWidth(GripZu));///Gripper ZU
       delay(50);
       pwm.setPWM(2, 0, pulseWidth(30));///Arm 2 zurück
       delay(50);
       pwm.setPWM(3, 0, pulseWidth(30));///Schrauber aus
       delay(50);
       
      for (int thisKlappe = 1; thisKlappe <= 5; thisKlappe++) {   
         int port = thisKlappe +10;        
         pwm.setPWM(port, 0, pulseWidth(KlappeAuf[thisKlappe]));//Klappe x    
         delay(500);         
      }

      delay(500);
      
      for (int thisKlappe = 1; thisKlappe <= 5; thisKlappe++) {   
         int port = thisKlappe +10;       
         pwm.setPWM(port, 0, pulseWidth(KlappeZu[thisKlappe]));//Klappe x    
         delay(500);          
      }     
       
      pwm.setPWM(7, 0, pulseWidth(SchubaAuf[1]));///Schuba S1
      delay(200);
      pwm.setPWM(6, 0, pulseWidth(SchubaAuf[2]));///Schuba S1
      delay(200);
      pwm.setPWM(5, 0, pulseWidth(SchubaAuf[3]));///Schuba S1
      delay(200);
      pwm.setPWM(4, 0, pulseWidth(SchubaAuf[4]));///Schuba S1
      delay(200);
      pwm.setPWM(7, 0, pulseWidth(SchubaZu[1]));///Schuba S1
      delay(200);
      pwm.setPWM(6, 0, pulseWidth(SchubaZu[2]));///Schuba S1
      delay(200);
      pwm.setPWM(5, 0, pulseWidth(SchubaZu[3]));///Schuba S1
      delay(200);
      pwm.setPWM(4, 0, pulseWidth(SchubaZu[4]));///Schuba S1
      delay(200);
      
      ServosAus();    
 
}



int Dance() {

      for (int n = 1; n <= 5; n++) { 

      //Function Arm reset evtl auslagern 
       pwm.setPWM(0, 0, pulseWidth(30));///Arm 1 zurück
       delay(50);
       pwm.setPWM(1, 0, pulseWidth(GripZu));///Gripper ZU
       delay(50);
       pwm.setPWM(2, 0, pulseWidth(30));///Arm 2 zurück
       delay(50);
       pwm.setPWM(3, 0, pulseWidth(30));///Schrauber aus
       delay(50);
       
      for (int thisKlappe = 1; thisKlappe <= 5; thisKlappe++) {   
         int port = thisKlappe +10;        
         pwm.setPWM(port, 0, pulseWidth(KlappeAuf[thisKlappe]));//Klappe x    
         delay(500);         
      }
      
      for (int thisKlappe = 1; thisKlappe <= 5; thisKlappe++) {   
         int port = thisKlappe +10;       
         pwm.setPWM(port, 0, pulseWidth(KlappeZu[thisKlappe]));//Klappe x    
         delay(500);          
      }     

      ServosAus();  
      }
      
  
}

int Faint() {

     // int KlappeAuf[] = {0,60,20,90,60,170};     
            
         pwm.setPWM(11, 0, pulseWidth(KlappeAuf[1]));//Klappe x   
        delay(1500);
        pwm.setPWM(0, 0, pulseWidth(160));///Arm 1 hoch
        
           pwm.setPWM(12, 0, pulseWidth(50));//Klappe x   
           pwm.setPWM(13, 0, pulseWidth(120));//Klappe x   
           pwm.setPWM(14, 0, pulseWidth(100));//Klappe x   
           pwm.setPWM(15, 0, pulseWidth(120));//Klappe x   
           
        
       delay(3000);       
       pwm.setPWM(0, 0, pulseWidth(30));///Arm 1 zurück
       delay(3000);    

       Sysreset();     
   
}

void DrivePower(int on){
  
   if (on == 1) {
   digitalWrite(REL1, HIGH);
   digitalWrite(REL2, HIGH);
   digitalWrite(REL3, HIGH);
   digitalWrite(REL4, HIGH);
   } else  {
   digitalWrite(REL1, LOW);
   digitalWrite(REL2, LOW);
   digitalWrite(REL3, LOW);
   digitalWrite(REL4, LOW);
   }
  
}




int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  //Serial.println(analog_value);
  return analog_value;
}


void RcInput() {

    int CH11value = pulseIn(CH11,HIGH);
    int CH12value = pulseIn(CH12,HIGH);
    int CH5value = pulseIn(CH5,HIGH);
    int CH6value = pulseIn(CH6,HIGH);



   
      if (CH11value >=800){ ///Check if Sensor is Connected and RC on
      ////Sensor Channel auslesen und Action    
          if (CH11value < 1400){
              if (debug){ 
                  Serial.println("LEVEL plus");
              }

            Serial1.print("1");
            Serial1.print("\r");
    
          } else if (CH11value > 1500) {
                if (debug) {
                    Serial.println("LEVEL minus");
                    }     
             Serial1.print("3");
             Serial1.print("\r");       
   
          } // END CH11
          

       
          if (CH12value < 1400){
              if (debug){ 
                  Serial.println("LEVEL plus");
              }
              
              Serial1.print("2");
              Serial1.print("\r");
    
          } else if (CH12value > 1500) {
                if (debug) {
                    Serial.println("LEVEL minus");
                    }     
                    
                Wave();    
               
          } // END CH12   

          ////CH5          
          if (CH5value < 1400){
              if (debug){ 
                  Serial.println("CH5");
              }
              
              DrivePower(0);
    
          } else if (CH5value > 1500) {
                if (debug) {
                    Serial.println("CH5");
                    }     
                    
              DrivePower(1); 
               
          } // END CH5

          //CH6
          
          if (CH6value < 1400){
              if (debug){ 
                  Serial.println("CH5");
              }

              Serial3.print(":SE07");
              Serial3.print("\r");
    
          } else if (CH6value > 1500) {
                if (debug) {
                    Serial.println("CH5");
                    }     
                    
              Serial3.print(":SE10");
              Serial3.print("\r");
              Sysreset();
               
          } // END CH6

          

      } //END check RC connected
      
} //END Sensor RC Input



void setup()
{
  // Zuerst initialisieren wir die serielle Schnittstelle des Arduino.
  Serial.begin(9600); // Monitor for debugging
  Serial.println("##### R2MainController 16.12.2018 #####");
  Serial.println("Comandos von RC - CoinTaster - Wfif Modul werde verarbeitet");
  Serial.println("INPUT:");
  Serial.println("..... CoinButton Controller an ....Serial 1 RX");
  Serial.println("..... .............................Serial 2 RX");
  Serial.println("..... WiFi Modul an ...............Serial 3 RX");
  Serial.println("");
  Serial.println("OUTPUT:");
  Serial.println("..... CoinButton Controller an ....Serial 1 RX");
  Serial.println("..... Dome Drive Controller........Serial 2 TX");
  Serial.println("..... Marcduino Dome Controller....Serial 3 TX");
  Serial.println("");
  Serial.println("...fuer DebugMode debug eingeben...");
  Serial.println("...ende DebugMode debug off eingeben...");
  Serial1.begin(9600); // Serial RX Input vom Coinslot Modul TX to Coinslot Modul
  Serial2.begin(9600); // Serial TX ____ to Dome Drive Controller
  Serial3.begin(9600); // Serial RX Input vom Wifi Modul TX to Marcduino Boards
  ///Output Pin for Relais Move/Drive
  pinMode(REL1, OUTPUT);
  pinMode(REL2, OUTPUT);
  pinMode(REL3, OUTPUT);
  pinMode(REL4, OUTPUT);
  DrivePower(1);
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY); 
  debug = true;
  Sysreset();  
  
  
}

/* ##### MAIN KERNEL SECTION #####*/

void loop()
{
  if (Mode == 0) {
    readWifi();
    readCoinButton();
  }

   if (Mode == 1) {
    readCoinButton();
    RcInput();
   }
    
   readCom(); 
}



void readWifi() {
  
  if(Serial3.available() > 0 )
    {      
       data = Serial3.readStringUntil('\r');      
      if (data != "") {
        if (debug){
           // say what you got:
          Serial.print("I received from Wifi: ");
          Serial.println(data);
        }
          parseCommand(data);
          data = "";
          Serial3.flush();
      } // end data
    } // end serial
}



void readCoinButton() {
    
    if(Serial1.available() > 0 )
    {      
      data = Serial1.readStringUntil('\r');      
      if (data != "") {
        if (debug){
           // say what you got:
          Serial.print("I received from CoinButton: ");
          Serial.println(data);
        }
          parseCommand(data);
          data = "";
         Serial1.flush();
      } // end data
    } // end Serial
  
}

void readCom() {
 
  if(Serial.available() > 0)
    {
        data = Serial.readStringUntil('\n');
        parseCommand(data);
        data = "";
        Serial.flush();
    } // end serial
     
}




void parseCommand(String cmd) {

    if (cmd == "CBD1") {
      if (debug){
        Serial.println("######Comando CBD1######");
        Serial.println(cmd);
        
      }
      
    //Serial1.print("5");     // to Coin Levelstatus
    Serial2.print("mode1");           // hier geht es weiter zum Dome Controller
    Serial2.print('\r');
    delay(500);
    
    
    Serial3.print(":SE13");           // hier geht es weiter zum Marcduino Dome Controller
    Serial3.print('\r');
    Sysreset();
      
    }
    if (cmd == "CBD2") {
    if (debug){
        Serial.println("######Comando CBD2 ######");
        Serial.println(cmd);
      }
      Mode = 0;
      
      Serial2.print("mode0");           // hier geht es weiter zum  Dome Controller
      Serial2.print('\r');
      delay(500);

      Serial2.print("$216");           // hier geht es weiter zum  Dome Controller
      Serial2.print('\r');
      delay(500);
    }
    
    if (cmd == "CBD3" ){
      if (debug){
        Serial.println("######Comando Dome CBD3 ######");
        Serial.println(cmd);
      }
      Mode = 1;
      Serial2.print("center");           // hier geht es weiter zum Marcduino Dome Controller
      Serial2.print('\r');
      delay(500);
      Serial3.print("$211");           // hier geht es weiter zum Marcduino Dome Controller
      Serial3.print('\r');

      
      
      pwm.setPWM(14, 0, pulseWidth(KlappeAuf[4]));//Klappe x  
      delay(500);
       
      
    }
  
    if (cmd == "CB0") {
    if (debug){
        Serial.println("######Comando CB0 ######");
        Serial.println(cmd);
      }
      Serial2.print("usb");           // hier geht es weiter zum  Dome Controller
      Serial2.print('\r');
      delay(1000);
      Serial3.print(":OP02");           // hier geht es weiter zum Marcduino Dome Controller
      Serial3.print('\r');
      delay(500);
      Serial3.print("$12");
      Serial3.print("\r");
    }

  
    
    if (cmd == "debug") {
      if (debug){
          Serial.println("######Comando - debug######");
         Serial.println(cmd);
       }
       debug=1;
    }

    if (cmd == "debug off") {
    if (debug){
          Serial.println("######Comando - debug off######");
         Serial.println(cmd);
       }
       debug=0;
    }
    ///// Komando/////
    if (cmd == "CB1") {
    if (debug){
          Serial.println("######Comando - CB1######");
         Serial.println(cmd);
       }

      
      Serial2.print("tool1");
      Serial2.print("\r");
      delay(2000); 
      Serial3.print(":OP04");
      Serial3.print("\r");
      delay(100);
      Serial3.print("$118");
      Serial3.print("\r");
    }

    /////Tool Komando/////

    if (cmd == "CB2") {
    if (debug){
          Serial.println("######Comando - CB2######");
         Serial.println(cmd);
       }

      
      
      Serial2.print("tool2");
      Serial2.print("\r");
      delay(2000);
      Serial3.print("$12");
      Serial3.print("\r");
      delay(500);
      Serial3.print(":OP05");
      Serial3.print("\r");
      
     
    }
    ///// Komando/////

    if (cmd == "CB3") {
    if (debug){
          Serial.println("######Comando - tool2######");
         Serial.println(cmd);
       }
      
         

      Serial2.print("tool3");
      Serial2.print("\r");
      delay(1000);
      Serial3.print(":OP06");
      Serial3.print("\r");
      delay(500);
      Serial3.print("$118");
      Serial3.print("\r");

      
    }
    
    if (cmd == "CB4") {
    if (debug){
          Serial.println("######Comando - CB4######");
         Serial.println(cmd);
       }
          
      pwm.setPWM(11, 0, pulseWidth(70));///Klappe 1 auf
      delay(1500);
      pwm.setPWM(0, 0, pulseWidth(160));///Arm 1 hoch
      delay(500);
      pwm.setPWM(1, 0, pulseWidth(GripZu));///Hand Auf
      delay(500);
      pwm.setPWM(1, 0, pulseWidth(GripAuf));///Hand schließen
      delay(1500);
      pwm.setPWM(1, 0, pulseWidth(GripZu));///Hand Auf
      delay(500);
      pwm.setPWM(1, 0, pulseWidth(80));///Hand schließen
      
      Serial3.print("$116");
      Serial3.print("\r");
      
    }

    if (cmd == "CB5") {
    if (debug){
          Serial.println("######Comando - CB5 Bohren######");
         Serial.println(cmd);
       }

      pwm.setPWM(15, 0, pulseWidth(KlappeAuf[5]));//Klappe 1
      delay(1500);
      pwm.setPWM(2, 0, pulseWidth(150));///Arm 2 hoch
      delay(1000);
      pwm.setPWM(3, 0, pulseWidth(20));///Schrauber hoch
      delay(500);
      pwm.setPWM(3, 0, pulseWidth(80));///Schrauber hoch

      pwm.setPWM(5, 0, pulseWidth(SchubaAuf[3]));///Schuba S3

      
      
      
      Serial3.print("$12");
      Serial3.print("\r");

      
    }

     if (cmd == "CB6") {
    if (debug){
          Serial.println("######Comando - CB6 Charging######");
         Serial.println(cmd);
       }

      pwm.setPWM(13, 0, pulseWidth(KlappeAuf[3]));//Klappe 1
      delay(1500);
     
      Serial3.print("$116");
      Serial3.print("\r");

      
    }

    if (cmd == "CB7") {
    if (debug){
          Serial.println("######Comando - CB7 Fire ######");
         Serial.println(cmd);
       }

          
      Serial3.print("$118");
      Serial3.print("\r");

      pwm.setPWM(7, 0, pulseWidth(SchubaZu[1]));///Schuba S1
      delay(50);
      pwm.setPWM(6, 0, pulseWidth(SchubaZu[2]));///Schuba S2
      delay(50);
       
    }

    if (cmd == "CB8") {
    if (debug){
          Serial.println("######Comando - CB8 Akkucheck ######");
         Serial.println(cmd);
       }

          
      Serial3.print("$12");
      Serial3.print("\r");

      pwm.setPWM(5, 0, pulseWidth(SchubaZu[3]));///Schuba S3
      delay(50);
      pwm.setPWM(4, 0, pulseWidth(SchubaZu[4]));///Schuba S4

      
    }

    if (cmd == "CB9") {
    if (debug){
          Serial.println("######Comando - CB9 Drive ######");
         Serial.println(cmd);
       }
          
      Serial3.print("$211");
      Serial3.print("\r");
      DrivePower(1);
      
    }

    if (cmd == "CB10") {
    if (debug){
          Serial.println("######Comando - CB10 Move####");
         Serial.println(cmd);
       }
          
      Serial3.print("$217");
      Serial3.print("\r");
      DrivePower(0);
      
    }

    if (cmd == "CB11") {
    if (debug){
          Serial.println("######Comando - CB11 Wave####");
         Serial.println(cmd);
       }
          
      Serial3.print(":SE04");
      Serial3.print("\r");

      Wave();
      
    }
    
    if (cmd == "CB12") {
    if (debug){
          Serial.println("######Comando - CB12 Smirk####");
         Serial.println(cmd);
       }
          
      Serial3.print(":SE03");
      Serial3.print("\r");

      Smirk();
      
    }

    if (cmd == "CB13") {
    if (debug){
          Serial.println("######Comando - CB13 Disco####");
         Serial.println(cmd);
       }
          
      Serial3.print(":SE07");
      Serial3.print("\r");

      Dance();
      
    }
    
    if (cmd == "CB14") {
    if (debug){
          Serial.println("######Comando - CB14 Open All####");
         Serial.println(cmd);
       }
          
      Serial3.print(":OP00");
      Serial3.print("\r");

      OpenAll();
      
    }

    if (cmd == "CB15") {
    if (debug){
          Serial.println("######Comando - CB15 Close All####");
         Serial.println(cmd);
       }
          
      Serial3.print(":CL00");
      Serial3.print("\r");

      CloseAll();
      
    }

    if (cmd == "CB16") {
    if (debug){
          Serial.println("######Comando - CB16 Sream####");
         Serial.println(cmd);
       }
          
      Serial3.print(":SE15");
      Serial3.print("\r");

      OpenAll();
      
    }

    if (cmd == "CB17") {
    if (debug){
          Serial.println("######Comando - CB17 Faint ####");
         Serial.println(cmd);
       }
          
      Serial3.print(":SE06");
      Serial3.print("\r");

      Faint();
      
    }

    /// Filtern ob Dome Komando oder nicht ///
    
    if (cmd.startsWith(":")) {
      if (debug){
        Serial.println("######WIFI Comando######");
        Serial.println(cmd);
      }
      Serial3.print(cmd);           // hier geht es weiter zum Marcduino Dome Controller
      Serial3.print('\r');
      bodyCommand(cmd);
      
    }

    if (cmd.startsWith("$")) {
      if (debug){
        Serial.println("######WIFI Comando######");
        Serial.println(cmd);
      }
      Serial3.print(cmd);           // hier geht es weiter zum Marcduino Dome Controller
      Serial3.print('\r');
    }
    if (cmd.startsWith("*")) {
      if (debug){
        Serial.println("######WIFI Comando######");
        Serial.println(cmd);
      }
      Serial3.print(cmd);           // hier geht es weiter zum Marcduino Dome Controller
      Serial3.print('\r');
    }
  
}

///BODY Action from Dome Command

void bodyCommand(String bcmd) {

      if (bcmd == ":SE00") {
        Sysreset();
      }

      if (bcmd == ":CL00") {
        CloseAll();
      }

      if (bcmd == ":OP00") {
        OpenAll();
      }

      if (bcmd == ":SE04") {
        Wave();
      }
      if (bcmd == ":SE02") {
        Smirk();
      }
      
      if (bcmd == ":SE03") {
        Smirk();
      }
     
      if (bcmd == ":SE07") {
        Dance();
      }

      if (bcmd == ":SE01") {
        Faint();
      }
      if (bcmd == ":SE06") {
        Faint();
      }
      
      if (bcmd == ":SE57") {
        Dance();
      }
      
      

  
}




