#include <Servo.h>
#include <MFRC522.h>
#include <SPI.h>
#define RST_PIN  9    //Pin 9 para el reset del RC522
#define SS_PIN  10   //Pin 10 para el SS (SDA) del RC522
MFRC522 mfrc522(SS_PIN, RST_PIN); //Creamos el objeto para el RC522

Servo servoMotor1;
Servo servoMotor2;
Servo servoMotor3;

int vel = 0;
int servoSpeed = 5;
//CONTROL INFRARROJO
//int IR = 11;     

void setup() {
  Serial.begin(9600);
servoMotor1.attach(4);
servoMotor2.attach(3);
servoMotor3.attach(2);
  SPI.begin();        //Iniciamos el Bus SPI
  mfrc522.PCD_Init(); // Iniciamos  el MFRC522
  Serial.println("Lectura del UID");
}

void loop() {
int po;
po = Serial.read();

switch (po) {
  case '1':
  rotativo1();
  break;

  case '2':
  rotativo2();
  break;

  
  case '3':
  break;
  
  default:
  Serial.println ("ÑO");
  
  
}

RFID();
}

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
                   servoMotor1.write (0);    
            }      
  } 
}



void rotativo1 (){
  vel = 180;
  servoMotor2.write(vel);              
  delay(1500);
  vel = 0;
  servoMotor2.write(vel);              
  delay(1500);
  
}

void rotativo2 (){
  // Mueve el servomotor en una dirección
  for (int pos = 90; pos <= 180; pos += servoSpeed) {
    servoMotor3.write(pos);  // Establece la posición del servomotor
    delay(15);  // Pequeña pausa para permitir el movimiento suave
  }
  
  delay(5000);  // Espera 5 segundos
  
  // Detiene el servomotor
  servoMotor3.write(90);  // Establece la posición del servomotor a 90 grados
  delay(1000);  // Espera 1 segundo antes de repetir el ciclo
}              



void leds (){
  
}
