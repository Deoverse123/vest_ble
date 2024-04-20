

#include <ArduinoBLE.h>

BLEService vestService("1101"); // create service

// create switch characteristic and allow remote device to read and write
BLEByteCharacteristic hapticCharacteristic("2101", BLEWrite);
BLEUnsignedCharCharacteristic batteryLevelChar("2105", BLERead | BLENotify);


int oldBatteryLevel = 0;          // last battery level reading from analog input
unsigned long previousMillis = 0; // last time the battery level was checked, in ms
bool isSubscribed = false;

// int preMillis = 0;
// int interval = 1000;
unsigned long previousMilliss = 0; // stores the last time the LED was updated
const long intervals = 300; // interval at which to blink (milliseconds)
bool ledOn = false; // flag to track LED state
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
  if (isSubscribed)
  { 
    // Serial.println("Subscribed");
    long currentMillis = millis();
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

  if (ledOn && (millis() - previousMilliss >= intervals)) {
    digitalWrite(16, LOW); // Turn off the LED
    digitalWrite(17, LOW); // Turn off the LED
    digitalWrite(ledPin, LOW); // Turn off the LED
    ledOn = false;
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
    // unsigned int dataHex[42] = {};
    // Serial.println(hapticCharacteristic.readValue(dataHex, 300));
    // Serial.println(hapticCharacteristic.valueSize());
    // Serial.println(dataHex[0]);
    if ((buffer[0]) == 1) {
      
      haptix(16,17,10,10);
      digitalWrite(ledPin, HIGH);
      ledOn = true;
      previousMilliss = millis();
      
      
    }
    // if ((buffer[0]) == 2) {
    //   haptix(18,17,10,10);
    // }
    // if ((buffer[0]) == 3) {
    //   haptix(21,17,10,10);
    // }
    // if ((buffer[0]) == 4) {
    //   haptix(16,19,10,10);
    // }
    // if ((buffer[0]) == 5) {
    //   haptix(18,19,10,10);
    // }
    // if ((buffer[0]) == 6) {
    //   haptix(21,19,10,10);
    // }
    // if ((buffer[0]) == 7) {
    //   haptix(16,22,10,10);
    // }
    // if ((buffer[0]) == 8) {
    //   haptix(18,22,10,10);
    // }
    // if ((buffer[0]) == 9) {
    //   haptix(21,22,10,10);
    // }




    Serial.println("LED on");
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    Serial.println("LED off");
    digitalWrite(ledPin, LOW);
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

void haptix(int pin_num1, int pin_num2, int delay_time, int impulse){
  digitalWrite(pin_num1, HIGH);
  digitalWrite(pin_num2, HIGH);
  // Serial.print(pin_num1); Serial.print(" , "); Serial.println(pin_num2);
  
  
  // delay(delay_time);
  // digitalWrite(pin_num1, LOW);
  // digitalWrite(pin_num2, LOW);

  // haptix_off();
}

// void haptix_off(){
//   unsigned long millisec = millis();
  
//   if (millisec - preMillis >= interval) {

//     // save the last time you blinked the LED
//     preMillis = millisec;
//     digitalWrite(16, LOW);
//     digitalWrite(17, LOW);
//     Serial.println(millisec);
//   }

//     // // if the LED is off turn it on and vice-versa:
//     // if (ledState == LOW) {
//     //   ledState = HIGH;
//     // } else {
//     //   ledState = LOW;
//     // }

// }