#define TRIGGER_PIN  2
#define ECHO_PIN     3
#define MAX_DISTANCE 400
#define BUZZER_PIN   6
#define GREEN_LED    8
#define RED_LED      12
#define CHECK_INTERVAL 3000
#define DETECTION_TIME 3000
#define ALARM_TIME 3000

unsigned long previousMillis = 0;
int initialDistance;
bool alarmArmed = false;
bool objectDetected = false;
unsigned long objectDetectedStart = 0;

void setup() {
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    // Serial.begin(9600);
    calibrateSensor();
}

void loop() {
    unsigned long currentMillis = millis();
    
    if (alarmArmed) {
        if (currentMillis - previousMillis >= CHECK_INTERVAL) {
            int distance = getDistance();
            if (distance != initialDistance) {
                if (!objectDetected) {
                    objectDetected = true;
                    objectDetectedStart = currentMillis;
                    triggerAlarm();
                }
            } else {
                if (objectDetected) {
                    // Intruder left or never fully detected
                    calibrateSensor();
                }
            }
            previousMillis = currentMillis;
        }
    }
}

void calibrateSensor() {
    digitalWrite(RED_LED, LOW); // Turn off red LED
    digitalWrite(GREEN_LED, HIGH); // Turn on green LED during calibration
    delay(250);  // Calibration time
    initialDistance = getDistance();
    alarmArmed = true;
}

void triggerAlarm() {
    // Prime Alarm with Red LED
    digitalWrite(RED_LED, HIGH);
    
    // Start actively scanning for intruder
    unsigned long alarmStart = millis();
    while (millis() - alarmStart < ALARM_TIME) {        
        int distance = getDistance();
        if (distance == initialDistance) { // If the intruder is gone
            noTone(BUZZER_PIN);
            calibrateSensor();
            return;
        }
    }

    // Intruder hasn't left, trigger alarm
    alarmStart = millis();
    digitalWrite(GREEN_LED, LOW); // Turn off green LED
    while (millis() - alarmStart < ALARM_TIME) {
        tone(BUZZER_PIN, 2000);  // Start buzzer
        delay(250);
        noTone(BUZZER_PIN);  // Stop buzzer
        delay(250);
        
        int distance = getDistance();
        if (distance == initialDistance) { // If the intruder is gone
            noTone(BUZZER_PIN);
            calibrateSensor();
            break;
        }
    }

    noTone(BUZZER_PIN);
    calibrateSensor();
}

int getDistance() {
    // Clears the trigPin condition
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    long duration = pulseIn(ECHO_PIN, HIGH);
    // Calculating the distance
    int distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Serial.print("Distance: ");
    // Serial.println(distance);
    return distance;
}
