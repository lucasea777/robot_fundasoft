float S_t_F (char s[7])  // 123.23 0 003.23
   {  
      int n[7];
      float data;
      float cien = 100;
      
      int i;
      for(i=0;i<6;i++)
      {
      n[i]=s[i]-48;
      if(n[i]>9)
      n[i]=0;
      }
      data = ( n[0] * cien ) ;
      data = data + ( n[1] * 10 ) +( n[2] )+( n[4]*0.1 )+( n[5]*0.01 );
      return(data);
   }                 
int16 S_t_I16 (char s[4])  //1234 o 0002
   {
      int n[4];
      int16 data;
      int16 const cien = 100;  // ccs no multiplica por 100 si 100 no es el valor de una variable :O
      
      int i;
      for(i=0;i<4;i++)
      {
      n[i]=s[i]-48;
      if(n[i]>9)
      n[i]=0;
      }
      data =  n[0] * 1000 + n[1] * cien + n[2] * 10 + n[3] ;
      
      return(data);
   } 
void get_usb_string(char s[] , int8 max)
   {  
      int kbhit = 0;
      while(kbhit < max)
      {
         s[kbhit] = usb_cdc_getc(); 
               usb_cdc_putc(s[kbhit]); //espejo            
               if(s[kbhit]==13) {        
                  usb_cdc_putc("\n");  //espejo enter
                  kbhit=max; }
               if(s[kbhit]==32)
                  kbhit=max;
              // if(s[kbhit]==8) { //espejo return
              //    kbhit--; }
         
         kbhit++;
      }
   }
   
void get_usb_string_sin_esp(char s[] , int8 max)
   {  
      int kbhit = 0;
      while(kbhit < max)
      {
         s[kbhit] = usb_cdc_getc(); 
               usb_cdc_putc(s[kbhit]); //espejo            
               if(s[kbhit]==13) {        
                  usb_cdc_putc("\n");  //espejo enter
                  kbhit=max; }
              // if(s[kbhit]==8) { //espejo return
              //    kbhit--; }
         
         kbhit++;
      }
   }
int1 igual(char a[],char b[] , ncaracteres) {
ncaracteres--; 
int8 i; 
int1 r=1;
for (i=0 ; i<=ncaracteres ; i++) {
if(a[i]!=b[i]) r=0;
} return(r); }

   
