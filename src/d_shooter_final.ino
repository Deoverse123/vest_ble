int incomingInt = 0; // for incoming serial data

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

void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to 115200 bps
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(23, OUTPUT);
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingInt = Serial.parseInt();

    // say what you got:
    // Serial.print("I received: ");
    // Serial.println(incomingInt);

  switch (incomingInt) {
    case 1:
      if (pin1_On) {
        haptix_off(16,17);
        pin1_On = false;
        Serial.println("turning off pin 1");
       }
       else{
        haptix_on(16,17,255);
        pin1_On = true;
        Serial.println("turning ON pin 1");
       }
      break;
    case 2:
      if (pin2_On) {
        haptix_off(18,17);
        pin2_On = false;
        Serial.println("turning off pin 2");
       }
       else{
        haptix_on(18,17,255);
        pin2_On = true;
        Serial.println("turning ON pin 2");
       }
      break;
    case 3:
      if (pin3_On) {
        haptix_off(21,17);
        pin3_On = false;
        Serial.println("turning off pin 3");
       }
       else{
        haptix_on(21,17,255);
        pin3_On = true;
        Serial.println("turning ON pin 3");
       }
      break;
    case 4:
      if (pin4_On) {
        haptix_off(16,19);
        pin4_On = false;
        Serial.println("turning off pin 4");
       }
       else{
        haptix_on(16,19,255);
        pin4_On = true;
        Serial.println("turning ON pin 4");
       }
      break;
    case 5:
      if (pin5_On) {
        haptix_off(18,19);
        pin5_On = false;
        Serial.println("turning off pin 5");
       }
       else{
        haptix_on(18,19,255);
        pin5_On = true;
        Serial.println("turning ON pin 5");
       }
      break;
    case 6:
      if (pin6_On) {
        haptix_off(21,19);
        pin6_On = false;
        Serial.println("turning off pin 6");
       }
       else{
        haptix_on(21,19,255);
        pin6_On = true;
        Serial.println("turning ON pin 6");
       }
      break;
    case 7:
      if (pin7_On) {
        haptix_off(16,22);
        pin7_On = false;
        Serial.println("turning off pin 7");
       }
       else{
        haptix_on(16,22,255);
        pin7_On = true;
        Serial.println("turning ON pin 7");
       }
      break;
    case 8:
      if (pin8_On) {
        haptix_off(18,22);
        pin8_On = false;
        Serial.println("turning off pin 8");
       }
       else{
        haptix_on(18,22,255);
        pin8_On = true;
        Serial.println("turning ON pin 8");
       }
      break;
    case 9:
      if (pin9_On) {
        haptix_off(21,22);
        pin9_On = false;
        Serial.println("turning off pin 9");
       }
       else{
        haptix_on(21,22,255);
        pin9_On = true;
        Serial.println("turning ON pin 9");
       }
      break;
    case 10:
      if (pin10_On) {
        haptix_off(16,25);
        pin10_On = false;
        Serial.println("turning off pin 10");
       }
       else{
        haptix_on(16,25,255);
        pin10_On = true;
        Serial.println("turning ON pin 10");
       }
      break;
    case 11:
      if (pin11_On) {
        haptix_off(18,25);
        pin11_On = false;
        Serial.println("turning off pin 11");
       }
       else{
        haptix_on(18,25,255);
        pin11_On = true;
        Serial.println("turning ON pin 11");
       }
      break;
    case 12:
      if (pin12_On) {
        haptix_off(21,25);
        pin12_On = false;
        Serial.println("turning off pin 12");
       }
       else{
        haptix_on(21,25,255);
        pin12_On = true;
        Serial.println("turning ON pin 12");
       }
      break;
    case 13:
      if (pin13_On) {
        haptix_off(16,32);
        pin13_On = false;
        Serial.println("turning off pin 13");
       }
       else{
        haptix_on(16,32,255);
        pin13_On = true;
        Serial.println("turning ON pin 13");
       }
      break;
    case 14:
      if (pin14_On) {
        haptix_off(18,32);
        pin14_On = false;
        Serial.println("turning off pin 14");
       }
       else{
        haptix_on(18,32,255);
        pin14_On = true;
        Serial.println("turning ON pin 14");
       }
      break;
    case 15:
      if (pin15_On) {
        haptix_off(21,32);
        pin15_On = false;
        Serial.println("turning off pin 15");
       }
       else{
        haptix_on(21,32,255);
        pin15_On = true;
        Serial.println("turning ON pin 15");
       }
      break;
    case 16:
      if (pin16_On) {
        haptix_off(16,23);
        pin16_On = false;
        Serial.println("turning off pin 16");
       }
       else{
        haptix_on(16,23,255);
        pin16_On = true;
        Serial.println("turning ON pin 16");
       }
      break;
    case 17:
      if (pin17_On) {
        haptix_off(18,23);
        pin17_On = false;
        Serial.println("turning off pin 17");
       }
       else{
        haptix_on(18,23,255);
        pin17_On = true;
        Serial.println("turning ON pin 17");
       }
      break;
    case 18:
      if (pin18_On) {
        haptix_off(21,23);
        pin18_On = false;
        Serial.println("turning off pin 18");
       }
       else{
        haptix_on(21,23,255);
        pin18_On = true;
        Serial.println("turning ON pin 18");
       }
      break;
      
  }
  }
}

void haptix_off(int pin_num1, int pin_num2){
  // turn off the haptics
  analogWrite(pin_num1, 0);
  digitalWrite(pin_num2, LOW);

}


void haptix_on(int pin_num1, int pin_num2, int impulse){
  // turn on the haptics
  analogWrite(pin_num1, impulse);
  digitalWrite(pin_num2, HIGH);
}

