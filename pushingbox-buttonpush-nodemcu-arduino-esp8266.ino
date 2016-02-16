/*Simple Door Bell (Push Button) Notification using pushingbox.
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

// replace with your channel’s thingspeak API key,
String apiKey = ""; //DevID code
const char* ssid = "***"; //SSID of your router
const char* password = ""; //WEP/WPA/WPA2 code for router

const char* server = "api.pushingbox.com";

int buttonPush = 0;

WiFiClient client;

void setup() {
Serial.begin(115200);
delay(10);

WiFi.begin(ssid, password);

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
Serial.println("WiFi connected");
Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


}
void loop() {
  
if (digitalRead(4) == HIGH && buttonPush == 0) {

if (client.connect(server,80)) { 
Serial.println("Connecting");
client.print("GET /pushingbox?devid=");
    client.print(apiKey);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("User-Agent: Arduino");
    client.println();
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  buttonPush = 1;
    }
  
  Serial.println();
  Serial.println("closing connection");
    }
  }

client.stop();
Serial.println("Waiting…");
// thingspeak needs minimum 15 sec delay between updates
delay(1000);
buttonPush = 0;
}
