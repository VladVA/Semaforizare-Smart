#include <HX711.h>
 
const int LOADCELL_DOUT_PIN1 = 9;
const int LOADCELL_SCK_PIN1 = 8;

const int LOADCELL_DOUT_PIN2 = 4;
const int LOADCELL_SCK_PIN2 = 5;

const int pin_red1 = 22;
const int pin_green1 = 26;
const int pin_yellow1 = 24;


const int pin_red2 = 48;
const int pin_green2 = 52;
const int pin_yellow2 = 50;

float weight1 = 1;
float weight2 = 1;
 
HX711 scale1;
HX711 scale2;

float calibration_factor1 = -867150;
float calibration_factor2 = -485620;


void setup() {
  Serial.begin(9600);

  pinMode(pin_red1, OUTPUT);
  pinMode(pin_green1, OUTPUT);
  pinMode(pin_yellow1, OUTPUT);

  pinMode(pin_red2, OUTPUT);
  pinMode(pin_green2, OUTPUT);
  pinMode(pin_yellow2, OUTPUT);

  
  digitalWrite(pin_red1, HIGH);
  digitalWrite(pin_green1, LOW);
  digitalWrite(pin_yellow1, LOW);

  
  digitalWrite(pin_red2, HIGH);
  digitalWrite(pin_green2, LOW);
  digitalWrite(pin_yellow2, LOW);

  
  scale1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
  scale2.begin(LOADCELL_DOUT_PIN2, LOADCELL_SCK_PIN2);
  
  scale1.set_scale();
  scale2.set_scale();
  
  scale1.tare(); //Reset the scale to 0
  scale2.tare(); //Reset the scale to 0
}

void loop() {

  scale1.set_scale(calibration_factor1);
  scale2.set_scale(calibration_factor2);


  int t = 10;
  
  //ciclu semafor 1
  Serial.print("PastWeight1 = ");
  Serial.print(weight1);

  weight1 = scale1.get_units() * 453.59237 + 1;
  float t1 = (weight1/(weight1 + weight2)) * t;
  float t2 = (weight2/(weight1 + weight2)) * t; 

  Serial.print(" Reading: t1 = ");
  Serial.print(t1);
  Serial.print(" t2 = ");
  Serial.print(t2);
  Serial.print(" CurrentWeight1 = ");
  Serial.print(weight1);
  Serial.println();
  
  digitalWrite(pin_red1, LOW);
  digitalWrite(pin_green1, HIGH);
  
  delay(((int)t1 * 1000) + 50);


  digitalWrite(pin_green1, LOW);
  digitalWrite(pin_yellow1, HIGH);

  delay(500);
  
  digitalWrite(pin_yellow1, LOW);
  digitalWrite(pin_red1, HIGH);




  //ciclu semafor 2

  Serial.print("PastWeight2 = ");
  Serial.print(weight2);
  
  weight2 = scale2.get_units() * 453.59237 + 1;

  t1 = (weight1/(weight1 + weight2)) * t;
  t2 = (weight2/(weight1 + weight2)) * t;
  
  Serial.print(" Reading: t1 = ");
  Serial.print(t1);
  Serial.print(" t2 = ");
  Serial.print(t2);
  Serial.print(" CurrentWeight2 = ");
  Serial.print(weight2);
  Serial.println();
  
  digitalWrite(pin_red2, LOW);
  digitalWrite(pin_green2, HIGH);


  delay(((int)t2 * 1000) + 50);

  digitalWrite(pin_green2, LOW);
  digitalWrite(pin_yellow2, HIGH);

  delay(500);
  
  digitalWrite(pin_yellow2, LOW);
  digitalWrite(pin_red2, HIGH);
  
}
