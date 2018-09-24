
#include "DRV8825.h"
 
// Quantidade de passos por volta completa 
#define MOTOR_STEPS 200
 
// Definição de pinos DIR e STEP
#define DIR 7
#define STEP 6

 
 
// Pinos de controle do DRV8825
   #define MODE0 10
   #define MODE1 11
   #define MODE2 12
 
// Instância da biblioteca para controle do Driver
   DRV8825 stepper(MOTOR_STEPS, DIR, STEP, MODE0, MODE1, MODE2);
 
void setup() {
    stepper.begin(120);
}
 
void loop() {
    
    stepper.setMicrostep(1); // modo 1
 
   
    delay(2000);
    
    stepper.move(100);
    stepper.rotate(360);
    
    delay(2000); // aguarda 1s
 
   
    stepper.move(-100);
    stepper.rotate(-360);
    
    delay(2000); // aguarda 1s
 }
