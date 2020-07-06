#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define DEBUG 1
#define BAUDRATE 115200

// pinout suitable for bare ESP-7 or ESP-12 (JTAG pins on one side, direct to xilinx 14-pin)
enum { TDO=12, TDI=13, TCK=14, TMS=16, TRST=4, SRST=5, TXD=1, RXD=3, LED=15 };
enum { MODE_JTAG=0, MODE_SERIAL=1 };
uint8_t mode = MODE_JTAG; // initial input parser mode is JTAG (remote bitbang)

// WEBSERVER START -----------------------------------------------------------------
ESP8266WebServer webserver(80);
const char* password_AP = "12345678";
/* const int led = LED_BUILTIN; */
const String postForm = "<html>\
  <head>\
    <meta name=\"viewport\" content=\"width=device-width, initial-scale=2\">\
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
      <label for=\"satatus\">Get WiFi status:</label><br>\
      <input type=\"submit\" value=\"Submit\">\
    </form>\
  </body>\
</html>";

void handleRoot()
{
  digitalWrite(LED, 1);
  webserver.send(200, "text/html", postForm);
  digitalWrite(LED, 0);
}

void handlePlain()
{
  String message;
  if(WiFi.SSID() != NULL)
  {
    message += "SSID: "+WiFi.SSID()+"\n";
  }
  if (webserver.method() != HTTP_POST) {
    digitalWrite(LED, 1);
    webserver.send(405, "text/plain", "Method Not Allowed");
    digitalWrite(LED, 0);
  } else
  {

#ifdef DEBUG == 1
    Serial.println("Get status");
#endif
    digitalWrite(LED, 1);
    if(WiFi.status() != WL_CONNECTED)
    {
#ifdef DEBUG == 1
      Serial.println("Connection FAIL !!!");
#endif
      webserver.send(200, "text/plain", "Connection FAIL!!!\n" + message);
      digitalWrite(LED, 0);
    }else
    {
      message += "Successful!!! \nIP: " + WiFi.localIP().toString()+"\n";
#ifdef DEBUG == 1
      Serial.println(message);
#endif
      webserver.send(200, "text/plain", message);
      digitalWrite(LED, 0);
    }
  }
}

void handleForm()
{
  if (webserver.method() != HTTP_POST)
  {
    digitalWrite(LED, 1);
    webserver.send(405, "text/plain", "Method Not Allowed");
    digitalWrite(LED, 0);
  } else
  {
    digitalWrite(LED, 1);
    String message = "Connecting:\n";
    for (uint8_t i = 0; i < webserver.args(); i++)
    {
      message += " " + webserver.argName(i) + ": " + webserver.arg(i) + "\n";
    }
    if(webserver.arg(0) != NULL && webserver.arg(1) != NULL)
    {
      // UNE_HFC_EA1F XQIDC9HE
      String ssid_ST = webserver.arg(0);
      String password_ST = webserver.arg(1);
      webserver.send(200, "text/plain", message);
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
      digitalWrite(LED, 0);
    } else
    {
      webserver.send(200, "text/plain", "Invalid arguments!!!");
      digitalWrite(LED, 0);
    }
  }
}

void handleNotFound()
{
  digitalWrite(LED, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += webserver.uri();
  message += "\nMethod: ";
  message += (webserver.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webserver.args();
  message += "\n";
  for (uint8_t i = 0; i < webserver.args(); i++) {
    message += " " + webserver.argName(i) + ": " + webserver.arg(i) + "\n";
  }
  webserver.send(404, "text/plain", message);
  digitalWrite(LED, 0);
}
// WEBSERVER END

// JTAG START -----------------------------------------------------------------
// 0: don't use additional TX
// 1: use additional TX at GPIO2
// this option currently doesn't work, leaving it 0
#define TXD_GPIO2 0

//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 2

WiFiServer server(3335);
WiFiClient serverClients[MAX_SRV_CLIENTS];

// led logic
#define LED_ON LOW
#define LED_OFF HIGH
#define LED_DIM INPUT_PULLUP

uint8_t jtag_state = 0; // 0:jtag_off 1:jtag_on, initial is jtag_off

// activate JTAG outputs
void jtag_on(void)
{
  // Serial.println("jtag on");
  pinMode(TDO, INPUT);
  pinMode(TDI, OUTPUT);
  pinMode(TMS, OUTPUT);
  pinMode(TRST, OUTPUT);
  pinMode(SRST, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(TCK, OUTPUT);
  jtag_state = 1;
}

// deactivate JTAG outputs: all pins input
void jtag_off(void)
{
  // Serial.println("jtag off");
  pinMode(TCK, INPUT);
  pinMode(TDO, INPUT);
  pinMode(TDI, INPUT);
  pinMode(TMS, INPUT);
  pinMode(TRST, INPUT);
  pinMode(SRST, INPUT);
  digitalWrite(LED, LED_OFF);
  pinMode(LED, INPUT);
  jtag_state = 0;
}

uint8_t jtag_read(void)
{
  return digitalRead(TDO);
}

void jtag_write(uint8_t tck_tms_tdi)
{
  digitalWrite(TDI, tck_tms_tdi & 1 ? HIGH : LOW);
  digitalWrite(TMS, tck_tms_tdi & 2 ? HIGH : LOW);
  digitalWrite(TCK, tck_tms_tdi & 4 ? HIGH : LOW);
}

void jtag_reset(uint8_t trst_srst)
{
  digitalWrite(SRST, trst_srst & 1 ? HIGH : LOW);
  digitalWrite(TRST, trst_srst & 2 ? HIGH : LOW);
}

void serial_break()
{
  pinMode(LED, LED_DIM);
  digitalWrite(LED, LED_ON);
  if(TXD == 15)
    Serial.swap();
  Serial.end(); // shutdown serial port
  #if TXD_GPIO2
  // if we want to drive additional tx line
  Serial1.end(); // shutdown it too
  #endif
  pinMode(TXD, OUTPUT);
  digitalWrite(TXD, LOW); // TXD line LOW for 200ms is serial break
  #if TXD_GPIO2
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  #endif
  delay(210); // at least 200ms we must wait for BREAK to take effect
  Serial.begin(BAUDRATE); // start port just before use
  // remove serial break either above or after swap
  if(TXD == 15)
    Serial.swap();
  #if TXD_GPIO2
  Serial1.begin(BAUDRATE); // port started, break removed at GPIO2 (will now become serial TX)
  #endif
  pinMode(LED, INPUT);
  digitalWrite(LED, LED_OFF);
  Serial.flush();
}

void tcp_parser(WiFiClient *client)
{
  if(mode == MODE_JTAG)
  {
    char c = client->read();
    switch(c)
    {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
        jtag_write(c & 7); // it's the same as ((c-'0') & 7)
        break;
      case 'R':
        client->write('0'+jtag_read());
        break;
      case 'r':
      case 's':
      case 't':
      case 'u':
        jtag_reset((c-'r') & 3);
        break;
      case 'B':
        if(jtag_state == 0)
          jtag_on();
        digitalWrite(LED, LED_ON);
        break;
      case 'b':
        digitalWrite(LED, LED_OFF);
        break;
      case '\0': // ctrl-@ (byte 0x00) sends serial BREAK
        serial_break();
        break;
      case '\r': // press enter to tcp-serial mode
        jtag_off();
        mode = MODE_SERIAL;
        break;
      case 'Q':
        jtag_off();
        client->stop(); // disconnect client's TCP
        break;
    } /* end switch */
  } // end mode == JTAG
  else
  {
    // get data from the telnet client and push it to the UART
    if(mode == MODE_SERIAL)
    {
      pinMode(LED, OUTPUT);
      digitalWrite(LED, LED_ON);
      Serial.write(client->read());
      digitalWrite(LED, LED_OFF);
    }
  }
}
// JTAG END

void setup()
{
  // WEBSERVER -----------------------------------------------------------------
  pinMode(LED, OUTPUT);
  digitalWrite(LED, 0);
  Serial.begin(BAUDRATE);

  byte mac[6];
  WiFi.macAddress(mac);

  char ssid_AP[9];
  sprintf(ssid_AP, "jtag_%x%x", mac[4], mac[5]);
#ifdef DEBUG == 1
  Serial.println(ssid_AP);
#endif
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid_AP, password_AP);
  WiFi.setAutoReconnect(true);

  webserver.on("/", handleRoot);
  webserver.on("/postplain/", handlePlain);
  webserver.on("/postform/", handleForm);
  webserver.onNotFound(handleNotFound);
  webserver.begin();

#ifdef DEBUG == 1
  Serial.println("HTTP server started");
#endif

  // JTAG ----------------------------------------------------------------------
  jtag_off();
  pinMode(LED, OUTPUT);
  Serial.begin(BAUDRATE);
  if(TXD == 15)
    Serial.swap();
  server.begin();
  server.setNoDelay(true);
#ifdef DEBUG == 1
  Serial1.println("Ready! To connect, use:");
  Serial1.print("telnet ");
  Serial1.print(WiFi.localIP());
  Serial1.println(" 3335");
#endif
}

void loop()
{
  // WEBSERVER -----------------------------------------------------------------
  webserver.handleClient(); 
  // JTAG ----------------------------------------------------------------------
  uint8_t i;
  //check if there are any new clients
  if (server.hasClient()){
    for(i = 0; i < MAX_SRV_CLIENTS; i++){
      //find free/disconnected spot
      if (!serverClients[i] || !serverClients[i].connected()){
        if(serverClients[i]) serverClients[i].stop();
        serverClients[i] = server.available();
        Serial1.print("New client: "); Serial1.print(i);
        mode = MODE_JTAG;
        if(jtag_state == 0)
          jtag_on();
        continue;
      }
    }
    //no free/disconnected spot so reject
    WiFiClient serverClient = server.available();
    serverClient.stop();
  }
  //check clients for data
  for(i = 0; i < MAX_SRV_CLIENTS; i++){
    if (serverClients[i] && serverClients[i].connected()){
      if(serverClients[i].available()){
        //get data from the telnet client and push it to the UART
        // while(serverClients[i].available()) Serial.write(serverClients[i].read());
        while(serverClients[i].available()) tcp_parser(&(serverClients[i]));
      }
    }
  }
  //check UART for data
  if(Serial.available()){
    size_t len = Serial.available();
    uint8_t sbuf[len];
    Serial.readBytes(sbuf, len);
    //push UART data to all connected telnet clients
    for(i = 0; i < MAX_SRV_CLIENTS; i++){
      if (mode == MODE_SERIAL)
      {
        if (serverClients[i] && serverClients[i].connected()){
          pinMode(LED, LED_DIM);
          serverClients[i].write(sbuf, len);
          delay(1);
          pinMode(LED, INPUT);
        }
      }
    }
  }
}
