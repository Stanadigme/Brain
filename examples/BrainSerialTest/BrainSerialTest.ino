// Arduino Brain Library - Brain Serial Test

// Description: Grabs brain data from the serial RX pin and sends CSV out over the TX pin (Half duplex.)
// More info: https://github.com/kitschpatrol/Arduino-Brain-Library
// Author: Eric Mika, 2010 revised in 2014

#include <Brain.h>

// Set up the brain parser, pass it the hardware serial object you want to listen on.
Brain brain(Serial);

char *values;

long value = 0;
// long valuesAr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// long _valuesAr[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
// long valuesAr[] = { 0, 0, 0,0,0};
// long _valuesAr[] = { 0, 0, 0,0,0};
// long valuesAr[] = { 0, 0};
// long _valuesAr[] = { 0, 0};
// long max = 0;
// long min = 0;
long previous = 0; 
int position = 3;
char *sepValue;
const char *delimiter = ",";
#include <Servo.h>
int pinServo = 9;
Servo monServo;
int angleServo = 90;


void setup() {
  // Start the hardware serial.
  Serial.begin(9600);
  monServo.attach(pinServo);
  monServo.write(angleServo);
}

void loop() {
  // Expect packets about once per second.
  // The .readCSV() function returns a string (well, char*) listing the most recent brain data, in the following format:
  // "signal strength, attention, meditation, delta, theta, low alpha, high alpha, low beta, high beta, low gamma, high gamma"
  if (brain.update()) {
    Serial.println(brain.readErrors());
    values = brain.readCSV();
    Serial.println(values);

    sepValue = strtok(values, delimiter);
    int i = 0;
    while (sepValue != NULL) {
      if (i == position) {
        previous = value;
        value = 0;
        for (int i = 1; i < strlen(sepValue) + 1; i++) {
          char _val = sepValue[strlen(sepValue) - i];
          int val = _val - '0';
          long plus = val * pow(10, i - 1);
          value += plus;
        }
        break;
      }
      sepValue = strtok(NULL, delimiter);
      i++;
    }
    setServo();
  }
}

void setValAr() {
  // long _valuesAr[] = valuesAr;
  // _valuesAr[0] = value;
//   for (int i = 0; i < sizeof(valuesAr)-1; i++) {
//     _valuesAr[i+1] = valuesAr[i];
//   }
// for (int i = 0; i < sizeof(valuesAr); i++) {
//     valuesAr[i] = _valuesAr[i];
//   }
// valuesAr = _valuesAr;   
// valuesAr[1] = valuesAr[0];
// valuesAr[0] = value;
  // for (int i = sizeof(valuesAr)-1; i > 0; i--) {
  //   valuesAr[i] = valuesAr[i-1];
  // }
  // valuesAr[0] = value;
}

void getMin() {
  // min = valuesAr[0];
  // for (int i = 0; i < sizeof(valuesAr); i++) {
  //   if (valuesAr[i] < min) min = valuesAr[i];
  // }
}

void getMax() {
  // max = valuesAr[0];
  // for (int i = 0; i < sizeof(valuesAr); i++) {
  //   if (valuesAr[i] > max) max = valuesAr[i];
  // }
}


void setServo() {
  // setValAr();
  // getMin();
  // getMax();
  // angleServo = map(value, min, max, 0, 180);
  // angleServo= angleServo + 10;
  // Serial.println(angleServo);
if(value >= previous)
{
  angleServo += 10;
}
else{
angleServo += -10;  
}

  monServo.write(angleServo);
  delay(15);
  // Serial.print(value);
  // Serial.print(" ");
  // Serial.print(previous);
  // Serial.print(" ");
  // Serial.print(min);
  // Serial.print(" ");
  // Serial.print(max);
  // Serial.print(" ");
  Serial.println(angleServo);
  if(angleServo == 180 || angleServo == 0 ){
    angleServo = 90;
    monServo.write(angleServo);
    delay(15);    
  }
}