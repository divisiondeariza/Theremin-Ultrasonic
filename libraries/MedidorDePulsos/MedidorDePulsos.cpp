#include "MedidorDePulsos.h"

MedidorDePulsos::MedidorDePulsos(int pin){
nextTimeTo=0;
inicial=0;
ultraState=false;  
anchoPulso=1000000;

}

void MedidorDePulsos::medirPulsoEnAlto(int pin){
 
  
  if(digitalRead(pin)&&!ultraState){
  inicial=micros();
  ultraState=true;
  }

  if(!digitalRead(pin)&&ultraState){
  ultraState=false;
  
  if(micros()>inicial){
  anchoPulso=micros()-inicial; 
  }
 
}
}

unsigned long MedidorDePulsos::darDuracionUltimoPulso(int pin){
return anchoPulso;}


void MedidorDePulsos::enviarPulsoCorto(int pin, int duracionMicros, unsigned long tiempoDeEsperaMillis) { 

    if(nextTimeTo<millis()&&!ultraState){    
    
    nextTimeTo=millis()+tiempoDeEsperaMillis;
    digitalWrite(pin, HIGH);   // set the LED on
    delayMicroseconds(duracionMicros);              // wait for a second
    digitalWrite(pin, LOW);    // set the LED off
  }
}
  


