
#include <sbs.h>
#include <sensor/Lps22hb.h>

sbs::sensor::Lps22hb sense;

#include <Arduino.h>

void sbs::setup() {
    // write your initialization code here
    sense.init();
    Serial.begin(115200);
    if (!sense.presence()) {
        Serial.println("Wait for sensor...");
        sense.selfCheck();
        delay(500);
    }
}

void sbs::loop() {
    sense.selfCheck();
    // write your code here
    auto dta = sense.getValue();
    Serial.print("Data read: ");
    Serial.print(dta.pressure);
    Serial.print(" hPa & ");
    Serial.print(dta.temperature);
    Serial.print("C ");
    Serial.print(dta.getQnh(294.05));
    Serial.println(" hpa");
    delay(1000);
}
