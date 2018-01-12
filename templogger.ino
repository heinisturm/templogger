#include <OneWire.h>
#include <DallasTemperature.h>
#include <EEPROM.h>

#define ONE_WIRE_BUS 2

#define PIN_ERASE 12
#define PIN_SHOW  10
#define PIN_DUMMY 11
#define PIN_LED   13

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// the current address in eeprom
int addr = 0;

bool stop = false;

void setup() {
  Serial.begin(9600);
  sensors.begin();

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_ERASE, INPUT_PULLUP);
  pinMode(PIN_SHOW, INPUT_PULLUP);
  pinMode(PIN_DUMMY, INPUT_PULLUP);

  digitalWrite(PIN_LED, 0);
}

void loop() {
  int temp;

  if (!stop) {
    if (digitalRead(PIN_ERASE) == 0) {
      Serial.print("EEPROM size is: ");
      Serial.println(EEPROM.length());
      Serial.print("erase eeprom... ");
      for (int i = 0; i < EEPROM.length(); i++)
        EEPROM.write(i, 0xff);
      Serial.println("done");
      digitalWrite(PIN_LED, 1);
      stop = true;

    } else if (digitalRead(PIN_SHOW) == 0) {
      Serial.println("show temperature log");
      for (int i = 0; i < EEPROM.length(); i += 2) {
        temp = EEPROM.read(i) << 8 | EEPROM.read(i + 1);
        Serial.println(temp);
      }

      digitalWrite(PIN_LED, 1);
      stop = true;
    } else {
      sensors.requestTemperatures();
      temp = sensors.getTempCByIndex(0) * 100;
      EEPROM.write(addr, temp >> 8);
      EEPROM.write(addr + 1, temp & 0xff);
      addr += 2;
      if (addr >= EEPROM.length()) {
        stop = true;
      }
      Serial.println(temp);

      delay(60000);
    }
  }
}
