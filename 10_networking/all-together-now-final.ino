#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
const char* ssid     = "guest";
const char* password = "password";
int red_pin = 5; // in this case, the SCK pin on the Feather
int green_pin = 22; // SCL pin
int blue_pin = 23; // SDA pin
String readString ; // string to hold client input
const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q=";
const String comma = ",";
const String api_setup = "&APPID=";
const String key = "ef20d2683a6976d999ce5afecb8e2d88";
WiFiServer server(80);
void setup()
{
  Serial.begin(115200);
  pinMode(red_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);      
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
int value = 0;
void loop() {
  readString = "";
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);
        if (readString.length() < 135) {
          readString += c;
          //Serial.print(c);
        }
        //Serial.println(readString);
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            // the content of the HTTP response follows the header:
            client.print("<h1>Virtual Weather Station </h1> <form action=\"/responses.php\"> <label for=\"fname\">City:</label> <input type=\"text\" id=\"fname\" name=\"fname\"> <br><br> <label for=\"lname\">Country Code:</label><input type=\"text\" id=\"lname\" name=\"lname\"><br><br><input type=\"submit\" value=\"Submit\"></form> <p>Look up country codes (alpha-2) <a href=\"https://www.nationsonline.org/oneworld/country_code_list.htm\">here</a>!</p><br>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");    
    int index1 = readString.indexOf('=');
    int index2 = readString.indexOf('&');
    int index3 = readString.lastIndexOf('=');
    int index4 = index3 + 1;
    int index5 = index4 + 2;
    String cityName = readString.substring(25, index2);
    String countryName = readString.substring(index4, index5);

    Serial.println(countryName);
    Serial.println(cityName);    
    HTTPClient http;
    http.begin(endpoint + cityName + comma + countryName + api_setup + key);
    int httpCode = http.GET();
    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println(httpCode); // let's see if our API call was successful! Shooting for 200
      // Serial.println(payload); don't want to see the full payload!
      DynamicJsonDocument doc(10000);
      DeserializationError error = deserializeJson(doc, payload);
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
      }
      // Let's move through the Json document! Huzzah!
      const char* desc = doc["weather"][0]["main"];
      const int wind = doc["wind"]["deg"];
      const int temp = doc["main"]["temp"];
      const int temp_f = (temp - 273.15) * (9 / 5) + 32;
      Serial.print("Here's your personalized weather report for ");
      Serial.print(cityName);
      Serial.print("! ");
      Serial.print("It is currently ");
      Serial.print(temp_f);
      Serial.print(" degrees Fahrenheit and ");
      Serial.print(desc);
      Serial.print(".");
      
      if (desc = "Clouds") {
        digitalWrite(red_pin, HIGH);
        digitalWrite(green_pin, HIGH);
        digitalWrite(blue_pin, LOW);
      }
      if (desc = "Clear") {
        digitalWrite(green_pin, HIGH);
      }
      if (desc = "Rain") {
        digitalWrite(red_pin, LOW);
        digitalWrite(green_pin, LOW);
        digitalWrite(blue_pin, HIGH);
      }
      if (desc = "Haze") {
        digitalWrite(red_pin, HIGH);
        digitalWrite(green_pin, LOW);
        digitalWrite(blue_pin, LOW);
      }
      else {
        digitalWrite(red_pin, HIGH);
        digitalWrite(green_pin, LOW);
        digitalWrite(blue_pin, LOW);
      }
    }
    else {
      Serial.println("Error upon HTTP request");
    }
    http.end();
  }
  delay(3000);
} 
