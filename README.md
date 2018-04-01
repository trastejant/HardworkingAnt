# HardworkingAnt

Sketch para emplear un attiny como extensor de pines o ADC por interfaz I2C totalmente abstraido del Hardware conectado a sus GPIOS 

## Formato de la solicitud

Formato del mensaje recibido 0x00
 * 0x -> Lectura (0) Escritura(1) 
 * x0 -> Número de pin
 * x_0 -> Estado en el que escribir el pin LOW(0) HIGH(1)
 
 ## Instrucciones
 En el chip que hará de esclavo y se comportará como extensor de pines y/o ADC por interfaz I2C unicamente debemos carcar el código contenido en el fichero /attiny/attiny.ino
 
 El maestro solicitará la lectura o escritura del pin que desee mediante la librería HardworkingAnt
 
 ## Funciones de la librería para el maestro
