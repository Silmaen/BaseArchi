
#include <time/timing.h>
#include <core/Print.h>
#include <sbs.h>
#include <shield/MKREnv.h>

sbs::shield::MKREnv ENV;

void sbs::setup() {
    ENV.Init();
}

void sbs::loop() {
    auto data = ENV.getData();
    sbs::io::logger("Measure: T=");
    sbs::io::logger(data.Temperature);
    sbs::io::logger("C P=");
    sbs::io::logger(data.Pressure);
    sbs::io::logger("hPa H=");
    sbs::io::logger(data.Humidity);
    sbs::io::logger("% UVA=");
    sbs::io::logger(data.UVa);
    sbs::io::logger(" UVB=");
    sbs::io::logger(data.UVb);
    sbs::io::logger(" Illum=");
    sbs::io::logger(data.Illuminance);
    sbs::io::logger("\n");
    sbs::time::delay(500);
}
