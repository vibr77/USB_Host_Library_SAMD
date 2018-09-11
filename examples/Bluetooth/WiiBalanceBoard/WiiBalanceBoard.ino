/*
 Example sketch for the Wii Balance Board Bluetooth library - developed by Kristian Lauszus
 For more information visit my blog: http://blog.tkjelectronics.dk/ or
 send me an e-mail:  kristianl@tkjelectronics.com
 */

#include <Wii.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USBHost UsbH;
//USBHub Hub1(&UsbH); // Some dongles have a hub inside

BTD Btd(&UsbH); // You have to create the Bluetooth Dongle instance like so
/* You can create the instance of the class in two ways */
WII Wii(&Btd, PAIR); // This will start an inquiry and then pair with your Wii Balance Board - you only have to do this once
//WII Wii(&Btd); // After that you can simply create the instance like so and then press the power button on the Wii Balance Board

void setup() {
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  if (UsbH.Init()) {
    Serial.print(F("\r\nUSB host did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nWii Balance Board Bluetooth Library Started"));
}
void loop() {
  UsbH.Task();
  if (Wii.wiiBalanceBoardConnected) {
    Serial.print(F("\r\nWeight: "));
    for (uint8_t i = 0; i < 4; i++) {
      Serial.print(Wii.getWeight((BalanceBoardEnum)i));
      Serial.print(F("\t"));
    }
    Serial.print(F("Total Weight: "));
    Serial.print(Wii.getTotalWeight());
    if (Wii.getButtonClick(A)) {
      Serial.print(F("\r\nA"));
      //Wii.setLedToggle(LED1); // The Wii Balance Board has one LED as well
      Wii.disconnect();
    }
  }
}