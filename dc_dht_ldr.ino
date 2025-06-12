//#define BLYNK_TEMPLATE_ID "TMPL3jZm4pr3i"
//#define BLYNK_TEMPLATE_NAME "Smart home automation system"
//#define BLYNK_AUTH_TOKEN "Y2w0SFxuwpo6R49hVJfdee9i-zk_0Cap"
#define  BLYNK_AUTH_TOKEN "o0zhLvRmADkNmG7nrJ0cBuorRjMNsph6"
#define BLYNK_TEMPLATE_ID "TMPL3tNZWwYkE"
#define BLYNK_TEMPLATE_NAME "Smart IoT"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

// Wi-Fi credentials
char ssid[] = "Broskii";
char pass[] = "saaakshi";

// Blynk auth
char auth[] = BLYNK_AUTH_TOKEN;

// Pin definitions
#define LDR_PIN 34
#define LED_PIN 18
#define RELAY_PIN 5  // GPIO for Relay module (Fan)

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Virtual pins
#define LDR_VPIN V7
#define LED_STATUS_VPIN V8
#define FAN_CONTROL_VPIN V1
#define TEMP_VPIN V9
#define HUM_VPIN V10

#define TEMP_THRESHOLD 25.0  // Celsius

BlynkTimer timer;

// Read LDR and control LED based on light intensity
void readLDRandControlLED() {
  int ldrValue = analogRead(LDR_PIN);
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  Blynk.virtualWrite(LDR_VPIN, ldrValue);

  if (ldrValue < 800) {
    digitalWrite(LED_PIN, HIGH);
    Blynk.virtualWrite(LED_STATUS_VPIN, 1);
    Serial.println("LED: ON");
  } else {
    digitalWrite(LED_PIN, LOW);
    Blynk.virtualWrite(LED_STATUS_VPIN, 0);
    Serial.println("LED: OFF");
  }
}

// Fan control from Blynk app switch
BLYNK_WRITE(FAN_CONTROL_VPIN) {
  int fanValue = param.asInt();  // 1 = ON, 0 = OFF

  if (fanValue == 1) {
    digitalWrite(RELAY_PIN, LOW);  // Relay ON (active LOW)
    Serial.println("Fan State: ON");
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Relay OFF
    Serial.println("Fan State: OFF");
  }
}

// Read temperature & humidity and send to Blynk
void sendSensorData() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();

  if (isnan(temp) || isnan(hum)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C\tHumidity: ");
  Serial.print(hum);
  Serial.println(" %");

  Blynk.virtualWrite(TEMP_VPIN, temp);
  Blynk.virtualWrite(HUM_VPIN, hum);

  if (temp > TEMP_THRESHOLD) {
    Blynk.logEvent("high_temp", "Temperature is high! Please turn ON the fan.");
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // Ensure fan is off initially

  dht.begin();

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");

  Blynk.begin(auth, ssid, pass);

  timer.setInterval(1000L, readLDRandControlLED);  // Every 1 second
  timer.setInterval(3000L, sendSensorData);        // Every 3 seconds
}

void loop() {
  Blynk.run();
  timer.run();
}
