#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* #define LIMIT_ATTEMPS 5 */
#define DEBUG 1

ESP8266WebServer server(80);


/* const char* ssid_AP = "jtag"; */
const char* password_AP = "12345678";

const int led = LED_BUILTIN;

const String postForm = "<html>\
  <head>\
    <title>ESP8266 Web Server POST handling</title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>Connect to network</h1><br>\
    <form method=\"post\" enctype=\"application/x-www-form-urlencoded\" action=\"/postform/\">\
      <label for=\"netword\">SSID:</label><br>\
      <input type=\"text\" name=\"ssid\" value=\"name_ssid\"><br>\
      <label for=\"pass\">Password:</label><br>\
      <input type=\"text\" name=\"password\" value=\"password\"><br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
    <h1>Network status</h1><br>\
    <form method=\"post\" enctype=\"text/plain\" action=\"/postplain/\">\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
  </body>\
</html>";

void handleRoot()
{
  digitalWrite(led, 1);
  server.send(200, "text/html", postForm);
  digitalWrite(led, 0);
}

void handlePlain()
{
  String message;
  if(WiFi.SSID() != NULL)
  {
    message += "SSID: "+WiFi.SSID()+"\n";
  }
  if (server.method() != HTTP_POST) {
    digitalWrite(led, 1);
    server.send(405, "text/plain", "Method Not Allowed");
    digitalWrite(led, 0);
  } else
  {
    digitalWrite(led, 1);
    if(WiFi.status() != WL_CONNECTED)
    {
      server.send(200, "text/plain", "Connection FAIL!!!\n" + message);
      digitalWrite(led, 0);
    }else
    {
      message += "IP: " + WiFi.localIP().toString()+"\n";
      server.send(200, "text/plain", message);
      digitalWrite(led, 0);
    }
  }
}

void handleForm()
{
  if (server.method() != HTTP_POST)
  {
    digitalWrite(led, 1);
    server.send(405, "text/plain", "Method Not Allowed");
    digitalWrite(led, 0);
  } else
  {
    digitalWrite(led, 1);
    String message = "Successful:\n";
    for (uint8_t i = 0; i < server.args(); i++)
    {
      message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
    }
    if(server.arg(0) != NULL && server.arg(1) != NULL)
    {
      // UNE_HFC_EA1F XQIDC9HE
      String ssid_ST = server.arg(0);
      String password_ST = server.arg(1);
      int attemps = 0;
      if(WiFi.status() == WL_CONNECTED)
      {
#ifdef DEBUG == 1
        Serial.println("WiFi disconnecting");
#endif
        WiFi.disconnect();
      }
#ifdef DEBUG == 1
        Serial.println("WiFi station connecting");
#endif
      WiFi.begin(ssid_ST, password_ST);
      while ( WiFi.status() != WL_CONNECTED)
      {
#ifdef DEBUG == 1
        Serial.println(attemps);
#endif
        delay(1000);
        if(attemps == LIMIT_ATTEMPS || WiFi.status() == WL_CONNECTED)
        {
          break;
        }
        attemps++;
      }
      if (WiFi.status() != WL_CONNECTED)
      {
        server.send(200, "text/plain", "Connection FAIL!!!");
      }else
      {
        message += "IP: " + WiFi.localIP().toString();
#if defined(DEBUG)
        Serial.println(WiFi.localIP());
#endif
        server.send(200, "text/plain", message);
        digitalWrite(led, 0);
      }
    }
  }
}

void handleNotFound()
{
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
void setup()
{
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(115200);

  byte mac[6];
  WiFi.macAddress(mac);

  char ssid_AP[9];
  sprintf(ssid_AP, "jtag_%x%x", mac[4], mac[5]);

  Serial.println(ssid_AP);

  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid_AP, password_AP);
  WiFi.setAutoReconnect(true);

  server.on("/", handleRoot);

  server.on("/postplain/", handlePlain);

  server.on("/postform/", handleForm);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop()
{
   server.handleClient(); 
}
