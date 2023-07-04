#include <IRremote.h> 
int sensor = 2;
IRrecv irrecv(sensor);
decode_results codigo;
void setup() { 
  Serial.begin(9600);
  irrecv.enableIRIn();
} 
void loop() { 
  if (irrecv.decode(&codigo)) {
    Serial.println(codigo.value, HEX);
    irrecv.resume();
  }
  delay (100);
}
