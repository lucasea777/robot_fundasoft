//output_low(alimentado);
#define attached pin_c6
   if(usb_enumerated()&&input(attached))  //retorna verdadero si el dispositivo esta enumerado y conectado
   {
   
      if (!avise_enum_flag) {
         lcd_gotoxy(1,2);printf(lcd_putc, "Enumere!! :D..       "); 
         avise_enum_flag = 1;
      }
      if(usb_cdc_kbhit())
      {  
         //usb_cdc_putc(usb_cdc_getc());
         get_usb_string(control , 10);
         if(control[0]=='g' && control[1]=='e' && control[2]=='t' )
         {
            get_usb_string(qvar , 20);  // 13 = enter , 32 = espacio
            
            float setPointPorc = 0.00;
            
            qvar2="sp"     ; if(igual(qvar,qvar2,2))   printf(usb_cdc_putc, "%f\n\r" setPointPorc);
            qvar2="a2"     ; if(igual(qvar,qvar2,2))   printf(usb_cdc_putc, "%f\n\r" v);
         }
         
         if(control[0]=='m' && control[1]=='s' && control[2]=='j' )
         {
            get_usb_string(qvar , 20);  // 13 = enter , 32 = espacio
            
            float setPointPorc = 0.00;
            
            qvar2="sp"     ; if(igual(qvar,qvar2,2))   printf(usb_cdc_putc, "%f\n\r" setPointPorc);
            qvar2="a2"     ; if(igual(qvar,qvar2,2))   printf(usb_cdc_putc, "%f\n\r" v);
         }
      }
   }
