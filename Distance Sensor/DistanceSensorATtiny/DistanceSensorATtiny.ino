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
