#include "GPRSL.h"
#include "Arduino.h"
#include "LGPRS.h"      
#include "LGPRSClient.h"

LGPRSClient globalClient;
int count = 0;

GPRSL::GPRSL()
{
 
}
void GPRSL::START(){
  // setup Serial port
  Serial.println("Attach to GPRS network");                         // Attach to GPRS network - need to add timeout
  while (!LGPRS.attachGPRS("internet2.voicestream.com","","")) {     //attachGPRS(const char *apn, const char *username, const char *password);
    delay(500);
  }
  LGPRSClient client;    //Client has to be initiated after GPRS is established with the correct APN settings - see above link
  globalClient = client;  // Again this is a temporary solution described in support forums
}

String GPRSL::POST(String var, char server[], char path[], char token[])
{
char action[] = "POST ";
int port = 80; // HTTP
  
    String le= String(var.length());                 //this is to calcule the length of var
    Serial.print("Connect to ");    // For the console - show you are connecting
    Serial.println(server);
   
    if (globalClient.connect(server, port)){  // if you get a connection, report back via serial:
      Serial.println("connected");  // Console monitoring
      Serial.print(action);                   // These commands build a JSON request for Ubidots but fairly standard
      Serial.print(path);                     // specs for this command here: http://ubidots.com/docs/api/index.html
      Serial.println(" HTTP/1.1");
      Serial.println(F("Content-Type: application/json"));
      Serial.print(F("Content-Length: "));
      Serial.println(le);
      Serial.print(F("X-Auth-Token: "));
      Serial.println(token);
      Serial.print(F("Host: "));
      Serial.println(server);
      Serial.println();
      Serial.println(var);  // The payload defined above
      Serial.println();
      Serial.println((char)26); //This terminates the JSON SEND with a carriage return
      globalClient.print(action);                   // These commands build a JSON request for Ubidots but fairly standard
      globalClient.print(path);                     // specs for this command here: http://ubidots.com/docs/api/index.html
      globalClient.println(" HTTP/1.1");
      globalClient.println(F("Content-Type: application/json"));
      globalClient.print(F("Content-Length: "));
      globalClient.println(le);
      globalClient.print(F("X-Auth-Token: "));
      globalClient.println(token);
      globalClient.print(F("Host: "));
      globalClient.println(server);
      globalClient.println();
      globalClient.println(var);  // The payload defined above
      globalClient.println();
      globalClient.println((char)26); //This terminates the JSON SEND with a carriage return
      count = 0;
      String serverreply = "";
      while(count < 13){
        if(globalClient.available()){
          char c = globalClient.read();
          if(count > 8 && count < 12){
            serverreply = serverreply + c;
          }
          count++;
        }
      }
      return serverreply;
    }

  }