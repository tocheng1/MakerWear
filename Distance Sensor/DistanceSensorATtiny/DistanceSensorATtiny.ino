#include <QueueArray.h>

//Pin Configurations
//int input_pin = 3;           //Pin 2 on ATtiny
int ir_receiver_pin = 2;   //Pin 3 on ATtiny
int output_pin = 1;          //Pin 6 on ATtiny
int intervals = 30;            // controls intensity of change between loops
QueueArray <int> q;
int total, last, result, distance;



void setup() {
  // put your setup code here, to run once:
  for (int i = 0; i < intervals; i++) {
    distance = process();
    total += distance;
    q.enqueue(distance);
    if (i == (intervals - 1))
      last = distance;  
  }
}

int process() {
  int x = analogRead(ir_receiver_pin);
  float y = 0.000004*x*x*x - 0.0013*x*x + 0.1567*x + 7.9254;
  int out_value = map(y, 7.5, 30, 255, 0);
  return out_value;
}

void loop() {
  distance = process();
  total += distance;
  q.enqueue(distance);
  total -= last;
  last = q.dequeue();
  result = total / intervals;
  
  
  if (result < 0) {
    result = 0;
  } else if (result > 255) {
    result = 255;   
  }
  
  analogWrite(output_pin, result);
}
