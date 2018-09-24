//Bluetooth HC06_firm-linvor1.5

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


//  SerialIn_SerialOut_HM-10_01
//
//  Uses hardware serial to talk to the host computer and AltSoftSerial for communication with the bluetooth module
//
//  What ever is entered in the serial monitor is sent to the connected device
//  Anything received from the connected device is copied to the serial monitor
//  Does not send line endings to the HM-10
//
//  Pins
//  BT VCC to Arduino 5V out. 
//  BT GND to GND
//  Arduino D8 (SS RX) - BT TX no need voltage divider 
//  Arduino D9 (SS TX) - BT RX through a voltage divider (5v to 3.3v)
//AT+NAME
//AT+PIN
 
#include <AltSoftSerial.h>
#include "DRV8825.h"
AltSoftSerial BTserial; 
// https://www.pjrc.com/teensy/td_libs_AltSoftSerial.html
char c=' ';
boolean NL = true;

// Quantidade de passos por volta completa 
#define MOTOR_STEPS 200
 
// Definição de pinos DIR e STEP
#define DIR 7
#define STEP 6
// Pinos de controle do DRV8825
#define MODE0 12
#define MODE1 11
#define MODE2 10

// Instância da biblioteca para controle do Driver
DRV8825 stepper(MOTOR_STEPS, DIR, STEP, MODE0, MODE1, MODE2);

boolean sentido = true;
int LDR=0;
int mapLDR=0;
//String EnviaLDR;

char setPointRecebido;
int valorSetPoint=0;

char centenaLDR;
  char dezenaLDR;
  char unidadeLDR;

int confirmaCEM;

void setup() 
{
    Serial.begin(9600);
    //Serial.print("Sketch:   ");   Serial.println(__FILE__);
    //Serial.print("Uploaded: ");   Serial.println(__DATE__);
    //Serial.println(" ");
 
    BTserial.begin(9600);  
    //Serial.println("BTserial started at 9600");

    // Inicio da instância
    stepper.begin(60);
    stepper.setMicrostep(1); // modo 1

  //Timer1.initialize(1000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  //Timer1.attachInterrupt( envia_ValorLDR ); // attach the service routine here
}
 
void loop()
{
  
    // Read from the Bluetooth module and send to the Arduino Serial Monitor
    if (BTserial.available())
    {
      valorSetPoint = 0;
      int contInteracao = 1;
      while(BTserial.available()>0)
      {
      setPointRecebido = BTserial.read();
      
      if(setPointRecebido == '%') break;

      if(contInteracao == 1) valorSetPoint = (setPointRecebido-48)*100;
      else if(contInteracao == 2) valorSetPoint = valorSetPoint + (setPointRecebido-48)*10;
      else if(contInteracao == 3) valorSetPoint = valorSetPoint + setPointRecebido-48;
      
      Serial.write(setPointRecebido);
      contInteracao++;
      
      }
      Serial.write("---");
      Serial.println(valorSetPoint);
    }
 
 
    // Read from the Serial Monitor and send to the Bluetooth module
    if (Serial.available())
    {
        c = Serial.read();
        
        if (c!=10 & c!=13 ) BTserial.write(c);

        
        else if (c==10) NL = true;
        
        else if (NL == true) { Serial.print("\r\n>"); NL = false; }

        //else if (c == 'a' || c == 'A') { sentido = !sentido; moveMotor(); }
     
        Serial.write(c);
    }

//    le_sensor();
    delay(10);
//    move_motor();
//    envia_ValorLDR();

     LDR=0; //Zera a variável LDR
  int cont=analogRead(A5);
  for(int i=0;i<=5;i++) //Faz 10 vezes a leitura do sensor
  {
  cont=analogRead(A0); //Lê o valor do sensor (LDR ligado ao pino A0) e guarda na variável LDR
  LDR = LDR+cont; //Armazenamento na varíavel LDR o valor lido + o valor anterior
  delay(1); //Delay se 10 milissegundos
  }
  LDR=LDR/5;
  mapLDR = map(LDR,0,1023,0,100);


if(valorSetPoint < mapLDR) { stepper.move(15);  delay(1);}
else if(valorSetPoint > mapLDR) { stepper.move(-15);  delay(1);}


delay(10);

centenaLDR = (mapLDR/100)+48;
 dezenaLDR = ((mapLDR%100)/10) + 48;
 unidadeLDR = (dezenaLDR%10) + 48;

 BTserial.write("A_");
 delay(2);
 BTserial.write(centenaLDR);
 delay(2);
 BTserial.write(dezenaLDR);
 delay(2);
 BTserial.write(unidadeLDR);
 delay(2);

}
