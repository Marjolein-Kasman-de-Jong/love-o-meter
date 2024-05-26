const int sensorPin = A0;
float baselineTemp = 0;

// Get temperature in Celsius from analog sensor
float getTemperature() {
  float temperature = (((analogRead(sensorPin) / 1024.0) * 5.0) - .5) * 100;
  return temperature;
}

void setup() {
  // Open serial port
  Serial.begin(9600);

  // Configure digital pin 2, 3 and 4 to be outputs and set initial value of each pin to LOW
  for (int pinNumber = 2; pinNumber < 5; pinNumber++) {
    pinMode(pinNumber, OUTPUT);
    digitalWrite(pinNumber, LOW);
  }

  // Set baseline temperature
  for (int measurement = 1; measurement < 100; measurement++) {
    float temperature = getTemperature();
    baselineTemp = baselineTemp + temperature;
  }

  baselineTemp = baselineTemp / 100;
}

void loop() {
  // Get temperature in Celsius from analog sensor
  float temperature = getTemperature();

  // Print baseline temperature in serial monitor
  Serial.println(baselineTemp);
  
  // Print measured temperature in serial monitor
  Serial.println(temperature);

  // Light LEDs
  if (temperature < baselineTemp + 3) {
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp + 3 && temperature < baselineTemp + 6) {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp + 6 && temperature < baselineTemp + 9) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
  } else if (temperature >= baselineTemp + 9) {
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
  }

  delay(1);
}