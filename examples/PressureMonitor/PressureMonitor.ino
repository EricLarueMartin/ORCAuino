#include<ORCAuino.h>
#include<BPS120.h> // https://github.com/EricLarueMartin/BPS120

#include <FlashStorage.h>

const int loopDelay = 20; // delay each loop
const int updatePeriod = 1000; // update every 1000 ms

FlashStorage(flashSaved,bool); // if set to true then settings have been saved
FlashStorage(flashOffset,double);
FlashStorage(flashScaleFactor,double);
FlashStorage(flashDecayTime,double);
FlashStorage(flashDiffMax,int);

double psidMax = -0.15f;
double psidMin = 0.15f;

BPS120 sensor;


void writeSettings() {
  flashSaved.write(true); // indicates settings have been saved
  flashOffset.write(sensor.rawOffset);
  flashScaleFactor.write(sensor.scaleFactor);
  flashDecayTime.write(sensor.decayTime);
  flashDiffMax.write(sensor.diffMax);
}

void readSettings() {
  if (flashSaved.read()){ // indicates settings have been saved
    sensor.rawOffset = flashOffset.read();
    sensor.scaleFactor = flashScaleFactor.read();
    sensor.decayTime = flashDecayTime.read();
    sensor.diffMax = flashDiffMax.read();
  }
}


void setup() {
  Wire.begin();
  Serial.begin(115200); // Arduino Uno, Mega, with AT8u2 USB
  ORCA::init();
  readSettings();
  delay(1500);
}

void loop() {
  ORCA::update();
  static int ctLoop = 0;
  static unsigned long lastUpdate = 0;

  sensor.measure();

  // track max and min since last power cycle
  double psid = sensor.psid();
  if (psid > psidMax) psidMax = psid;
  if (psid < psidMin) psidMin = psid;

  if (millis()-lastUpdate>=updatePeriod && Serial) {
    ORCA::setCustom(0,sensor.Pa());
  }
    
  delay(loopDelay);
  ++ctLoop;

}
