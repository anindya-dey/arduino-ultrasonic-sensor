#include <Arduino.h>
#include <NewPing.h>
#include <DHT.h>

// HC-SR04 = Ultrasonic Sensor (used for measuring distance)
// It has 4 pins:
//   - Vcc  -> Input voltage
//   - Trig -> Trigger (Output Signal)
//   - Echo -> Echo (Input Signal reflected back from an object in front)
//   - Gnd  -> Ground
// If Echo recieves a pulse of 38 us width, there is no object in front

// We can use the same pin for both trigger and echo.
// If we use same pin for these two, the HC-SR02 is said to be in 3-pin mode
#define TRIGGER_PIN 10
#define ECHO_PIN 13
#define MAX_DISTANCE_CM 400

#define LED_INDICATOR 8
#define MIN_DISTANCE_CM 10

#define DHT_PIN 7
#define DHT_TYPE DHT11

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE_CM);
DHT dht(DHT_PIN, DHT_TYPE);


float duration;     // HC-SR04 echo receive duration
float distance;     // distance in cm
float temperature;  // temperature in celcius
float humidity;     // humidity in percentage
float sound_m;      // speed of sound in m/s
float sound_cm;     // speed of sound in cm/ms
int iterations = 5; // iterations to calculate echo duration of HC-SR02

void setup() {
  Serial.begin(9600);
  pinMode(LED_INDICATOR, OUTPUT);
  dht.begin();
}

void loop() {
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("\u00B0C, Humidity: "); // \u00B0 = Unicode for degree symbol (Refer https://unicodeplus.com/U+00B0)
  Serial.print(humidity);
  Serial.print(" %");

  // calculate actual speed of sound for a given temperature and humidity
  sound_m = 331.4 + (0.606 * temperature) + (0.0124 * humidity);

  Serial.print(", Sound: ");
  Serial.print(sound_m);
  Serial.print(" m/s");

  // convert speed of sound from m/s to cm/ms
  sound_cm = sound_m / 10000;

  // calculate duration of echoes from HC-SR02 using median value
  duration = sonar.ping_median(iterations);

  // calculate distance (in cm) of object from HC-SR02 
  distance = (duration / 2) * 0.0343;

  // Send results to Serial Monitor
  Serial.print(", Distance = ");
  Serial.print(distance);
  Serial.print(" cm");
  if (distance >= MAX_DISTANCE_CM) {
    Serial.print(" - Out of Range");
  }
  Serial.println();

  // if distance is less than a minimum value, turn on LED indicator
  if (distance < MIN_DISTANCE_CM) {
    digitalWrite(LED_INDICATOR, HIGH);
  } else {
    digitalWrite(LED_INDICATOR, LOW);
  }

  delay(1000);
}