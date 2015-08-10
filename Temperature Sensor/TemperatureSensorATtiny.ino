//TMP36 Pin Variables
int led = 1;            // pin 6 on ATtiny
int sensorPin = 3;      // pin 1 on ATtiny
                        //the analog pin the TMP36's Vout (sense) pin is connected to
                        //the resolution is 10 mV / degree centigrade with a
                        //500 mV offset to allow for negative temperatures

int min_temp = 50;    //minimum temperature in F
int min_temp = 100;   //maximum temperature in F

#include <QueueArray.h>

QueueArray <int> q;
int intervals = 20;
float total, last, result, tempF;

/*
 * setup() - this function runs once when you turn your Arduino on
 * We initialize the serial connection with the computer
 */
void setup()
{
  for (int i = 0; i < intervals; i++) {
    tempF = readF();
    q.enqueue(tempF);
    total += tempF;
    if (i == intervals - 1) {
      last = tempF;
    } 
  }
}

float readF() {
  int reading = analogRead(sensorPin);
  float temperatureF = ((reading * 5.0 / 1024.0) - 0.5) * 180 + 32.0;
  return map(temperatureF, min_temp, max_temp, 0, 255);
}
 
void loop()                     // run over and over again
{
 //getting the voltage reading from the temperature sensor
 //int reading = analogRead(sensorPin);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 //float voltage = reading * 5.0;
 //voltage /= 1024.0; 
 
 // print out the voltage
 //Serial.print(voltage); Serial.println(" volts");
 
 // now print out the temperature
 //float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                               //to degrees ((voltage - 500mV) times 100)
 //Serial.print(temperatureC); Serial.println(" degrees C");
 
 // now convert to Fahrenheit

  tempF = readF();
  total += tempF;
  q.enqueue(tempF);
  total -= last;
  last = q.dequeue();
  result = total / intervals;

  if (result > 255) {
    analogWrite(led, 255);  
  } else if (result < 0) {
    analogWrite(led, 0);  
  } else {
    analogWrite(led, result);
  }
}
