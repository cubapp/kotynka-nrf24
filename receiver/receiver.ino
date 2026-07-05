#include <SPI.h>
#include <RF24.h>
#include <avr/wdt.h>

#define LED_R 5
#define LED_G 6
#define LED_B 7

RF24 radio(9, 10);
const byte address[6] = "00001";

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  setRGB(0,0,0);

  Serial.begin(115200);
  
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(76);
  radio.openReadingPipe(1, address);
  radio.startListening();

  wdt_enable(WDTO_8S);
  Serial.println("Receiver started");
  setRGB(0, 0, 255); delay(500); setRGB(0,0,0);
}

void loop() {
  wdt_reset();

  if (radio.available()) {
    float temp;
    radio.read(&temp, sizeof(temp));
    
    int tempInt = (int)round(temp);
    Serial.println(tempInt);
    
    // Visual feedback
    setRGB(0, 0, 255); delay(50); setRGB(0,0,0);
  }

  delay(10);
}

void setRGB(uint8_t r, uint8_t g, uint8_t b) {
  analogWrite(LED_R, r);
  analogWrite(LED_G, g);
  analogWrite(LED_B, b);
}