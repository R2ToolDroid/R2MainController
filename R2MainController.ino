// #include <SoftwareSerial.h>        // Durch diesen Include können wir die Funktionen
// der SoftwareSerial Bibliothek nutzen.
//SoftwareSerial FromWifi(10,11);     //  Pin D10 ist RX, Pin D11 ist TX.// Senden an Marcduino Boards
//SoftwareSerial comDuino(8,9);       //  Pin D8 ist RX, Pin D9 ist TX.// Senden an Marcduino Boards

char W_inChar;   // Jedes empfangene Zeichen kommt kurzzeitig in diese Variable.
String W_input;  // In diesem String speichern wir dann unseren kompletten Text.

char RC_inChar;   // Jedes empfangene Zeichen kommt kurzzeitig in diese Variable.
String RC_input;  // In diesem String speichern wir dann unseren kompletten Text.

char CB_inChar;   // Jedes empfangene Zeichen kommt kurzzeitig in diese Variable.
String CB_input;  // In diesem String speichern wir dann unseren kompletten Text.

String cmd; //Consohlen Input
byte debug; //Debug function

void setup()
{
  // Zuerst initialisieren wir die serielle Schnittstelle des Arduino.
  Serial.begin(9600); // Monitor for debugging
  Serial.println("##### R2MainController 25.10.2018 #####");
  Serial.println("Comandos von RC - CoinTaster - Wfif Modul werde verarbeitet");
  Serial.println("INPUT:");
  Serial.println("..... CoinButton Controller an ....Serial 1 RX");
  Serial.println("..... RC Inputcontroller an .......Serial 2 RX");
  Serial.println("..... WiFi Modul an ...............Serial 3 RX");
  Serial.println("");
  Serial.println("OUTPUT:");
  Serial.println("..... Marcduino Dome Controller....Serial 3 TX");
  Serial.println("..... Gadget Controller............Serial 2 TX");
  Serial.println("..... Dome Drive Controller........Serial 1 TX");
  Serial.println("");
  Serial.println("...fuer DebugMode 1 eingeben...");
  Serial.println("...ende DebugMode 0 eingeben...");
  Serial1.begin(9600); // Serial RX Input vom Coinslot Modul TX to Dome Drive Controller
  Serial2.begin(9600); // Serial RX Input vom RC Controller TX to Gadget Controller
  Serial3.begin(9600); // Serial RX Input vom Wifi Modul TX to Marcduino Boards

  // Dann initialisieren wir die serielle Schnittstelle der SoftwareSerial Bibliothek.
  //FromWifi.begin(9600);

  //delay(500);
  //comDuino.begin(9600);

}

void loop()
{

  //FromWifi.listen();
  while (Serial3.available() > 0 || Serial.available() > 0 ) {      // So lange etwas empfangen wird, durchlaufe die Schleife.

    checkdebug(); ///debuging prüfen

    W_inChar = Serial3.read();           // Speichere das empfangene Zeichen in der Variablen c_inChar.
    W_input.concat(W_inChar);               // Füge das Zeichen an den String an, damit wir den kompletten Text erhalten.
    if (W_inChar == '\r' ) {      // War das letzte Zeichen ein CR (Carriage Return)?

      if (debug == 1) {
        Serial.print("Wifi Input: ");   // Dann schreibe einen Text auf den Serial Monitor.
        Serial.print(W_input + "  zeichen  ");                // Füge in dieselbe Zeile den empfangenen Text ein
        Serial.print( W_input.length());
        Serial.print('\n');
      }

      Serial3.print(W_input);           // hier geht es weiter zum Marcduino Dome Controller
      Serial3.print('\r');
      // und schicke noch ein NL (NewLine) für einen Zeilenumbruch hinterher.
      W_input = "";                         // Lösche den String für die nächste Nachricht.

    } /// CR abgewartet
  }  //end While

  while (Serial1.available() > 0 || Serial.available() > 0 ) {      // So lange etwas empfangen wird, durchlaufe die Schleife.

    checkdebug(); ///debuging prüfen

    CB_inChar = Serial1.read();           // Speichere das empfangene Zeichen in der Variablen c_inChar.
    CB_input.concat(CB_inChar);               // Füge das Zeichen an den String an, damit wir den kompletten Text erhalten.
    if (CB_inChar == '\r' ) {      // War das letzte Zeichen ein CR (Carriage Return)?

      if (debug == 1) {
        Serial.print("CoinButton Input: ");   // Dann schreibe einen Text auf den Serial Monitor.
        Serial.print(CB_input + "  zeichen  ");                // Füge in dieselbe Zeile den empfangenen Text ein
        Serial.print( CB_input.length());
        Serial.print('\n');
      }

      Serial3.print(CB_input);           // hier geht es weiter zum Marcduino Dome Controller
      Serial3.print('\r');
      // und schicke noch ein NL (NewLine) für einen Zeilenumbruch hinterher.
      CB_input = "";                         // Lösche den String für die nächste Nachricht.

    } /// CR abgewartet

  } ///ende WHile for CB


  while (Serial2.available() > 0 || Serial.available() > 0 ) {      // So lange etwas empfangen wird, durchlaufe die Schleife.

    checkdebug(); ///debuging prüfen

    RC_inChar = Serial2.read();           // Speichere das empfangene Zeichen in der Variablen c_inChar.
    RC_input.concat(RC_inChar);               // Füge das Zeichen an den String an, damit wir den kompletten Text erhalten.
    if (RC_inChar == '\r' ) {      // War das letzte Zeichen ein CR (Carriage Return)?

      if (debug == 1) {
        Serial.print("RC Module Input: ");   // Dann schreibe einen Text auf den Serial Monitor.
        Serial.print(RC_input + "  zeichen  ");                // Füge in dieselbe Zeile den empfangenen Text ein
        Serial.print( RC_input.length());
        Serial.print('\n');
      }

      Serial3.print(RC_input);           // hier geht es weiter zum Marcduino Dome Controller
      Serial3.print('\r');
      // und schicke noch ein NL (NewLine) für einen Zeilenumbruch hinterher.
      RC_input = "";                         // Lösche den String für die nächste Nachricht.

    } /// CR abgewartet

  } ///ende WHile for CB

}

void checkdebug() {

  cmd = "";
  cmd = Serial.read();
  int h = Serial.available();
  for (int i = 0; i < h; i++) {
    cmd += (char)Serial.read();
  }

  if (cmd == "49") {
    Serial.print( cmd + " OK debug on" + "\n" ); //Kommando quittieren
    debug = 1;
  }
  if (cmd == "48") {
    Serial.print( cmd + " OK debug off" + "\n" ); //Kommando quittieren
    debug = 0;
  }
  return;
}

