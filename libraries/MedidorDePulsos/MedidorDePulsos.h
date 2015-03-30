#ifndef medidorDePulsos_h
#define medidorDePulsos_h
#include <WString.h>
#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

class MedidorDePulsos
{
  public:
    MedidorDePulsos(int pin);
    void medirPulsoEnAlto(int pin);
    unsigned long darDuracionUltimoPulso(int pin);
    void enviarPulsoCorto(int pin, int duracionMicros, unsigned long tiempoDeEsperaMillis);

private:

unsigned long nextTimeTo;
unsigned long inicial;
boolean ultraState;  
unsigned long anchoPulso;

};
#endif
 
