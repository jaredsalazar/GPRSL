#include<LBattery.h>
#include<GPRSL.h>

GPRSL global;

void setup() {
  // put your setup code here, to run once:
global.START();
}

void loop() {
  String value = String(LBattery.level()); //get battery charge level
  String var="{\"value\":"+ value + "}";     //contruct json 
  
  char server[] = "things.ubidots.com";
  char path[] = "/api/v1.6/variables/xxxxxxxxxxxxxxxxxxxx/values";  // Edit Path to include you source key
  char token[] = "xxxxxxxxxxxxxxxxxxxxxxxxx"; //add token here
  
  String response;
  response = global.POST(var,server,path,token);
  
  Serial.println(response);
  delay(10000);
}
