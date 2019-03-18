const double C = 255.0; // 用いるLEDに依存する定数

int lightPin = 0;    // LED connected to digital pin 9
int ledPin = 1;    // LED connected to digital pin 9
int button = 2;

void setup() {
  // nothing happens in setup
  pinMode(button, INPUT_PULLUP);

  fade(0, 255);

}

void loop() {
  while (digitalRead(button)) {
    delay(200);
  }
  fade(250, 200);

  while (digitalRead(button)) {
    delay(200);
  }
  fade(200, 100);

  while (digitalRead(button)) {
    delay(200);
  }
  fade(100, 0);
  digitalWrite(lightPin,LOW);
  

  while (digitalRead(button)) {
    delay(200);
  }
  fade(0, 255);

}

void fade(int from, int to) {

  if (from < to) {
    for (int i = from ; i <= to; i += 1) {
      analogWrite(lightPin, getDuty(i));
      // wait for 30 milliseconds to see the dimming effect
      delay(5);
    }
  } else {
    for (int i = from ; i >= to; i -= 1) {
      analogWrite(lightPin, getDuty(i));
      // wait for 30 milliseconds to see the dimming effect
      delay(5);
    }

  }

}

int getDuty(double ratio) {
  return round(exp(log(255.0) - (1 - (ratio / 255.0)) * log(C)));
}

