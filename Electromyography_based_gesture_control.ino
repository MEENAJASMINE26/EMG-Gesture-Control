const int EMG_PIN = A0;
const int LIGHT_PIN = 3;
const int FAN_PIN = 4;
const int BUZZER_PIN = 5;

const int NUM_SAMPLES = 50;
const unsigned long SAMPLE_DELAY = 10;
const unsigned long DISPLAY_INTERVAL = 500;
float baselineVoltage = 0.0;

float THRESHOLD_LOW_MULT = 1.3;
float THRESHOLD_MID_MULT = 1.8;
float THRESHOLD_HIGH_MULT = 2.3;

float THRESHOLD_LOW;
float THRESHOLD_MID;
float THRESHOLD_HIGH;

void calibrateEMG();
float getFilteredEMG();
void controlDevices(float voltage);
void displayStatus(float voltage, const char* level);
void turnOffAllDevices();

void setup() {
  Serial.begin(9600);
  pinMode(LIGHT_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  turnOffAllDevices();
  Serial.println("===============================================");
  Serial.println(" EMG-Based Gesture Control System - Initializing");
  Serial.println("===============================================");
  Serial.println();
  calibrateEMG();
  THRESHOLD_LOW = baselineVoltage * THRESHOLD_LOW_MULT;
  THRESHOLD_MID = baselineVoltage * THRESHOLD_MID_MULT;
  THRESHOLD_HIGH = baselineVoltage * THRESHOLD_HIGH_MULT;
  Serial.println("Calibration Completed Successfully!");
  Serial.print("Baseline Voltage: "); Serial.print(baselineVoltage); Serial.println(" V");
  Serial.print("Threshold Low : "); Serial.println(THRESHOLD_LOW);
  Serial.print("Threshold Mid : "); Serial.println(THRESHOLD_MID);
  Serial.print("Threshold High: "); Serial.println(THRESHOLD_HIGH);
  Serial.println("-----------------------------------------------");
  delay(2000);
}

void loop() {
  float emgVoltage = getFilteredEMG();
  static unsigned long lastDisplayTime = 0;
  if (millis() - lastDisplayTime >= DISPLAY_INTERVAL) {
    Serial.print("Current EMG Voltage: ");
    Serial.print(emgVoltage, 3);
    Serial.println(" V");
    lastDisplayTime = millis();
  }
  controlDevices(emgVoltage);
  delay(SAMPLE_DELAY);
}

void calibrateEMG() {
  Serial.println("Starting EMG Calibration...");
  Serial.println("Please relax your muscle for 5 seconds...");
  delay(1000);
  float sumVoltage = 0;
  int readings = 0;
  unsigned long startTime = millis();
  while (millis() - startTime < 5000) {
    int sensorValue = analogRead(EMG_PIN);
    float voltage = sensorValue * (5.0 / 1023.0);
    sumVoltage += voltage;
    readings++;
    delay(10);
  }
  baselineVoltage = sumVoltage / readings;
  Serial.print("Baseline (Average Rest Voltage): ");
  Serial.print(baselineVoltage);
  Serial.println(" V");
  Serial.println("Calibration done.\n");
}

float getFilteredEMG() {
  float sum = 0;
  for (int i = 0; i < NUM_SAMPLES; i++) {
    int sensorValue = analogRead(EMG_PIN);
    float voltage = sensorValue * (5.0 / 1023.0);
    sum += voltage;
    delay(SAMPLE_DELAY);
  }
  return (sum / NUM_SAMPLES);
}

void controlDevices(float voltage) {
  if (voltage <= THRESHOLD_LOW) {
    digitalWrite(LIGHT_PIN, HIGH);
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    displayStatus(voltage, "LOW → Light ON");
  }
  else if (voltage > THRESHOLD_LOW && voltage <= THRESHOLD_MID) {
    digitalWrite(LIGHT_PIN, LOW);
    digitalWrite(FAN_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    displayStatus(voltage, "MEDIUM → Fan ON");
  }
  else if (voltage > THRESHOLD_MID && voltage <= THRESHOLD_HIGH) {
    digitalWrite(LIGHT_PIN, HIGH);
    digitalWrite(FAN_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    displayStatus(voltage, "STRONG → Light + Fan ON");
  }
  else {
    digitalWrite(LIGHT_PIN, LOW);
    digitalWrite(FAN_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    displayStatus(voltage, "HIGH → Buzzer ON");
  }
}

void displayStatus(float voltage, const char* level) {
  static String lastStatus = "";
  String current = String(level);
  if (current != lastStatus) {
    Serial.print("Detected Voltage: ");
    Serial.print(voltage, 3);
    Serial.print(" V | Status: ");
    Serial.println(level);
    lastStatus = current;
  }
}

void turnOffAllDevices() {
  digitalWrite(LIGHT_PIN, LOW);
  digitalWrite(FAN_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}
