/*
 * File:         emf_detector.ino
 * Author:       Uncle RedBeard
 * Date:         12-JAN-2015
 * Description:  diy emf detector (initially) using a 1M ohm risistor, DHT22
 *               temperature sensor, and various leds ultimately, the project
 *               will be a self contained spirit detector and the containing
 *               device will be a teddy bear or some other young children's
 *               doll that has an emf antenna in each arm and accompanying
 *               leds that will light up when an emf fluctuation is detected.
 * Note:         Based on Aaron Alai's EMF Detector Project
 *               http://aaronalai.com/emf-detector
 * ToDo:         12-JAN-2015
 *               - switch to TMP36 temperature sensor (not as accurate
 *                 as the DHT22, but sufficient for this project)
 *               - add pre-recorded voice autoplayback
 */
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
//---------------------------------------
DHT dht(DHTPIN, DHTTYPE);

const int ANTENNA = 5;    //A5
const int LED_PIN = 11;   //LED output pin

unsigned long int emf_interval = 5;
unsigned long int previous_millis = 0;

int ANTENNA_READING = 0;
int EMF_VAL = 0;

//float tempC = 0;
float tempF = 0;

void setup(){
  
  Serial.begin(9600);
  
  Serial.println("EMF Detector Starting");
  Serial.println("  Please Wait");
  
  dht.begin();
  
  delay(5);  //and breathe
  
}
//-------------------------------------------
void get_emf(){
  
  ANTENNA_READING = analogRead(ANTENNA);
  
  if (ANTENNA_READING >= 1) {
    
    EMF_VAL = constrain(ANTENNA_READING, 1, 100);
    EMF_VAL = map(EMF_VAL, 1, 100, 1, 255);
    
    Serial.print("EMF Reading: ");
    Serial.println(ANTENNA_READING);
    
    analogWrite(LED_PIN, ANTENNA_READING);
    
  } else {
    
    Serial.print("EMF Reading: "); 
    Serial.println(ANTENNA_READING);
    
    analogWrite(LED_PIN, 0);
    
  }
  
}

void get_temp(){
  
  //tempC = dht.readTemperature();
  tempF = dht.readTemperature(true);
  
  if (isnan(tempF)){
    
    Serial.println("\nFailed to read from DHT Temp Sensor");
    
  } else {
    
    Serial.print("Tempeature: ");
    //Serial.print (tempC);
    //Serial.print("*C | ");
    Serial.print(tempF);
    Serial.println("*F");
    
  }
  
}
//---------------------------------------------
void loop(){
  
  if (((unsigned long)(millis() - previous_millis) >= emf_interval)) {
    
    previous_millis = millis();
    
    get_emf();
    //get_temp();
    
  }
  
}
