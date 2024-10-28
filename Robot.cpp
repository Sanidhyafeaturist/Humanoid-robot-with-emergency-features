#include <Servo.h>
#include <Wire.h>
#include <NewPing.h>
#include <TinyGsmClient.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Define pins for the ultrasonic sensor
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200

// Define pins for motor control (ESC for flying, servos for walking)
#define ESC1_PIN 9 // Motor 1 (thrust)
#define ESC2_PIN 10 // Motor 2 (thrust)
#define SERVO1_PIN 11 // Leg servo 1
#define SERVO2_PIN 12 // Leg servo 2

// Define pins for sensors
#define IR_SENSOR_PIN A0 // Analog pin for fire detection
#define SOUND_SENSOR_PIN A1 // Analog pin for sound detection

// GSM module configuration
#define SerialMon Serial
#define SerialAT Serial1 // Adjust if using different serial ports
TinyGsmClient gsmClient(SerialAT);
const char* apn = "your_apn"; // Your APN
const char* user = ""; // APN user
const char* pass = ""; // APN password
const char* phoneNumber = "+1234567890"; // Emergency number

// GPS setup
TinyGPSPlus gps;
SoftwareSerial gpsSerial(4, 3); // RX, TX for GPS module

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

Servo legServo1;
Servo legServo2;

void setup() {
    SerialMon.begin(9600);
    SerialAT.begin(9600);
    gpsSerial.begin(9600);
    
    // Initialize GSM module
    SerialMon.println("Initializing GSM...");
    if (!gsmClient.init()) {
        SerialMon.println("Failed to initialize GSM module!");
        while (true);
    }
    SerialMon.println("GSM initialized.");

    // Attach leg servos
    legServo1.attach(SERVO1_PIN);
    legServo2.attach(SERVO2_PIN);
    
    // Set ESCs to idle
    pinMode(ESC1_PIN, OUTPUT);
    pinMode(ESC2_PIN, OUTPUT);
    analogWrite(ESC1_PIN, 0);
    analogWrite(ESC2_PIN, 0);
}

void loop() {
    // Autonomous decision-making
    if (canFly()) {
        fly();
    } else {
        walk();
    }

    // Measure distance to detect obstacles
    unsigned int distance = sonar.ping();
    SerialMon.print("Distance: ");
    SerialMon.print(distance / US_ROUNDTRIP_CM);
    SerialMon.println(" cm");

    // Check for emergencies based on sensors
    if (detectFire() || detectAccident()) {
        callEmergencyServices();
    }

    // Read GPS data
    while (gpsSerial.available()) {
        gps.encode(gpsSerial.read());
    }

    delay(200); // Delay for stability
}

void walk() {
    SerialMon.println("Walking...");
    // Basic walking logic: alternate leg movement
    for (int step = 0; step < 2; step++) { // Simulate two steps
        legServo1.write(30); // Move leg up
        legServo2.write(150); // Move other leg down
        delay(500);
        legServo1.write(150); // Move leg down
        legServo2.write(30); // Move other leg up
        delay(500);
    }
}

bool detectFire() {
    int irValue = analogRead(IR_SENSOR_PIN);
    if (irValue > 500) { // Adjust threshold for fire detection
        SerialMon.println("Fire detected!");
        return true;
    }
    return false;
}

bool detectAccident() {
    int soundValue = analogRead(SOUND_SENSOR_PIN);
    if (soundValue > 600) { // Adjust threshold for accident detection
        SerialMon.println("Accident detected!");
        return true;
    }
    return false;
}

void callEmergencyServices() {
    SerialMon.println("Calling emergency services...");

    // Ensure GPS data is available
    if (gps.location.isValid()) {
        String location = "Lat: " + String(gps.location.lat(), 6) + 
                          ", Lon: " + String(gps.location.lng(), 6);
        String emergencyType = "Fire or Accident";

        // Send SMS to emergency number
        if (gsmClient.connect()) {
            gsmClient.println("AT+CMGF=1"); // Set SMS mode
            delay(100);
            gsmClient.println("AT+CMGS=\"" + String(phoneNumber) + "\""); // Set recipient
            delay(100);
            gsmClient.print("Emergency detected: " + emergencyType + "\n");
            gsmClient.print("Location: " + location + "\n");
            delay(100);
            gsmClient.write(26); // Send Ctrl+Z to send SMS
            SerialMon.println("Emergency services notified.");
        } else {
            SerialMon.println("Failed to connect to GSM module.");
        }
    } else {
        SerialMon.println("GPS location not available.");
    }
}
