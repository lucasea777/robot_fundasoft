output_low(alimentado);
#define USB_CON_SENSE_PIN pin_c6
#define enumerando pin_c7
   if(usb_enumerated()&&(input(USB_CON_SENSE_PIN)))  //retorna verdadero si el dispositivo esta enumerado y conectado
   {
   output_high(enumerando);
      if(usb_cdc_kbhit())
      {  
         //usb_cdc_putc(usb_cdc_getc());
         get_usb_string(control , 10);
         if(control[0]=='g' && control[1]=='e' && control[2]=='t' )
         {
            get_usb_string(qvar , 20);  // 13 = enter , 32 = espacio
            
            qvar2="rel"    ; if(igual(qvar,qvar2,3))   printf(usb_cdc_putc, "%f\n\r" var1);
               
               
         }
         }

  
   }
   else
   {
      output_low(enumerando);
   }
   

/*
if(_bomba==1) { output_high(bomba); _bomba =0; }
if(_bomba==1) { output_high(bomba); _bomba =0; }
if(_bomba==1) { output_high(bomba); _bomba =0; }
if(_bomba==1) { output_high(bomba); _bomba =0; }
*/

/*   
  set -variable-  _valor_
  set -tbomOnS-   _valor_
  set -tbomOffS-  _valor_
  get -variable-
  get -tbomOff-
  get -tbomOn-
  resmem
  
  
*/

