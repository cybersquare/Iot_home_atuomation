

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

//Firebase settings
#define FIREBASE_HOST  "iothomeautomation-eaf2d.firebaseio.com"
#define FIREBASE_AUTH "KVOpc7gBgIjWgYT3q7C0q85lqkdtJQ61JnzsVBQP"
                     
// wifi settings
#define WIFI_SSID  "OnePlus 6T"
#define WIFI_PASSWORD  "12345678"

void setup() {
  // put your setup code here, to run once:
  Serial.println("Starting IoT program");
  Serial.begin(115200);
  delay(1000);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to: ");
  Serial.print(WIFI_SSID);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to");
  Serial.println(WIFI_SSID);
  Serial.print("IP address is: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  delay(500);
  Serial.print("Failed is:");
  Serial.println(Firebase.failed());
  Serial.print("Error is:");
  Serial.println(Firebase.error());
  Serial.print("Success is:");
  Serial.println(Firebase.success());
  
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  
}

void loop() {
  if(Firebase.success()){

    if(Firebase.getString("iot/bulb_bed_room")=="true"){
      digitalWrite(0, HIGH);
      Serial.println("Light ON");
    }
    else{
      digitalWrite(0, LOW);
      Serial.println("Light OFF");
    }

    if(Firebase.getString("iot/fan_living_room")=="true"){
      digitalWrite(1, HIGH);
      Serial.println("Fan ON");
    }
    else{
      digitalWrite(1, LOW);
      Serial.println("Fan OFF");
    }
  }
  else{
    Serial.println("Error");
  }
}
