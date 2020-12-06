// Arduino Menorah

// Menorah pins
// The 1st night of Chanukah is represented by the light on the right-hand side
// of the menorah. However the menorah lights from left to right.
const int kCandleCount = 8;
const int kCandleStart = 2;
const int kShamash = 13;

// The night of Chanukah can be represented as a 3-bit integer who's value can
// be determined by GPIO pin state. For spacing reasons, these 3 bits are
// analog pins being read as digital GPIO pins. In addition to the Chanukah
// night, the menorah is only on when the enable pin is reading high.
const int kEnablePin = A5;
const int kBinaryPinCount = 3;
const int kBinaryPins[kBinaryPinCount] = {A0, A1, A2};

// The interval between checking the enable/night status
const int kIntervalMs = 50;
const int kLightupIntervalMs = 250;

// Transform an 0-7 loop number into the actual menorah pin
// My setup has the highest pin number as the night 1 light
int GetMenorahPin(const int p) { return kCandleStart + kCandleCount - p - 1; }

// Shut off all of the lights
void AllOff() {
  digitalWrite(kShamash, LOW);
  for (int p = 0; p < kCandleCount; p++) {
    digitalWrite(GetMenorahPin(p), LOW);
  }
}

// Get the current night of Chanukah based on GPIO register voltages
int GetNight() {
  int night = 0;
  for (int i = 0; i < kBinaryPinCount; i++) {
    night |= digitalRead(kBinaryPins[i]) << i;
  }

  return night;
}

// Light up the menorah
void LightUp(const int night, const bool lightup_delay) {
  digitalWrite(kShamash, HIGH);
  for (int p = kCandleCount - 1; p >= 0; p--) {
    // Exit the lightup if the enable pin goes low
    if (!digitalRead(kEnablePin)) {
      return;
    }

    int pin = GetMenorahPin(p);
    if (p > night) {
      digitalWrite(pin, LOW);
    } else {
      if (lightup_delay) {
        delay(kLightupIntervalMs);
      }

      digitalWrite(pin, HIGH);
    }
  }
}

void setup() {
  pinMode(kShamash, OUTPUT);
  for (int p = 0; p < kCandleCount; p++) {
    pinMode(GetMenorahPin(p), OUTPUT);
  }
  AllOff();
}

void loop() {
  while (!digitalRead(kEnablePin)) {
    delay(kIntervalMs);
    AllOff();
  }

  int night = GetNight();
  bool light_up = true;
  do {
    delay(kIntervalMs);
    LightUp(night, light_up);
    light_up = false;
  } while (digitalRead(kEnablePin));
}
