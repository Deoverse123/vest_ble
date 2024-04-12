/*
  Callback LED

  This example creates a Bluetooth® Low Energy peripheral with service that contains a
  characteristic to control an LED. The callback features of the
  library are used.

  The circuit:
  - Arduino MKR WiFi 1010, Arduino Uno WiFi Rev2 board, Arduino Nano 33 IoT,
    Arduino Nano 33 BLE, or Arduino Nano 33 BLE Sense board.

  You can use a generic Bluetooth® Low Energy central app, like LightBlue (iOS and Android) or
  nRF Connect (Android), to interact with the services and characteristics
  created in this sketch.

  This example code is in the public domain.
*/

#include <ArduinoBLE.h>

BLEService ledService("1101"); // create service

// create switch characteristic and allow remote device to read and write
BLEStringCharacteristic switchCharacteristic("2101", BLEWrite, 4);
// BLEByteCharacteristic switchCharacteristic2("2105", BLERead | BLEWrite);

const int ledPin = LED_BUILTIN; // pin to use for the LED


// inline const char * typeStr (int   var) { return " int "; }
// inline const char * typeStr (long  var) { return " long "; }
// inline const char * typeStr (float var) { return " float "; }
// inline const char * typeStr (const char *var) { return " char "; }



void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  pinMode(ledPin, OUTPUT); // use the LED pin as an output

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");

    while (1);
  }

  // set the local name peripheral advertises
  BLE.setLocalName("LEDCallback");
  // set the UUID for the service this peripheral advertises
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);
  // ledService.addCharacteristic(switchCharacteristic2);

  // add service
  BLE.addService(ledService);

  // assign event handlers for connected, disconnected to peripheral
  BLE.setEventHandler(BLEConnected, blePeripheralConnectHandler);
  BLE.setEventHandler(BLEDisconnected, blePeripheralDisconnectHandler);

  // assign event handlers for characteristic
  switchCharacteristic.setEventHandler(BLEWritten, switchCharacteristicWritten);
  // switchCharacteristic2.setEventHandler(BLEWritten, switchCharacteristicWritten2);
  // set an initial value for the characteristic
  // switchCharacteristic.setValue(0);
  // switchCharacteristic2.setValue(0);

  // start advertising
  BLE.advertise();

  Serial.println(("Bluetooth® device active, waiting for connections..."));
}

void loop() {
  // poll for Bluetooth® Low Energy events
  BLE.poll();
}

void blePeripheralConnectHandler(BLEDevice central) {
  // central connected event handler
  Serial.print("Connected event, central: ");
  Serial.println(central.address());
}

void blePeripheralDisconnectHandler(BLEDevice central) {
  // central disconnected event handler
  Serial.print("Disconnected event, central: ");
  Serial.println(central.address());
}

void switchCharacteristicWritten(BLEDevice central, BLECharacteristic characteristic) {
  // central wrote new value to characteristic, update LED
  // Serial.print("Characteristic event, written: ");

  if (true) {
    Serial.println(switchCharacteristic.value());


  // String inputString = "AA";
  // int asciiValue = 0;

  // for (int i = 0; i < inputString.length(); i++) {
  //   asciiValue = asciiValue * 100 + inputString[i]; // Multiply by 256 to shift one character to the left
  // }

  // Serial.println(asciiValue);



    // char x = switchCharacteristic.value();

    // Serial.println(switchCharacteristic.value().toInt());
    // Serial.println(String(switchCharacteristic.value()));
    // Serial.print (typeStr(switchCharacteristic.value())); Serial.println (switchCharacteristic.value());
    // Serial.println(typeof(switchCharacteristic.value()));
    // Serial.println(switchCharacteristic.valueBE());
    uint8_t buffer[20];
    int bytesRead = switchCharacteristic.readValue(buffer, sizeof(buffer));

    Serial.print("Received bytes: ");
    for (int i = 0; i < bytesRead; i++) {
      Serial.print(buffer[i], HEX);
      Serial.print(" ");
    }
    Serial.println(" ");


    unsigned int dataHex[42] = {};
    Serial.println(switchCharacteristic.readValue(dataHex, 300));
    // Serial.println(switchCharacteristic.valueLE());
    Serial.println(switchCharacteristic.valueSize());
    // Serial.println(switchCharacteristic.valueUpdated());
    Serial.println(dataHex[0]);
    // Serial.println(dataHex[1]);

    

    // unsigned int dataHex[42] = {};
    // switchCharacteristic.readValue(dataHex, 42);
    // Serial.println();
    // // Serial.println(switchCharacteristic2.value());
    // // Serial.println(switchCharacteristic.read());
    // // Serial.println(switchCharacteristic.);

    // // unsigned int dataHex[42] = {};
    // // Serial.println(switchCharacteristic.readValue(dataHex, 42));
    // for (int i = 0; i < 42; i++) {
    //     Serial.println(dataHex[i]);
    //     }
    

    // Serial.println(switchCharacteristic.valueLE());
    // Serial.println(event[1]);
    Serial.println("LED on");
    digitalWrite(ledPin, HIGH);
  } else {
    Serial.println("LED off");
    digitalWrite(ledPin, LOW);
  }
}

