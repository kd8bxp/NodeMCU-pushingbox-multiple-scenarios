/* Multiple Water Level Scenarios/Notification using pushingbox.
 * Based on ESP8266 Client (From library Examples)
 * and Clement87 PushingBox for Arduino official ethernet code
 * 
 * By LeRoy Miller, Copywrite 2016
 * 
 */

/*This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses
*/
 
#include <ESP8266WiFi.h>

String apiKey;
String lowWaterKey = ""; //scenario 1 - low water deviceID
String medWaterKey = ""; //scenario 2 - med. water deviceID
String highWaterKey = ""; //scenario 3 - high water deviceID

const char* ssid = "linksys";
const char* password = "";

const char* server = "api.pushingbox.com";

WiFiClient client;

void notifry() {
  if (client.connect(server,80)) { 
Serial.println("Connecting");
client.print("GET /pushingbox?devid=");
    client.print(apiKey);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: Arduino");
    client.println();
  }
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
     }
  
  Serial.println();
  Serial.println("closing connection");
    }

void setup() {
Serial.begin(115200);
delay(10);

WiFi.begin(ssid, password);

Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);

WiFi.begin(ssid, password);

pinMode(12, INPUT); //PIN D6
pinMode(4, INPUT); //PIN D2
pinMode(13, INPUT); //PIN D7

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  
if (digitalRead(4) == LOW) {
  apiKey = lowWaterKey;
  notifry();
  }

if (digitalRead(12) == LOW) {
  apiKey = medWaterKey;
  notifry();
}

if (digitalRead(13) == LOW) {
  apiKey = highWaterKey;
  notifry();
}

client.stop();
Serial.println("Waiting…");

delay(1000);

}





