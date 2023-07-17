  #include <Servo.h>
#include <MFRC522.h>
#include <SPI.h>
#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522


//ir
#include <IRremote.h>     
#define boton1 0xF30CFF00   
#define boton2 0xE718FF00
#define boton3 0xA15EFF00
#define boton4 0xF708FF00
#define boton5 0xE31CFF00
#define boton6 0xA55AFF00
#define boton7 0xBD42FF00
#define boton8 0xAD52FF00
#define boton9 0xB54AFF00
#define boton10 0xF20DFF00
#define botonon 0xBA45FF00
#define botonup 0xE619FF00
#define botondown 0xE916FF00
#define botonright 0xEA15FF00
#define botonleft 0xF807FF00


int IR = 5; 

Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;

int vel =0;

int servoSpeed = 5;
int servoSpeed2 = -5;
//CONTROL INFRARROJO
//int IR = 11;     

void RFID(){
   // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) 
        {  
      //Seleccionamos una tarjeta
            if ( mfrc522.PICC_ReadCardSerial()) 
            {
                  // Enviamos serialemente su UID
                  Serial.print("Card UID:");
                  for (byte i = 0; i < mfrc522.uid.size; i++) {
                          Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                          Serial.print(mfrc522.uid.uidByte[i], HEX);   
                        servoMotor1.write (180);
                        delay (500);
                        
                          
                  } 
                  Serial.println();
                  // Terminamos la lectura de la tarjeta  actual
                  mfrc522.PICC_HaltA();      
                   servoMotor1.write (90);    
            }      
  } 
}



void rotativo1 (){
 vel = 90;
  servoMotor2.write(vel);              
  
}


void rotativo1off (){
 vel = 0;
  servoMotor2.write (vel);
}

void rotativo2 (){
  // Mueve el servomotor en una dirección
  for (int pos = 90; pos <= 180; pos += servoSpeed) {
    servoMotor3.write(pos);  // Establece la posición del servomotor
   delay(15);  // Pequeña pausa para permitir el movimiento suave
  }
  
delay(5000);  // Espera 5 segundos
  
 //Detiene el servomotor
servoMotor3.write(90);  // Establece la posición del servomotor a 90 grados
 delay(1000);  // Espera 1 segundo antes de repetir el ciclo
//servoMotor3.write (0);
}              

void rotativo2reverse (){
  // Mueve el servomotor en una dirección
  for (int pos = 90; pos <= 180; pos += servoSpeed) {
    servoMotor3.write(-pos);  // Establece la posición del servomotor
   delay(15);  // Pequeña pausa para permitir el movimiento suave
  }
  
delay(5000);  // Espera 5 segundos
  
 //Detiene el servomotor
servoMotor3.write(90);  // Establece la posición del servomotor a 90 grados
 delay(1000);  // Espera 1 segundo antes de repetir el ciclo
// servoMotor3.write (0);
} 
  





void bombaon (){
 digitalWrite(8, HIGH);
 delay (15000);
   digitalWrite (8,LOW);

}

void bombaoff (){
 
}


void leds1(){
 digitalWrite (6, HIGH);
 digitalWrite (7, HIGH); 
 analogWrite (A1, 255);
 analogWrite (A2, 255);
 analogWrite (A3, 255);
 analogWrite (A0, 255);


}


void leds2 (){
 analogWrite (A4, 255);
 analogWrite (A5, 255);
}





void ledoff(){


 digitalWrite (6, LOW);
 digitalWrite (7, LOW);
 analogWrite (A0, 0); 
 analogWrite (A1, 0);
 analogWrite (A2, 0);
 analogWrite (A3, 0);
 analogWrite (A4, 0);
 analogWrite (A5, 0);




  
}

void setup() {
  Serial.begin(9600);
servoMotor1.attach(3);
servoMotor2.attach(2);
servoMotor3.attach(4);
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
  Serial.println("Lectura del UID");

  IrReceiver.begin(IR, DISABLE_LED_FEEDBACK); 
  
pinMode (7, OUTPUT);
pinMode (6, OUTPUT);
pinMode (8, OUTPUT);


pinMode (A0, OUTPUT);
pinMode (A1, OUTPUT);
pinMode (A2, OUTPUT);
pinMode (A3, OUTPUT);
pinMode (A4, OUTPUT);
pinMode (A5, OUTPUT);

  
}

void loop() {

if (IrReceiver.decode())

{


  
  switch (IrReceiver.decodedIRData.decodedRawData)

  {
    case boton1: 
      Serial.println ("1"); 
      rotativo1();
      IrReceiver.resume();
      break;


    case boton2:
    rotativo1off();
    IrReceiver.resume();
    break;
       
    case boton3:
    Serial.println ("2");  
    rotativo2 (); 
    IrReceiver.resume();
    break;

    case boton4:
    Serial.println ("3");
   rotativo2reverse();
    IrReceiver.resume ();
    break;

    case boton5:
    Serial.println ("4");
    bombaon();
    IrReceiver.resume();
    break;

    case boton6:
    Serial.println ("5");
    bombaoff();
    IrReceiver.resume();
    break;

    case boton7:
      Serial.println ("6");
      leds1();
      IrReceiver.resume();
      break;
      
      case boton8:
      Serial.println ("7");
      leds2 ();
     IrReceiver.resume();
     break;

     case boton9:
     Serial.println ("8");
     ledoff();
     IrReceiver.resume ();
     break;
    

    default:
      Serial.println ("0");
      IrReceiver.resume();
    
  }
}

RFID();
          
}
