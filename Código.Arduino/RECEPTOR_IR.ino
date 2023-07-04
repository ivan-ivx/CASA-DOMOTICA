
#include <IRremote.h>     
#define boton1 0xF30CFF00   
#define boton2 0xE718FF00
  
 
int IR = 11;   
///int LED = 13;     
 
void setup() {
  Serial.begin(9600);     
  IrReceiver.begin(IR, DISABLE_LED_FEEDBACK); 
 // pinMode(LED, OUTPUT); 
} 
 
void loop() {
  if (IrReceiver.decode()) {        
  //  Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX); 
    if (IrReceiver.decodedIRData.decodedRawData == boton1)   
   Serial.println ("boton1"); 
    if (IrReceiver.decodedIRData.decodedRawData == boton2)   
   Serial.println ("boton2");
    
    IrReceiver.resume();       
  }
  delay (100);            
}
