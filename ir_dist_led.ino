//#define BLYNK_TEMPLATE_ID "TMPL3jZm4pr3i"
//#define BLYNK_TEMPLATE_NAME "Smart home automation system"
//#define BLYNK_AUTH_TOKEN "Y2w0SFxuwpo6R49hVJfdee9i-zk_0Cap"
#define  BLYNK_AUTH_TOKEN "o0zhLvRmADkNmG7nrJ0cBuorRjMNsph6"
#define BLYNK_TEMPLATE_ID "TMPL3tNZWwYkE"
#define BLYNK_TEMPLATE_NAME "Smart IoT"

#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include <BlynkSimpleEsp32.h>

// WiFi credentials
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Broskii";
char pass[] = "saaakshi";

// Firebase placeholders (not used in this integration, but kept for consistency)
#define API_KEY "v8CAiyo83VmES1qEBjx55ny02F972T1Sqve3TngP"
#define DATABASE_URL "https://ir-sensor-98e58-default-rtdb.asia-southeast1.firebasedatabase.app"
FirebaseData fbdo;
FirebaseAuth authFB;
FirebaseConfig configFB;

// IR Sensor and LED
#define USER_LED_PIN 13       // Controlled via V2
#define IR_SENSOR_PIN 18      // IR sensor input
#define IR_LED_PIN 19         // LED for IR detection

// Ultrasonic Sensor and Buzzer
#define TRIG_PIN 23
#define ECHO_PIN 22
#define BUZZER_PIN 21

long duration;
float distance;

int irValue = 0;

BlynkTimer timer;

// --- BLYNK CONTROL HANDLER ---
BLYNK_WRITE(V2) {
  int ledState = param.asInt();  // LED control from app
  digitalWrite(USER_LED_PIN, ledState);
}

// --- IR SENSOR FUNCTION ---
void readIRSensor() {
  irValue = digitalRead(IR_SENSOR_PIN);

  if (irValue == 0) {
    digitalWrite(IR_LED_PIN, HIGH);
    Serial.println("Object Detected");
    Blynk.virtualWrite(V0, "Object Detected"); // Text on V0
    Blynk.virtualWrite(V1, 1);                 // LED on V1
  } else {
    digitalWrite(IR_LED_PIN, LOW);
    Serial.println("No Object Detected");
    Blynk.virtualWrite(V0, "No Object");
    Blynk.virtualWrite(V1, 0);
  }
}

// --- ULTRASONIC FUNCTION ---
void measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.0343) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Blynk.virtualWrite(V4, distance); // Distance to V4

  if (distance > 0 && distance < 5) {
    digitalWrite(BUZZER_PIN, HIGH);
    Blynk.virtualWrite(V5, 1);      // Object detected
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    Blynk.virtualWrite(V5, 0);      // No object
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Booting Smart Home System...");
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  // Pin setup
  pinMode(USER_LED_PIN, OUTPUT);
  pinMode(IR_SENSOR_PIN, INPUT);
  pinMode(IR_LED_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Connect to WiFi and Blynk
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Connecting to Blynk...");
  Blynk.begin(auth, ssid, pass);
  Serial.println("Blynk Connected!");

  // Schedule both sensor functions
  timer.setInterval(1000L, readIRSensor);
  timer.setInterval(1000L, measureDistance);
}

void loop() {
  Blynk.run();
  timer.run();
}
