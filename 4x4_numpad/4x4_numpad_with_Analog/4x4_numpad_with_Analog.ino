void setup() {
  Serial.begin(9600);  /* Define baud rate for serial communication */
}

void loop() {
  int adc_val;
  adc_val = analogRead(A7); /* Read input from keypad */
  if (adc_val>850)
  {
    Serial.print("Key Pressed : ");
    Serial.println("D");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>450  && adc_val<510)
  {
    Serial.print("Key Pressed : ");
    Serial.println("C");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>300  && adc_val<350)
  {
    Serial.print("Key Pressed : ");
    Serial.println("B");
    Serial.print(adc_val);
    delay(100);
  }
  else if ( adc_val>230  && adc_val<270)
  {
    Serial.print("Key Pressed : ");
    Serial.println("A");
    Serial.print(adc_val);
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
