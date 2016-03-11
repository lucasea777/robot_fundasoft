// fuente: http://www.forosdeelectronica.com/f24/envio-hola-ccs-usb-atraves-hid-18f2550-46955/
// no es necesario modificar otro archivo aparte de este!!!!!

//comentar si se esta usando la CPU_5 en vez de la proto!
//#define PROTOBOARD //ACA Y EN FUNDABOT.H

#ifdef PROTOBOARD
#include <18f2550.h>           //archivo de cabecera
#else
#include <18f4550.h>           //archivo de cabecera
#endif

//#fuses HSPLL,MCLR,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,NOVREGEN,NOPBADEN // fuses  configurados
#fuses hspll,nowdt,noprotect,nolvp,nodebug,usbdiv,pll5,cpudiv1,vregen,nomclr      //cdc FUNCIONA! :D

#use delay(clock=20000000)     // el clock que tendremos a la entrada del CPU compatible con USB 2.0
//#use rs232(baud=9600, xmit=PIN_C6, rcv=PIN_C7, BITS=8) //para debuguear las salidas del printf,puts etc.

#ifdef PROTOBOARD
#include <\lib\flex_lcd_2.c>
#endif

#define USB_CONFIG_HID_RX_SIZE 10  //lucas!!!
#define USB_CONFIG_HID_TX_SIZE 10  //lucas!!!

#DEFINE USB_HID_DEVICE  TRUE // Si usar HID 
#define USB_CONFIG_PID  0x0020
#define  USB_CONFIG_VID 0x0461

//Habilitar la Transferencia
#define USB_EP1_TX_ENABLE  USB_ENABLE_INTERRUPT   //Activa el punto final 1 para transferencias por bloque 
#define USB_EP1_TX_SIZE    8                      //8 bytes  para envio
//Habilitar la Recepcion
#define USB_EP1_RX_ENABLE  USB_ENABLE_INTERRUPT   //Activa el punto final 1 para recepcion por bloque 
#define USB_EP1_RX_SIZE    8                      //8 bytes para recepcion

#include <pic18_usb.h>      //Funciones de bajo nivel(hardware) para la serie PIC 18Fxx5x que serviran en usb.c
#include <lib/usb_desc_hid.h>    //Aqui es donde van las descripciones de este dispositivo (como lo reconocera windows)
#include <usb.c>            //libreria para el manejo del usb

//funciones en pic18_usb.h
//Posibles estados del USB
// USB_STATE_DETACHED=0, USB_STATE_ATTACHED=1, USB_STATE_POWERED=2, USB_STATE_DEFAULT=3,
// USB_STATE_ADDRESS=4, USB_STATE_CONFIGURED=5
//usb_init()
//             se desconecta usando usb_init_cs y luego entra en un ciclo infinito monitoriado por
//             usb_task hasta que el estado del usb sea POWERED 
//usb_init_cs()
//             es un alias de usb_detach()
//usb_put_packet()
//             envia un paquete al HOST
//usb_kbhit()
//             devuelve TRUE si hay datos enviados por HOST(PC)
//usb_rx_packet_size()
//             devuelve el tamano del paquete enviado por el HOST(PC)
//usb_get_packet()
//             realiza la recepcion de la informacion enviada por el HOST(PC)
//usb_detach()
//             Se Desconecta y se pone en estado DETACHED
//usb_attach()
//             Se Conecta
//usb_attached() 
//             Para dispositivos que no tienen este pin simpre devuelve TRUE como el 18F2550
//             devuelve TRUE si USB_CON_SENSE_PIN = TRUE el pin que indica si esta conectado o no
//usb_task()
//             Monitorea el estado de la coneccion conectandose y desconectandose automaticamente


//funciones en usb.c necesita de la libreria de hardware
//usb_enumerated()
//             devuelve TRUE si el HOST(PC) ya enumero el dispositivo o sea si windows ya lo detecto
//usb_wait_for_enumeration()
//             espera infinitamente hasta que el dispositivo fue enumerado 
//usb_kbhit()
//             devuelve TRUE si hay datos enviados por HOST(PC)
//usb_puts()
//             como el puts serial solo que este es USB usa la funcion put packet 
//usb_gets()    
//             como el gets serial solo que este es USB usa la funcion get packet 

#ifdef PROTOBOARD
	#define PIN_HEART pin_a1
	#define PIN_ENUMERATED pin_a0
#else
	#define PIN_HEART pin_d0
	#define PIN_ENUMERATED pin_d1
	#define PIN_ENABLE pin_d7
	#define PIN_IN4 pin_d6
	#define PIN_IN3 pin_d5
	#define PIN_IN2 pin_d4
	#define PIN_IN1 pin_d3
	//#define PIN_ENABLE pin_d2
#endif

#define PACKAGE_LENGTH 10

#use rtos(timer=0, minor_cycle=10ms)

   int8 out_data[20];
   int8 in_data[2];
   int8 send_timer=0;
   int8 contador=0;
   char Mensaje[4]={'H','O','L','A'};
   char mensaje_boton1[5]={'B','O','T','O','N'};
   int1 avise = false;
   
   char recivido[PACKAGE_LENGTH];   

int strncmp(char * str1, char * str2, int len);

int strncmp(char * str1, char * str2, int len) {
	int i = 0;
	for (i = 0; i < len; ++i)
		if (str1[i] != str2[i])
			return 0;
	return 1;
}

#task(rate=10ms, max=10ms)
void checkear_terminal() {
   //#include <terminal_hid.c>
   if (usb_enumerated()) {
      if(!avise) {
      	 #ifdef PROTOBOARD
         lcd_gotoxy(1,1);printf(lcd_putc ,"Enumere!! :D"); //<<protoboard>>
         #endif
         output_high(PIN_ENUMERATED);
         avise = true;
      }
      //usb_puts(1,Mensaje,4,100);
      if (usb_kbhit(1)) {
      	usb_gets(1, &recivido, PACKAGE_LENGTH, 100);
         #ifdef PROTOBOARD
         lcd_gotoxy(1,1);printf(lcd_putc ,"kbhit!! :D");
         lcd_gotoxy(1,1);printf(lcd_putc ,"                 ");
         lcd_gotoxy(1,1);printf(lcd_putc , "Recivi %s", recivido);
         #endif
         char cmp[3] = "IN4";
         usb_puts(1,recivido,PACKAGE_LENGTH,100); //package length esta bien o mando basura?
         char wi[3] = "wii";
         if (strncmp(recivido,cmp,3)) {
         	output_toggle(PIN_IN4);
         	usb_puts(1,wi,3,100); //package length esta bien o mando basura?

         }
      }
   }
   /*if (avise && !usb_enumerated()) {   	
      lcd_gotoxy(1,1);printf(lcd_putc ,"Desenumere!! :D");
   }*/
}

#task(rate=1000ms, max=10ms)
void hid_heart_beat() {
   if(usb_enumerated())
      usb_puts(1,Mensaje,4,100);
}

#task(rate=500ms, max=10ms)
void heart_beat() {
   output_toggle(PIN_HEART);
}

#task(rate=20ms, max=10ms)
void mandar_boton() {
   //if(input(PIN_C7)){
   //   usb_puts(1,mensaje_boton1,5,100);
   //}
   delay_ms(80);
}

void main() {
   setup_adc_ports(NO_ANALOGS);  // desactivando puertos analogicos   
   //set_tris_b(0x0);              // configurando los puertos como salidas
   //output_b (0);                 // saca un nivel bajo de salida en los puertos

   #ifdef PROTOBOARD
   lcd_init();
   lcd_gotoxy(1,1);printf(lcd_putc ,"Espero... ");
   #endif  

   usb_init(); //inicializa y espera a ser encendido
   //usb_task (); //lucas!
   #ifdef PROTOBOARD
   lcd_gotoxy(1,1);printf(lcd_putc ,"Inicializado"); //<<protoboard>>
   #endif
   
   //usb_wait_for_enumeration(); //ahora espera hasta ser enumerado (reconocido por la PC)    
   //lcd_gotoxy(1,1);printf(lcd_putc ,"Enumere!! :D");
 
   /*while(TRUE){
      usb_puts(1,Mensaje,4,100);
      delay_ms(500);
   }
   */
   output_high(PIN_ENABLE);
   output_high(PIN_HEART);
   rtos_run();
   while (true) {      
      
   }
}
