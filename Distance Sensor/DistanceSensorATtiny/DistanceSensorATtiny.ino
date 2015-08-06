//Pin Configurations
//int input_pin = 3;           //Pin 2 on ATtiny
int ir_receiver_pin = 2;   //Pin 3 on ATtiny
int output_pin = 1;          //Pin 6 on ATtiny


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  int x = analogRead(ir_receiver_pin);
  float y = 0.000004*x*x*x - 0.0013*x*x + 0.1567*x + 7.9254;
  int out_value = map(y, 7.5, 30, 255, 0);

  if(x>250)
    out_value = 0;

  analogWrite(output_pin, out_value);
  Serial.println(out_value);
}
