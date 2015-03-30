#include <toneAC.h>

  // intensidad del brillo del arreglo de leds
  int intensity = 0;

  // pin al que esta conectado el arreglo de leds
  int ledPin = 3; 
  
  // pin del trigger del ultrasonido que mapea la frecuencia
  int trig_freq = 11;
    
  // pin del echo del ultrasonido que mapea la frecuencia
  int echo_freq = 12;

  // centmetros que se debe acercar un obstculo para aumentar una octava
  float cms_por_octava= 40;
  
  /* frecuencia maxima: frecuencia terica maxima que se alcanza cuando hay un obstculo a 0 centimetros.
   * esta nunca se alcanza porque la distancia minima medida por el ultrasonido es de 2cms
   * la frecuencia minima sera freq_max*(0.5^(400/cms_por_octava))
  */
  float freq_max = 4000;
  
  // frecuencia minima del sonido, si el sensor arroja una distancia que mapea una frecuencia menor, el generador se apaga
  int freq_min = 40;

  // pin del trigger del ultrasonido que mapea la frecuencia
  int trig_vol = 5;
    
  // pin del echo del ultrasonido que mapea la frecuencia
  int echo_vol = 6;
 
  
  
void setup(){  
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(trig_freq, OUTPUT); 
  pinMode(echo_freq, INPUT);
  pinMode(trig_vol, OUTPUT); 
  pinMode(echo_vol, INPUT);
  
}

void loop(){
  
  intensity=map(analogRead(2),256, 1023,0,255);
  if(intensity<0){
    intensity=0;
  }    
  
  analogWrite(ledPin, intensity);
  generarSonido();
  
}
/*
 * Esta funcion controla un ultrasonido, devuelve la distancia medida en centimetros.
 * Parmetros:
 *  - trig: pin conectado al trigger, que recibe el pulso que indica al ultrasonido que debe hacer un sensado
 *  - echo: pin conectado al echo, que produce un pulso de duracion proporcional a la distancia 
 *
 * Retorna: (float) distancia en centmetros.
 */
float medirDistancia(int trig, int echo){
  digitalWrite(trig,LOW); /* Por cuestión de estabilización del sensor*/
  delayMicroseconds(5);
  digitalWrite(trig, HIGH); /* envío del pulso ultrasónico*/
  int now = millis();
  while(!digitalRead(echo) && millis() - now <0){}

  float distancia = ((float) pulseIn(echo, HIGH, 29000))/58; 

 
  return distancia == 0 ? 500 : distancia; 
}


/*
 * Esta funcion genera, modifica o apaga el sonido generado por un pwm
 * La frecuencia aumenta exponencialmente para que sea amigable con la percepcion humana
 *
 */
int generarSonido(){
  // Obtencion de la distancia a partir del cual se mapea la frecuencia del sonido.
  float distanciaF = medirDistancia(trig_freq, echo_freq);

  // Obtencion de la distancia a partir del cual se mapea el volumen del sonido.
  float distanciaV = medirDistancia(trig_vol, echo_vol);
  
  
    
  // se calcula la frecuencia a partir de la distancia medida por uno de los ultrasonidos
  int frecuencia =  (int) freq_max*pow(0.5, distanciaF/cms_por_octava);
  
  // se calcula el volumen (de 1 a 10) a partir de la distancia medida por uno de los ultrasonidos  
  int volumen = (int) (400 - distanciaV)/40;
  
  
  if(frecuencia < freq_min || volumen<0){
    noToneAC(); 
  } 
  
  else{
    toneAC(frecuencia,volumen);    
  }
  
  Serial.print("  ");  
  Serial.print(frecuencia);
  Serial.print("  ");  
  Serial.println(volumen);
  

}


