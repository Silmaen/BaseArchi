
#include <sbs.h>
#include <sensor/Lps22hb.h>
#include <sensor/Hts221.h>

sbs::sensor::Lps22hb sense;
sbs::sensor::Hts221 sense2;

#include <Arduino.h>

void sbs::setup() {
    Serial.begin(115200);
    while(!Serial.available())
        delay(500);
    Serial.println("Tout systeme top depart");
    // write your initialization code here
    sense.init();
    sense2.init();
    if (!(sense.presence()&&sense2.presence())) {
        Serial.println("Wait for sensors...");
        sense.selfCheck();
        sense2.selfCheck();
        delay(500);
    }
}

void sbs::loop() {
    sense.selfCheck();
    sense2.selfCheck();
    // write your code here
    auto dta = sense.getValue();
    auto dta2 = sense2.getValue();
    Serial.print("Data read: ");
    Serial.print(dta.pressure);
    Serial.print(" hPa & ");
    Serial.print(dta.temperature);
    Serial.print("C ");
    Serial.print(dta.getQnh(294.05));
    Serial.print(" hpa !!! ");
    Serial.print(dta2.temperature);
    Serial.print("C ");
    Serial.print(dta2.humidity);
    Serial.println("% ");
    delay(1000);
}
