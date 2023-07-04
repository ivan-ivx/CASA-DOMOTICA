#include <IRremote.h>

int receptor =11;
int led =13;
IRrecv irrecv (receptor); 
decode_results codigo;

void setup() {
Serial.begin (9600);
irrecv.enableIRIn();
pinMode (led, OUTPUT);

}

void loop() {
 if (irrecv.decode (&codigo))
 {  
  Serial.println (codigo.value, HEX);

  if ( codigo.value==0xFF6897)
  {
    digitalWrite (led, HIGH);
  }
  if (codigo.value==0xFF30FC)
  {
    digitalWrite (led, LOW);
  }
  delay (500);
  irrecv.resume ();
 }
}
