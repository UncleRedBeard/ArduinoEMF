/*
 * File:         calibrate_emf.ino
 * Author:       Uncle RedBeard
 * Date:         12-JAN-2015
 * Description:  attempts at calibarting a diy emf detector
 *               using a 1M ohm resistor
 * Note:         Based on Aaron Alai's EMF Detector Project
 *               http://aaronalai.com/emf-detector
 */
//----------------------------------------
const int ANTENNA = 5;    //A5
const int LED_PIN = 11;    //LED output pin

unsigned long int EMF_WAIT = 1000;
unsigned long int PREVIOUS_WAIT = 0;

int ANTENNA_READING = 0;

void setup(){
  
  Serial.begin(9600);
  
  Serial.println("EMF Detector Starting");
  Serial.println("  Please Wait");
  
  delay(5);  //and breathe
  
}
//-------------------------------------------
void get_emf(){
  
  ANTENNA_READING = analogRead(ANTENNA);
  
  if (ANTENNA_READING >= 1) {
    
    ANTENNA_READING = constrain(ANTENNA_READING, 1, 100);
    ANTENNA_READING = map(ANTENNA_READING, 1, 100, 1, 255);
    
    Serial.println(ANTENNA_READING);
    
    analogWrite(LED_PIN, ANTENNA_READING);
    
  } else {
    
    Serial.println(ANTENNA_READING);
    
    analogWrite(LED_PIN, 0);
    
    
  }
  
}
//---------------------------------------------
void loop(){
  
  if (((unsigned long)(millis() - PREVIOUS_WAIT) >= EMF_WAIT)) {
    
    get_emf();
    
  }
  
}
