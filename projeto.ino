#include <OneWire.h>
#include <DallasTemperature.h>
#include "thingProperties.h"

const int ONE_WIRE_BUS = 4;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#include "MAX30102_PulseOximeter.h"
PulseOximeter pox;
uint32_t tsLastReport = 0;
// Callback (registered below) fired when a pulse is detected 
void onBeatDetected()
{
    Serial.println("Beat!");
}

void setup() {
  Serial.begin(115200);
  sensors.begin();
  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  

    Serial.print("Initializing..");
    delay(3000);
    // Initialize the PulseOximeter instance
    if (!pox.begin()) {
        Serial.println("FAILED");
        for(;;);
    } else {
        Serial.println("SUCCESS");
    }
    // The default current for the IR LED is 50mA and is changed below
    pox.setIRLedCurrent(MAX30102_LED_CURR_7_6MA);
    // Register a callback for the beat detection
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  pox.update();
  ArduinoCloud.update();
  sensors.requestTemperatures(); 
  
  temp = sensors.getTempCByIndex(0);  
  
  btm = pox.getHeartRate();
  ox2 = pox.getSpO2();
  
  delay(2000);
}
