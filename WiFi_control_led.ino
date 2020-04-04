#include <ESP8266WiFi.h>
#define led D0
#define led1 D1
#define led2 D2
String ssid = "SINGHAM 1149";
String password = "12345671";
WiFiServer server(80);

void setup() {
  Serial.begin(9600);
  delay(10);
 
  pinMode(led, OUTPUT);
  digitalWrite(led,HIGH);
  pinMode(led2, OUTPUT);
  digitalWrite(led2,HIGH);
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");     
}
  
int value = 0;
int value1 = 1;
int value2 = 1;
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request    
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(led, LOW);
    value = 1;
  }
  else if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(led, HIGH);
    value = 0;
  }else if (request.indexOf("/LED1=ON") != -1)  {
    Serial.println("LED1 is ON");
    digitalWrite(led1, HIGH);
    value1 = 1;
  }else if (request.indexOf("/LED1=OFF") != -1)  {
    Serial.println("LED1 is OFF");
    digitalWrite(led1, LOW);
    value1 = 0;
  }
  else if (request.indexOf("/LED2=ON") != -1)  {
    Serial.println("LED2 is ON");
    digitalWrite(led2, HIGH);
    value2 = 1;
  }
  else if (request.indexOf("/LED2=OFF") != -1)  {
    Serial.println("LED2 is OFF");
    digitalWrite(led2, LOW);
    value2 = 0;
  }


  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("Internal Led is now: ");
  
  if(value == 1) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />"); 
   
  client.println("<br><br>");
  client.print("External Led 1 is now: ");
  
  if(value1 == 1) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED1=ON\"\"><button>Turn External LED 1 On </button></a>");
  client.println("<a href=\"/LED1=OFF\"\"><button>Turn External LED 1 Off </button></a><br />");

  client.println("<br><br>");
  client.print("External Led 2 is now: ");
  
  if(value2 == 1) {
    client.print("On");
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED2=ON\"\"><button>Turn External LED 2 On </button></a>");
  client.println("<a href=\"/LED2=OFF\"\"><button>Turn External LED 2 Off </button></a><br />");

  client.println("</html>");
 
  Serial.println("Client disonnected");
  Serial.println("");
}
