/*
 Setup your scale and start the sketch WITHOUT a weight on the scale
 Once readings are displayed place the weight on the scale
 Press +/- or a/z to adjust the calibration_factor until the output readings match the known weight
 Arduino pin A! -> HX711 CLK
 Arduino pin A0 -> HX711 DOUT
 Arduino pin 5V -> HX711 VCC
 Arduino pin GND -> HX711 GND 
*/

/*
 *   The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * 
 * http://www.arduino.cc/en/Tutorial/LiquidCrystalHelloWorld
 */
// include the library code:
#include <LiquidCrystal.h>
#include "HX711.h"

#define relayoff HIGH
#define relayon LOW
#define relay_A 6
#define relay_B 7
#define relay_C 8
#define relay_D 9

HX711 scale(A1, A0);

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
float calibration_factor = 2230; // this calibration factor is adjusted according to my load cell
float units;
float ounces;

String inputString;
long inputInt;
bool lop = true;


void setup() {

  pinMode(relay_A, OUTPUT);
  pinMode(relay_B, OUTPUT);
  pinMode(relay_C, OUTPUT);
  pinMode(relay_D, OUTPUT);
  digitalWrite(relay_A, relayoff);
  digitalWrite(relay_B, relayoff);
  digitalWrite(relay_C, relayoff);
  digitalWrite(relay_D, relayoff);
  
  inputString.reserve(10); // maximum number of digit for a number is 10, change if needed
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  boot_screen();
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");

  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  long zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {

  numpad();
  
  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  units = scale.get_units(), 10;
//  not to show negative value
  if (units < 0)
  {
    units = 0.00;
  }
  ounces = units * 0.035274;
  Serial.print(units);
//  value in float
//  Serial.print(round(units));
  Serial.print(" grams"); 
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1;
  }
//  LCD codes for printing
  lcd.setCursor(0, 0);
//  lcd.print(units);
//  value in float
  lcd.print("Grams : ");
  lcd.setCursor(8, 0);
  lcd.print(round(units));
  lcd.setCursor(0, 1);
  lcd.print("c_factor: ");
  lcd.print(calibration_factor);

  // clear screen for the next loop:
  delay(100);
  lcd.clear();

}
// relay on off function
void relay_state(){
  if (round(units) >= inputString.toInt()) {
//    turn on the relay
      digitalWrite(relay_A, relayon);
      delay(1000);
      digitalWrite(relay_A, relayoff);
    }
  }

void boot_screen(){
  lcd.setCursor(0, 0);
  lcd.print("Welcome !");
  lcd.setCursor(0, 1);
  lcd.print("+919094542212");
  delay(5000);
  lcd.clear(); 
  }

void numpad(){
  int adc_val;
  adc_val = analogRead(A7); /* Read input from keypad */
  if (adc_val>850)
  {
    Serial.print("Key Pressed : ");
    Serial.println("D");
    Serial.print(adc_val);
    delay(100);
  }
  else if (adc_val>450  && adc_val<510)
  {
    delay(1000);
    if (adc_val>450  && adc_val<510){
      Serial.print("Key Pressed : ");
      Serial.println("C");
      Serial.print(adc_val);
      delay(100);
      }
  }
  else if ( adc_val>300  && adc_val<350)
  {
    delay(1000);
    if ( adc_val>300  && adc_val<350){
      Serial.print("Key Pressed : ");
      Serial.println("B");
      Serial.print(adc_val);
      // set over weight value
      lop = true;
      while(lop){
        Serial.println("loop in B");
        numpad_loop();
        if (lop == false) {
          break;
        }
      }
    }    
    delay(100);
  }
  else if ( adc_val>230  && adc_val<270)
  {
    Serial.print("Key Pressed : ");
    Serial.println("A");
    Serial.print(adc_val);
    scale.tare();  //Reset the scale to 0
    delay(100);
  }
  else if ( adc_val>160  && adc_val<180)
  {
    Serial.print("Key Pressed : ");
    Serial.println("STOP");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>145  && adc_val<155)
  {
    Serial.print("Key Pressed : ");
    Serial.println("9");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>125  && adc_val<135)
  {
    Serial.print("Key Pressed : ");
    Serial.println("6");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>105  && adc_val<120)
  {
    Serial.print("Key Pressed : ");
    Serial.println("3");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>92  && adc_val<99)
  {
    Serial.print("Key Pressed : ");
    Serial.println("0");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>85  && adc_val<90)
  {
    Serial.print("Key Pressed : ");
    Serial.println("8");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>77  && adc_val<81)
  {
    Serial.print("Key Pressed : ");
    Serial.println("5");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>72  && adc_val<76)
  {
    Serial.print("Key Pressed : ");
    Serial.println("2");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>65  && adc_val<68)
  {
    Serial.print("Key Pressed : ");
    Serial.println("START");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>60  && adc_val<62)
  {
    Serial.print("Key Pressed : ");
    Serial.println("7");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>57  && adc_val<59)
  {
    Serial.print("Key Pressed : ");
    Serial.println("4");
    Serial.print(adc_val);
    delay(100);
  }
  else if( adc_val>52  && adc_val<56)
  {
    Serial.print("Key Pressed : ");
    Serial.println("1");
    Serial.print(adc_val);
    delay(100);
  }
  else
  {   
  }
  delay(100);
  }

void numpad_loop(){

  int adc_val2;
  adc_val2 = analogRead(A7); /* Read input from keypad */
  if (adc_val2>850)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("D");
    Serial.print(adc_val2);
    delay(100);
  }
  else if ( adc_val2>450  && adc_val2<510)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("C");
    Serial.print(adc_val2);
    delay(100);
  }
  else if ( adc_val2>300  && adc_val2<350)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("B");
    Serial.print(adc_val2);
    delay(100);
  }
  else if ( adc_val2>230  && adc_val2<270)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("A");
    Serial.print(adc_val2);
    delay(100);
  }
  else if ( adc_val2>160  && adc_val2<180)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("STOP");
    Serial.print(adc_val2);
    inputString = ""; // clear the input
    delay(100);
  }
  else if ( adc_val2>145  && adc_val2<155)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("9");
    Serial.print(adc_val2);
    inputString += "9";
    delay(100);
  }
  else if ( adc_val2>125  && adc_val2<135)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("6");
    Serial.print(adc_val2);
    inputString += "6";
    delay(100);
  }
  else if ( adc_val2>105  && adc_val2<120)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("3");
    Serial.print(adc_val2);
    inputString += "3";
    delay(100);
  }
  else if ( adc_val2>92  && adc_val2<99)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("0");
    Serial.print(adc_val2);
    inputString += "0";
    delay(100);
  }
  else if ( adc_val2>85  && adc_val2<90)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("8");
    Serial.print(adc_val2);
    inputString += "8";
    delay(100);
  }
  else if ( adc_val2>77  && adc_val2<81)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("5");
    Serial.print(adc_val2);
    inputString += "5";
    delay(100);
  }
  else if ( adc_val2>72  && adc_val2<76)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("2");
    Serial.print(adc_val2);
    inputString += "2";
    delay(100);
  }
  else if ( adc_val2>65  && adc_val2<68)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("START");
    Serial.print(adc_val2);
    if (inputString.length() > 0) {
        inputInt = inputString.toInt(); // YOU GOT AN INTEGER NUMBER
        Serial.print(inputInt);
        inputString = "";               // clear input
        lop = false;                          // break the loop
      }
    delay(100);
  }
  else if ( adc_val2>60  && adc_val2<62)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("7");
    Serial.print(adc_val2);
    inputString += "7";
    delay(100);
  }
  else if ( adc_val2>57  && adc_val2<59)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("4");
    Serial.print(adc_val2);
    inputString += "4";
    delay(100);
  }
  else if( adc_val2>52  && adc_val2<56)
  {
    Serial.print("Key Pressed from loop : ");
    Serial.println("1");
    Serial.print(adc_val2);
    inputString += "1";
    delay(100);
  }

  else
  {   
  }
  delay(100);
    }
