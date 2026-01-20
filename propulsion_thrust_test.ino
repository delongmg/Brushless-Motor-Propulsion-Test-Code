#include "HX711.h"

HX711 scale;
float calibration_factor = 1.0;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5000);
  scale.begin(4, 5);  // Asign pins to scale
  Serial.println("Type known mass and press ENTER.");
}

void loop() {

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();

    // Tare
    if (input == "t") {
      scale.tare();
      return;
    }

    // Calibrate
    float known_mass = input.toFloat();
    if (known_mass > 0) {

      delay(200);

      long raw = scale.read_average(20);  // True raw val
      calibration_factor = raw / known_mass;
      scale.set_scale(calibration_factor);

      Serial.print("Calibration factor = ");
      Serial.println(calibration_factor);
      Serial.println("Calibration complete");
    }
  }

  // Read scale
  if (scale.is_ready()) {
    float val = scale.get_units(5);
    Serial.println(val);
  }

  delay(200);
}
