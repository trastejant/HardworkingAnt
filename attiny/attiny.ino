/***
 * *****************************HardworkingAnt************************************
 * *                                                                             * 
 * * Sketch para emplear un attiny como extensor de pines o ADC por interfaz I2C *
 * *  Totalmente abstraido del Hardware conectado a sus GPIOS                    * 
 * *                                                                             * 
 * ******************************ByCrakerNano*************************************
 * *******************************4Trastejant*************************************
 ***
 */

#include <TinyWire.h> //Se inicia la librería TinyWire
byte own_address = 10; //Dirección del Digispark en el bus I2C

void setup() {
  TinyWire.begin(own_address); //Se entra al bus I2C en la direccion 10  
  TinyWire.onRequest(onI2CRequest);//Si se nos solicita información
  TinyWire.onReceive(onI2CReceive);//Si recibimos información del maestro
}
 
void loop() {
}


//Contestamos para saber que el Attiny está vivo
void onI2CRequest() {
  String msg = "hola"; //Mensaje a enviar
  for (int i = 0; i < msg.length(); i++) {
    TinyWire.send(msg.charAt(i)); //Se envia el mensaje caracter por caracter
  }  
}


/***
 * Formato del mensaje recibido 0x00
 * 0x -> Lectura (0) Escritura(1) 
 * x0 -> Número de pin
 * x_0 -> Estado en el que escribir el pin LOW(0) HIGH(1)
 * 
 */

 //devuelve la lectura analogica del pin pedido
float readPin(int pin){
  pinMode(pin, INPUT);
  return analogRead(pin);
}


//Escribe el pin solicitado al estado pedido
bool writePin(int pin, int state){
  pinMode(pin, OUTPUT);
  digitalWrite(pin, state);
  return true;
}

//!!Implementar control de errores
void failMsg(){
  
}

//Leemos la solicitud del maestro 
void onI2CReceive(){
  int i = 0;
  char msg[]={'0','0','0','0'};
  
  while(TinyWire.available()){
    msg[i] = TinyWire.read();         
    i++;
  }

  if(msg[0]=='0'){
    readPin(msg[2]);//numero de pin
  }else if(msg[0]=='1'){
    writePin(msg[2],msg[3]);//pin, estado
  }else{
    failMsg();
  }
}

