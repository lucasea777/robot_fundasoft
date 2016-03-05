#Funda Bot
Robot cuatrimotor controlado por PIC 18F2550/4550.

La idea es tener una GUI super sencilla con "flechitas" para controlar 
el robot. 

Se podria controlar este instantaneamente haciendo click en las 
felchitas o mejor aun guardando una secuencia de movimientos y luego 
ejecutandola como si se tratace de "guardar un programa y luego ejecutarlo"


##Tecnologia
El robot es controlado desde la pc por medio de un canal bidireccional:

```
PC <<[wifi]>> smarthphone <<[USB(otg)]>> pic <<[L298N]>> motores
```

###PC
Utilizando la tecnologia NW.JS se diseña la GUI y se conecta con el smartphone 
mediante un socket simple, quizas utilizando HTTP y un protocolo del estilo:

```
--> {"comando":"adelante", "cantidad_en_metros":2.5}
<-- {"status":"OK"}
```

###Smartphone
El smartphone solo servira como puente (wifi<->usb).

Para esto se expandira una [terminal HID de codigo abierto](https://github.com/452/USBHIDTerminal) agregandole sockets.

###PIC
Se utilizara el microcontrolador pic 18F2550/4550
