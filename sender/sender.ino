#include <SPI.h>
#include <RF24.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <avr/wdt.h>

#define ONE_WIRE_BUS 2
#define LED_R 5
#define LED_G 6
#define LED_B 7

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
RF24 radio(9, 10);                // CE, CSN
const byte address[6] = "00001";

unsigned long lastRestartCheck = 0;
const unsigned long RESTART_INTERVAL = 86400000UL; // 24 hours

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  setRGB(0, 0, 0);

  Serial.begin(115200);
  sensors.begin();
  
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(76);
  radio.openWritingPipe(address);
  radio.stopListening();

  wdt_enable(WDTO_8S);  // Watchdog safety
  Serial.println("Sender started");
  setRGB(0, 255, 0); delay(500); setRGB(0,0,0);
}

void loop() {
  wdt_reset();

  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);

  if (tempC > -55 && tempC < 125) {
    bool success = radio.write(&tempC, sizeof(tempC));
    if (success) {
      Serial.print("Sent: "); Serial.println((int)round(tempC));
      setRGB(0, 255, 0); delay(100); setRGB(0,0,0);
    } else {
      setRGB(255, 0, 0); delay(200); setRGB(0,0,0);
    }
  } else {
    setRGB(255, 0, 0); delay(500); setRGB(0,0,0);
  }

  // Daily restart
  if (millis() - lastRestartCheck > RESTART_INTERVAL) {
    wdt_enable(WDTO_15MS); while(1); // force restart
  }

  delay(60000); // 1 minute
}

void setRGB(uint8_t r, uint8_t g, uint8_t b) {
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}