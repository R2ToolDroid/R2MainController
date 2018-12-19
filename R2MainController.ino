
/* Doc Snyders Tool Droid MainController Arduino Mega 2560 */
String cmd; //Consolen Input
byte debug; //Debug function
String data; //Serial Data

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

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
// 3 = Servo Arm Links auf ab
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
int KlappeAuf[] = {0,60,20,90,60,170};
//Nummer  0   1  2   3   4  5
int KlappeZu[] = {0,170,180,190,190,50};

//SCHUBA 0 1 2 3 4
int SchubaAuf[] = {0, 80, 80, 80, 80};
//SCHUBA 0 1 2 3 4
int SchubaZu[] = {0, 190, 190, 190, 190};

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
       pwm.setPWM(1, 0, pulseWidth(85));///Gripper ZU
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
      pwm.setPWM(6, 0, pulseWidth(SchubaZu[2]));///Schuba S1
      delay(50);
      pwm.setPWM(5, 0, pulseWidth(SchubaZu[3]));///Schuba S1
      delay(50);
      pwm.setPWM(4, 0, pulseWidth(SchubaZu[4]));///Schuba S1

      delay(200);
      
      ServosAus();    
      
}


int CloseAll() {
  
      pwm.setPWM(0, 0, pulseWidth(30));///Arm 1 zurück
       delay(200);
       pwm.setPWM(1, 0, pulseWidth(85));///Gripper ZU
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
       pwm.setPWM(1, 0, pulseWidth(85));///Gripper ZU
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
       pwm.setPWM(1, 0, pulseWidth(85));///Gripper ZU
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
       pwm.setPWM(1, 0, pulseWidth(85));///Gripper ZU
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





int pulseWidth(int angle)
{
  int pulse_wide, analog_value;
  pulse_wide   = map(angle, 0, 180, MIN_PULSE_WIDTH, MAX_PULSE_WIDTH);
  analog_value = int(float(pulse_wide) / 1000000 * FREQUENCY * 4096);
  //Serial.println(analog_value);
  return analog_value;
}



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
  Serial.println("16 channel Servo test!");
  pwm.begin();
  pwm.setPWMFreq(FREQUENCY); 
  debug = true;
  Sysreset();  
}

/* ##### MAIN KERNEL SECTION #####*/

void loop()
{

   readWifi();
   readCoinButton();
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

    if (cmd == "test") {
      if (debug){
        Serial.println("######Comando######");
        Serial.println(cmd);
        
      }
    Serial1.print("5");     // to Coin Levelstatus
    
    Serial3.print(":OP09");           // hier geht es weiter zum Marcduino Dome Controller
    Serial3.print('\r');

    delay(1000);
    Serial3.print(":CL00");           // hier geht es weiter zum Marcduino Dome Controller
    Serial3.print('\r');
      
    }

    if (cmd == "try dome") {
    if (debug){
        Serial.println("######Comando try dome######");
        Serial.println(cmd);
      }
      Serial2.print("try dome");           // hier geht es weiter zum  Dome Controller
      Serial2.print('\r');

      Sysreset();
      
      for (int thisKlappe = 1; thisKlappe <= 5; thisKlappe++) {
    
         int port = thisKlappe +10;
         pwm.setPWM(port, 0, pulseWidth(KlappeAuf[thisKlappe]));//Klappe x      
         delay(2000);
         pwm.setPWM(port, 0, pulseWidth(KlappeZu[thisKlappe]));//Klappe x    
      }

      CloseAll();
           
    }

    if (cmd == "mode1") {
    if (debug){
        Serial.println("######Comando Dome Mode 1 RC on ######");
        Serial.println(cmd);
      }
      Serial2.print("mode1");           // hier geht es weiter zum  Dome Controller
      Serial2.print('\r');
    }
  
    if (cmd == "mode0") {
    if (debug){
        Serial.println("######Comando Dome Mode 0 RAND RC off ######");
        Serial.println(cmd);
      }
      Serial2.print("mode0");           // hier geht es weiter zum  Dome Controller
      Serial2.print('\r');
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
    /////USB Komando/////
    if (cmd == "usb") {
    if (debug){
          Serial.println("######Comando - usb######");
         Serial.println(cmd);
       }

      Serial3.print(":OP02");
      Serial3.print("\r");
      delay(100);
      Serial2.print("usb");
      Serial2.print("\r");
      delay(100);
      pwm.setPWM(13, 0, pulseWidth(KlappeAuf[3]));//Klappe x   
      Serial3.print("$26");
      Serial3.print("\r");

      
    }

    /////Tool Komando/////

    if (cmd == "tool1") {
    if (debug){
          Serial.println("######Comando - tool1######");
         Serial.println(cmd);
       }

      Serial3.print(":SE14");
      Serial3.print("\r");
      delay(100);
      Serial2.print("tool1");
      Serial2.print("\r");
      delay(100);
      Serial3.print("$26");
      Serial3.print("\r");

       
      pwm.setPWM(11, 0, pulseWidth(70));///Klappe 1 auf
      delay(1500);
      pwm.setPWM(0, 0, pulseWidth(160));///Arm 1 hoch
      delay(500);
      pwm.setPWM(1, 0, pulseWidth(140));///Hand Auf
      delay(500);
      pwm.setPWM(1, 0, pulseWidth(85));///Hand schließen
      
      

      

      
    }
    /////Tool Komando/////

    if (cmd == "tool2") {
    if (debug){
          Serial.println("######Comando - tool2######");
         Serial.println(cmd);
       }
      

      pwm.setPWM(15, 0, pulseWidth(KlappeAuf[5]));//Klappe 1
      delay(1500);
      pwm.setPWM(2, 0, pulseWidth(150));///Arm 2 hoch
      
      pwm.setPWM(3, 0, pulseWidth(50));///Schrauber hoch
      

      Serial2.print("tool2");
      Serial2.print("\r");
      delay(100);
      Serial3.print("$26");
      Serial3.print("\r");

      
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




