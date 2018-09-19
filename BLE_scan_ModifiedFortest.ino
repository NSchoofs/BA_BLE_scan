/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

int scanTime = 20; //In seconds

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
	void onResult(BLEAdvertisedDevice advertisedDevice) {
		Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());

      /*  
      if (advertisedDevice.haveRSSI()){
        Serial.printf("Rssi: %d \n", (int)advertisedDevice.getRSSI());
      }
      else Serial.printf("\n");
      */
	}
};

void setup() {
	Serial.begin(115200);
	Serial.println("Scanning...");

	BLEDevice::init("");

}

void loop() {

	// --- Start new scan on button press
	Serial.println("Press a button to start the scan...");

	// --- Read all to make sure no old inputs are in buffer
	while (Serial.peek() != -1)
	{
		Serial.read();
	}
	// --- wait for press
	while (!Serial.available());

	Serial.println("");
	Serial.print("scan start - ");
	Serial.println(millis());

	//von Setup in loop verfrachtet
	BLEScan* pBLEScan = BLEDevice::getScan(); //create new scan
	pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
	pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
	BLEScanResults foundDevices = pBLEScan->start(scanTime);
	Serial.print("Devices found: ");
	int deviceCount = foundDevices.getCount();
	Serial.println(deviceCount);
	for (int i = 0; i < deviceCount; i++)
	{
		BLEAdvertisedDevice dev = foundDevices.getDevice(i);
		Serial.print(i + 1);
		Serial.print(". - Name: ");
		//Serial.print("NopeyDopey sonst kein Compilerino");
		Serial.print(dev.getName().c_str());
		Serial.print(" - RSSI: ");
		Serial.println(dev.getRSSI());
	}

	Serial.println("Scan done!");

	Serial.println("");
	Serial.println("");
	Serial.println("");

	delay(500);
}
