

#include <ArduinoBLE.h>

BLEService vestService("1101"); // create service

// create switch characteristic and allow remote device to read and write
BLEStringCharacteristic hapticCharacteristic("2101", BLEWrite, 4);
BLEUnsignedCharCharacteristic batteryLevelChar("2105", BLERead | BLENotify);

const int ledPin = LED_BUILTIN; // pin to use for the LED

int oldBatteryLevel = 0;          // last battery level reading from analog input
unsigned long previousMillis = 0; // last time the battery level was checked, in ms
bool isSubscribed = false;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  pinMode(ledPin, OUTPUT); // use the LED pin as an output

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