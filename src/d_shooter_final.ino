

#include <ArduinoBLE.h>

BLEService vestService("1101"); // create service

// create switch characteristic and allow remote device to read and write
BLEByteCharacteristic hapticCharacteristic("2101", BLEWrite);
BLEUnsignedCharCharacteristic batteryLevelChar("2105", BLERead | BLENotify);


int oldBatteryLevel = 0;          // last battery level reading from analog input
unsigned long previousMillis = 0; // last time the battery level was checked, in ms
bool isSubscribed = false;


unsigned long pVestMillis1 = 0; // millis for point 1
unsigned long pVestMillis2 = 0; // millis for point 2
unsigned long pVestMillis3 = 0; // millis for point 3
unsigned long pVestMillis4 = 0; // millis for point 4
unsigned long pVestMillis5 = 0; // millis for point 5
unsigned long pVestMillis6 = 0; // millis for point 6
unsigned long pVestMillis7 = 0; // millis for point 7
unsigned long pVestMillis8 = 0; // millis for point 8
unsigned long pVestMillis9 = 0; // millis for point 9
unsigned long pVestMillis10 = 0; // millis for point 10
unsigned long pVestMillis11 = 0; // millis for point 11
unsigned long pVestMillis12 = 0; // millis for point 12
unsigned long pVestMillis13 = 0; // millis for point 13
unsigned long pVestMillis14 = 0; // millis for point 14
unsigned long pVestMillis15 = 0; // millis for point 15
unsigned long pVestMillis16 = 0; // millis for point 16
unsigned long pVestMillis17 = 0; // millis for point 17
unsigned long pVestMillis18 = 0; // millis for point 18






bool pin1_On = false; // flag to track pin1 trigger status
bool pin2_On = false; // flag to track pin2 trigger status
bool pin3_On = false; // flag to track pin3 trigger status
bool pin4_On = false; // flag to track pin4 trigger status
bool pin5_On = false; // flag to track pin5 trigger status
bool pin6_On = false; // flag to track pin6 trigger status
bool pin7_On = false; // flag to track pin7 trigger status
bool pin8_On = false; // flag to track pin8 trigger status
bool pin9_On = false; // flag to track pin9 trigger status
bool pin10_On = false; // flag to track pin10 trigger status
bool pin11_On = false; // flag to track pin11 trigger status
bool pin12_On = false; // flag to track pin12 trigger status
bool pin13_On = false; // flag to track pin13 trigger status
bool pin14_On = false; // flag to track pin14 trigger status
bool pin15_On = false; // flag to track pin15 trigger status
bool pin16_On = false; // flag to track pin16 trigger status
bool pin17_On = false; // flag to track pin17 trigger status
bool pin18_On = false; // flag to track pin18 trigger status







const int intervals = 300; // how long the haptic vibrate
const int ledPin = 27; // the number of the LED pin


void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  pinMode(ledPin, OUTPUT); // use the LED pin as an output
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(23, OUTPUT);
  



  // begin initialization
  if (!BLE.begin())
  {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1)
      ;
  }

  // set the local name peripheral advertises
  BLE.setLocalName("DVest");
  // set the UUID for the service this peripheral advertises
  BLE.setAdvertisedService(vestService);

  // add the characteristic to the service
  vestService.addCharacteristic(hapticCharacteristic);
  vestService.addCharacteristic(batteryLevelChar);

  // add service
  BLE.addService(vestService);

  batteryLevelChar.writeValue(oldBatteryLevel); // set initial value for this characteristic

  // assign event handlers for connected, disconnected to peripheral
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // assign event handlers for characteristic
  hapticCharacteristic.setEventHandler(BLEWritten, hapticCharacteristicWritten);
  batteryLevelChar.setEventHandler(BLESubscribed, updateBatteryLevel);
  batteryLevelChar.setEventHandler(BLEUnsubscribed, endBatteryLevel);

  // start advertising
  BLE.advertise();

  Serial.println(("Bluetooth® device active, waiting for connections..."));
}

void loop()
{
  /* Read the current voltage level on the A0 analog input pin.
     This is used here to simulate the charge level of a battery.
  */
  unsigned long currentMillis = millis();
  if (isSubscribed)
  { 
    // Serial.println("Subscribed");
    ;
    // if 200ms have passed, check the battery level:
    if (currentMillis - previousMillis >= 10000)
    {
      // Serial.println("HAI");
      previousMillis = currentMillis;
      int battery = analogRead(A0);
      int batteryLevel = map(battery, 0, 1023, 0, 100);

      if (batteryLevel != oldBatteryLevel)
      {                                           // if the battery level has changed
        Serial.print("Battery Level % is now: "); // print it
        Serial.println(batteryLevel);
        batteryLevelChar.writeValue(batteryLevel); // and update the battery level characteristic
        oldBatteryLevel = batteryLevel;            // save the level for next comparison
      }
    }
  }


  if (pin1_On && (currentMillis - pVestMillis1 >= intervals)) {
    Serial.println("turning off pin 1");
    haptix_off(16,17);
    pin1_On = false;
  }
  if (pin2_On && (currentMillis - pVestMillis2 >= intervals)) {
    Serial.println("turning off pin 2");
    haptix_off(18,17);
    pin2_On = false;
  }
  if (pin3_On && (currentMillis - pVestMillis3 >= intervals)) {
    Serial.println("turning off pin 3");
    haptix_off(21,17);
    pin3_On = false;
  }
  if (pin4_On && (currentMillis - pVestMillis4 >= intervals)) {
    Serial.println("turning off pin 4");
    haptix_off(16,19);
    pin4_On = false;
  }
  if (pin5_On && (currentMillis - pVestMillis5 >= intervals)) {
    Serial.println("turning off pin 5");
    haptix_off(18,19);
    pin5_On = false;
  }
  if (pin6_On && (currentMillis - pVestMillis6 >= intervals)) {
    Serial.println("turning off pin 6");
    haptix_off(21,19);
    pin6_On = false;
  }
  if (pin7_On && (currentMillis - pVestMillis7 >= intervals)) {
    Serial.println("turning off pin 7");
    haptix_off(16,22);
    pin7_On = false;
  }
  if (pin8_On && (currentMillis - pVestMillis8 >= intervals)) {
    Serial.println("turning off pin 8");
    haptix_off(18,22);
    pin8_On = false;
  }
  if (pin9_On && (currentMillis - pVestMillis9 >= intervals)) {
    Serial.println("turning off pin 9");
    haptix_off(21,22);
    pin9_On = false;
  }
   if (pin10_On && (currentMillis - pVestMillis10 >= intervals)) {
    Serial.println("turning off pin 10");
    haptix_off(16,25);
    pin10_On = false;
  }
   if (pin11_On && (currentMillis - pVestMillis11 >= intervals)) {
    Serial.println("turning off pin 11");
    haptix_off(18,25);
    pin11_On = false;
  }
  if (pin12_On && (currentMillis - pVestMillis12 >= intervals)) {
    Serial.println("turning off pin 12");
    haptix_off(21,25);
    pin12_On = false;
  }
  if (pin13_On && (currentMillis - pVestMillis13 >= intervals)) {
    Serial.println("turning off pin 13");
    haptix_off(16,32);
    pin13_On = false;
  }
   if (pin14_On && (currentMillis - pVestMillis14 >= intervals)) {
    Serial.println("turning off pin 14");
    haptix_off(18,32);
    pin14_On = false;
  }
  if (pin15_On && (currentMillis - pVestMillis15 >= intervals)) {
    Serial.println("turning off pin 15");
    haptix_off(21,32);
    pin15_On = false;
  }
   if (pin16_On && (currentMillis - pVestMillis16 >= intervals)) {
    Serial.println("turning off pin 16");
    haptix_off(16,23);
    pin16_On = false;
  } 
  if (pin17_On && (currentMillis - pVestMillis17 >= intervals)) {
    Serial.println("turning off pin 17");
    haptix_off(18,23);
    pin17_On = false;
  } 
  if (pin18_On && (currentMillis - pVestMillis18 >= intervals)) {
    Serial.println("turning off pin 18");
    haptix_off(21,23);
    pin18_On = false;
  }
  // poll for Bluetooth® Low Energy events
  BLE.poll();
}

void blePeripheralConnectHandler(BLEDevice central)
{
  // central connected event handler
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
  digitalWrite(LED_BUILTIN, HIGH);
}

void blePeripheralDisconnectHandler(BLEDevice central)
{
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
  digitalWrite(LED_BUILTIN, LOW);
}

void hapticCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic)
{
  // central wrote new value to characteristic, update LED
  // Serial.print("Characteristic event, written: ");

  if (hapticCharacteristic.value())
  {
    // Serial.println(hapticCharacteristic.value());
    uint8_t buffer[20];
    int bytesRead = hapticCharacteristic.readValue(buffer, sizeof(buffer));
    // Serial.println(buffer[0]);

    Serial.print("Received bytes: ");
    for (int i = 0; i < bytesRead; i++)
    {
      Serial.print(buffer[i], HEX);
      Serial.print(" ");
    }
    Serial.println(" ");

    if ((buffer[0]) == 1) {
      Serial.println("compared to 1 ok");
      haptix_on(16,17,255);
      pVestMillis1 = millis();
      pin1_On = true;
    }
    if ((buffer[0]) == 2) {
      Serial.println("compared to 2 ok");
      haptix_on(18,17,255);
      pVestMillis2 = millis();
      pin2_On = true;
    }
    if ((buffer[0]) == 3) {
      Serial.println("compared to 3 ok");
      haptix_on(21,17,255);
      pVestMillis3 = millis();
      pin3_On = true;
    }
    if ((buffer[0]) == 4) {
      Serial.println("compared to 4 ok");
      haptix_on(16,19,255);
      pVestMillis4 = millis();
      pin4_On = true;
    }
    if ((buffer[0]) == 5) {
      Serial.println("compared to 5 ok");
      haptix_on(18,19,255);
      pVestMillis5 = millis();
      pin5_On = true;
    }
    if ((buffer[0]) == 6) {
      Serial.println("compared to 6 ok");
      haptix_on(21,19,255);
      pVestMillis6 = millis();
      pin6_On = true;
    }
    if ((buffer[0]) == 7) {
      Serial.println("compared to 7 ok");
      haptix_on(16,22,255);
      pVestMillis7 = millis();
      pin7_On = true;
    }
    if ((buffer[0]) == 8) {
      Serial.println("compared to 8 ok");
      haptix_on(18,22,255);
      pVestMillis8 = millis();
      pin8_On = true;
    }
    if ((buffer[0]) == 9) {
      Serial.println("compared to 9 ok");
      haptix_on(21,22,255);
      pVestMillis9 = millis();
      pin9_On = true;
    }
    if ((buffer[0]) == 10) {
      Serial.println("compared to 10 ok");
      haptix_on(16,25,255);
      pVestMillis10 = millis();
      pin10_On = true;
    }
    if ((buffer[0]) == 11) {
      Serial.println("compared to 11 ok");
      haptix_on(18,25,255);
      pVestMillis11 = millis();
      pin11_On = true;
    }
    if ((buffer[0]) == 12) {
      Serial.println("compared to 12 ok");
      haptix_on(21,25,255);
      pVestMillis12 = millis();
      pin12_On = true;
    }
     if ((buffer[0]) == 13) {
      Serial.println("compared to 13 ok");
      haptix_on(16,32,255);
      pVestMillis13 = millis();
      pin13_On = true;
    }
     if ((buffer[0]) == 14) {
      Serial.println("compared to 14 ok");
      haptix_on(18,32,255);
      pVestMillis14 = millis();
      pin14_On = true;
    }
     if ((buffer[0]) == 15) {
      Serial.println("compared to 15 ok");
      haptix_on(21,32,255);
      pVestMillis15 = millis();
      pin15_On = true;
    }
     if ((buffer[0]) == 16) {
      Serial.println("compared to 16 ok");
      haptix_on(16,23,255);
      pVestMillis16 = millis();
      pin16_On = true;
    }
    if ((buffer[0]) == 17) {
      Serial.println("compared to 17 ok");
      haptix_on(18,23,255);
      pVestMillis17 = millis();
      pin17_On = true;
    }
     if ((buffer[0]) == 18) {
      Serial.println("compared to 18 ok");
      haptix_on(21,23,255);
      pVestMillis18 = millis();
      pin18_On = true;
    }

  }

}

void updateBatteryLevel(BLEDevice central, BLECharacteristic characteristic)
{
  // Start battery Notification
  isSubscribed = true;
}

void endBatteryLevel(BLEDevice central, BLECharacteristic characteristic)
{
  // End battery Notification
  isSubscribed = false;
}

void haptix_on(int pin_num1, int pin_num2, int impulse){
  // turn on the haptics
  analogWrite(pin_num1, impulse);
  digitalWrite(pin_num2, HIGH);
}

void haptix_off(int pin_num1, int pin_num2){
  // turn off the haptics
  analogWrite(pin_num1, 0);
  digitalWrite(pin_num2, LOW);
}
