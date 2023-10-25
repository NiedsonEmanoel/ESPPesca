

#include <FS.h>
#include <ArduinoJson.h>
#include "languages.h"
#include "config.h"
#include "functions.h"
#include "ledmsg.h"

#include "filesystem.h"


#include "jsonfiles.h"
#include "webfiles.h"

#include "servingWebPages.h"

#define LED 2

#include <Wire.h>  //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA
 
LiquidCrystal_I2C lcd(0x3F, 16, 2);

unsigned long previousMillisLoop = 0;        // will store last time LED was updated

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  pinMode(15,OUTPUT);
  pinMode(13,OUTPUT);

  digitalWrite(LED, 1);
  digitalWrite(13, 1);

  delay(100);
  digitalWrite(LED, 0);
  digitalWrite(13, 0);

  lcd.init();
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO) 
  lcd.clear();
  
  startSPIFFS();
  logging("");
  logging("");
  logging("------ BOOTING ------");
  logging("");

  logging("setup :: Initialising File System... Success!");


  logging("setup :: Starting LoadConfig...");
  loadSettingJSON();
  createSystemJSON();
  logging("setup :: loadSettingJSON DONE");
  // put your setup code here, to run once:
  logging("setup :: Starting copyWebFiles ...");
  copyWebFiles(true);
  logging("setup :: copyWebFiles DONE");

  logging("setup :: Starting copyWebFiles ...");  
  startAP();
  logging("setup :: startAP DONE");

  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(" REDE  INICIADA ");


  digitalWrite(LED, 1);
  delay(500);
  digitalWrite(LED, 0);
  delay(500);
  digitalWrite(LED, 1);
  delay(500);
  digitalWrite(LED, 0);
  delay(500);
  digitalWrite(LED, 1);
  delay(500);
  digitalWrite(LED, 0);
}

void loop() {
//  ftpSrv.handleFTP();
  dnsServer.processNextRequest();
  server.handleClient();
  httpServer.handleClient();
  ledmsgvoid();



  // constants won't change:


  unsigned long currentMillisLoop = millis();

  if (currentMillisLoop - previousMillisLoop >= 2000) {
    previousMillisLoop = currentMillisLoop;
    client_status();

  }






}
