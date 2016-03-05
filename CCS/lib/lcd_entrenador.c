///////////////////////////////////////////////////////////////////////////
////                                                                   ////
////            Driver para LCD del Entrenador de PIC                 ////
////                                                                   ////
////   lcd_init();      inicializa los puertos del pic para el         ////
////                    funcionamiento del LCD.                        ////
////                                                                   ////
////   lcd_putc(c);     Muestra el caracter c en la próxima ubicación  ////
////                    del LCD. Tiene los siguientes caracters        ////
////                    especiales:                                    ////
////                      \f  Limpia el LCD                            ////
////                      \n  Va al comienzo de la 2º línea            ////
////                      \b  Regresa una posición.                    ////
////                                                                   ////
////   lcd_gotoxy(x,y); Setea una posición en el LCD(upper left is 1,1)////
////                                                                   ////
////   lcd_getc(x,y);   Retorna el caracter de la posición x,y         ////
////                    en el LCD                                      ////
////                                                                   ////
////   void lcd_unscroll (int line); Rota una linea del LCD            ////
////                                                                   ////
////    Memoria DDRAM del LCD = a Pantalla                             ////
////    Memoria CGRAM del LCD = Almacena caracteres                    ////
////                                                                   ////
////                            Pin Layout                             ////
////   -----------------------------------------------------------     ////
////   |                       |                                 |     ////
////   |     LCD               |           PIC                   |     ////
////   |                       |                                 |     ////
////   -----------------------------------------------------------     ////
////   | 1: ENABLE             |   1:  Pin10    RE2              |     ////
////   |                       |                                 |     ////
////   | 2: RS                 |   2:  Pin8     RE0              |     ////
////   |                       |                                 |     ////
////   | 3: RW                 |   3:  Pin9     RE1              |     ////
////   |                       |                                 |     ////
////   | 4: D4                 |   4:  Pin27    RD4              |     ////
////   |                       |                                 |     ////
////   | 5: D5                 |   5:  Pin28    RD5              |     ////
////   |                       |                                 |     ////
////   | 6: D6                 |   6:  Pin29    RD6              |     ////
////   |                       |                                 |     ////
////   | 7: D7                 |   7:  Pin30    RD7              |     ////
////   -----------------------------------------------------------     ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////



// Si no necesita utilizar caracteres en español comentar el siguiente define
// tener en cuenta que requiere 48 bytes de memoria RAM del PIC...

#define use_caracteres_espanioles                  //Utilizo caracteres en Español

// Define los caractreres en español

#if defined use_caracteres_espanioles

char a_conacento[] = {  0b0000010,
                        0b0000100,
                        0b0001110,
                        0b0000001,
                        0b0001111,
                        0b0010001,
                        0b0001111,
                        0b0000000
                     };

char e_conacento[] = {  0b0000010,
                        0b0000100,
                        0b0001110,
                        0b0010001,
                        0b0011110,
                        0b0010000,
                        0b0001110,
                        0b0000000
                     };

char i_conacento[] = {  0b1111111,
                        0b0000000,
                        0b0000000,
                        0b0000000,
                        0b0000000,
                        0b0000000,
                        0b0000000,
                        0b0000000
                     };

char o_conacento[] = {  0b0000010,
                        0b0000100,
                        0b0001110,
                        0b0010001,
                        0b0010001,
                        0b0010001,
                        0b0001110,
                        0b0000000
                      };

char u_conacento[] = {  0b0000010,
                        0b0000100,
                        0b0010001,
                        0b0010001,
                        0b0010001,
                        0b0010011,
                        0b0001101,
                        0b0000000
                      };

char letra_enie[] =  {  0b0001110,
                        0b0000000,
                        0b0010110,
                        0b0011001,
                        0b0010001,
                        0b0010001,
                        0b0010001,
                        0b0000000
                      };


#endif

struct lcd_pin_map                                 // Pines definidos en el puerto A
            {
               int     unused : 4;
               int     data : 4;
            } lcd_data;


struct lcd_pin_map2                                // Pines definidos en el puerto E
            {
               BOOLEAN rs;
               BOOLEAN rw;
               BOOLEAN enable;
               int unused : 5;
            } lcd_ctrl;


#if defined(__PCH__)                               //En función del compilador utilizado defino

   #byte lcd_data = 0xF83                          // on to port D
   #byte lcd_ctrl = 0xF84                          // on to port E

#else

   #byte lcd_data = 8                              // en el puerto D
   #byte lcd_ctrl = 9                              // en el puerto E

#endif

#define  LCD_MAXROWS		   ((byte)(2))
#define	LCD_MAXCOLS		   ((byte)(16))
#define	LCD_MULTI_LINE		(TRUE)

#define set_tris_lcdData(x) set_tris_d(x)

#define set_tris_lcdCtrl(y) set_tris_e(y)

//Define la configuración del LCD

#define lcd_type 2                                 // 0=5x7, 1=5x10, 2=2 lines

#define lcd_line_two 0x40                          // LCD RAM address for the second line


BYTE const LCD_INIT_STRING[4] = {0x20 | (lcd_type << 2), 0xc, 1, 6};

//Asigna valores a las estructuras para las operaciones de Lectura/Escritura

struct lcd_pin_map const LCD_WRITED = {0,0};       // Para Escritura
struct lcd_pin_map2 const LCD_WRITEC = {0,0,0,0};
struct lcd_pin_map const LCD_READD = {0,15};       // Para Lectura
struct lcd_pin_map2 const LCD_READC = {0,0,0,0};


/*************************************************************************/
/*
/*           BYTE lcd_read_byte()
/*
/*           Funcion:      Lee un valor de la RAM interna del LCD
/*
/*           Parametros:   No se le pasan parámetros.
/*
/*           Retorno:      El valor de la posición actual de la RAM
/*                         en un byte.
/*
/*************************************************************************/


BYTE lcd_read_byte()

{

      BYTE low,high;

      set_tris_lcdData (LCD_READD);
      set_tris_lcdCtrl (LCD_READC);

      lcd_ctrl.rw = 1;
      delay_cycles(1);
      lcd_ctrl.enable = 1;
      delay_cycles(1);

      high = lcd_data.data;

      lcd_ctrl.enable = 0;
      delay_cycles(1);
      lcd_ctrl.enable = 1;
      delay_us(1);

      low = lcd_data.data;

      lcd_ctrl.enable = 0;

      set_tris_lcdData(LCD_WRITED);
      set_tris_lcdCtrl(LCD_WRITEC);

      return( (high<<4) | low);
}

/*************************************************************************/
/*
/*           void lcd_send_nibble( BYTE n )
/*
/*           Funcion:      Manda al lcd un nibble
/*
/*           Parametros:   valor de 4 bits a mandar.
/*
/*           Retorno:      No retorna nada
/*
/*************************************************************************/

void lcd_send_nibble( BYTE n )

{
      lcd_data.data = n;

      delay_cycles(1);
      lcd_ctrl.enable = 1;
      delay_us(2);
      lcd_ctrl.enable = 0;
}

/*************************************************************************/
/*
/*           void lcd_send_byte( BYTE address, BYTE n )
/*
/*           Funcion:      Manda un byte al LCD
/*
/*           Parametros:   Una Address que define si el valor se mandará
/*                         a la DDRAM (1) o a la CGRAM(0). Además se manda el
/*                         valor a gurdar.
/*
/*           Retorno:      No retorna nada.
/*
/*************************************************************************/

void lcd_send_byte( BYTE address, BYTE n )

{

      lcd_ctrl.rs = 0;

      while ( bit_test(lcd_read_byte(),7) ) ;

      lcd_ctrl.rs = address;

      delay_cycles(1);
      lcd_ctrl.rw = 0;
      delay_cycles(1);
      lcd_ctrl.enable = 0;

      lcd_send_nibble(n >> 4);
      lcd_send_nibble(n & 0xf);
}

/*************************************************************************/
/*
/*           void lcd_gotoxy( BYTE x, BYTE y)
/*
/*           Funcion:      Rutina que ubica el cursor del LCD en la posición
/*                         x,y.
/*
/*           Parametros:   Posición x e y en la que se quiere ubicar el cursor.
/*
/*           Retorno:      No retorna nada
/*
/*************************************************************************/

void lcd_gotoxy( BYTE x, BYTE y)

{
   BYTE address;

   if(y!=1)
     address=lcd_line_two;
   else
     address=0;

   address+=x-1;

   lcd_send_byte(0,0x80|address);
}

/*************************************************************************/
/*
/*           void lcd_putc( char c)
/*
/*           Funcion:      Muestra el caracter c en el display
/*
/*           Parametros:   Caracter c tipo char.
/*
/*           Retorno:      No retorna nada.
/*
/*************************************************************************/


void lcd_putc( char c)

{
   switch (c)
   {
     case '\f'   : lcd_send_byte(0,1);
                   delay_ms(2);
                   break;

     case '\n'   : lcd_gotoxy(1,2);
                   break;

     case '\b'   : lcd_send_byte(0,0x10);
                   break;

#if defined use_caracteres_espanioles

     case 'á'    : lcd_send_byte (1, 1);
                   break;

     case 'é'    : lcd_send_byte (1, 2);
                   break;

     case 'í'    : lcd_send_byte (1, 3);
                   break;

     case 'ó'    : lcd_send_byte (1, 4);
                   break;

     case 'ú'    : lcd_send_byte (1, 5);
                   break;

     case 'ñ'    : lcd_send_byte (1, 6);
                   break;

#endif

     default     : lcd_send_byte(1,c);
                   break;

   }

}

/*************************************************************************/
/*
/*           char lcd_getc( BYTE x, BYTE y)
/*
/*           Funcion:      Rutina que devuelve el valor de caracter ubicado en
/*                         la posición x,y del LCD.
/*
/*           Parametros:   Posición x e y del caracter a conocer.
/*
/*           Retorno:      El valor ASCII de caracter de esa posición.
/*
/*************************************************************************/

char lcd_getc( BYTE x, BYTE y)

{
    char value;

    lcd_gotoxy(x,y);

    while ( bit_test(lcd_read_byte(),7) ); // Espera que se desocupe el LCD

    lcd_ctrl.rs=1;
    value = lcd_read_byte();
    lcd_ctrl.rs=0;

    return(value);
}

/*************************************************************************/
/*
/*           void lcd_unscroll (int line)
/*
/*           Funcion:      Esta función rota una line del LCD
/*
/*           Parametros:   Se le pasa la línea a rotar.
/*
/*           Retorno:      No retorna nada.
/*
/*************************************************************************/

void lcd_unscroll (int line)
{

   int largo = 30;
   int x = 1, y;
   char oldchar, newchar, firstchar;

   y = line;

   lcd_gotoxy (x, y);
   firstchar = lcd_getc (x, y);
   x = largo;

   lcd_gotoxy (x, y);
   newchar = lcd_getc (x, y);
   lcd_gotoxy (x, y);
   lcd_putc (firstchar);

   do
   {
      lcd_gotoxy (--x, y);
      oldchar = lcd_getc (x, y);
      lcd_gotoxy (x, y);
      lcd_putc (newchar);
      newchar = oldchar;

   } while ( x != 1);

}

/*************************************************************************/
/*
/*           void lcd_define_char(byte c, char *bitmap)
/*
/*           Funcion:      Esta función carga caracteres definidos por el
/*                         usuario en la CGRAM del LCD.
/*
/*           Parametros:   Se le pasa la posición del caracter a definir y
/*                         la dirección al array que contiene la definición.
/*
/*           Retorno:      No retorna nada.
/*
/*************************************************************************/

void lcd_define_char(byte c, char *bitmap)

{
	byte	i;

   lcd_send_byte (0, ((0b01000000) | (c << 3)));	// Selecciona el caracter a definir

	for (i = 0; i < 8; i++)
		lcd_send_byte (1, (*bitmap++));				   //	Pone cada byte en la memoria

}

/*************************************************************************/
/*
/*           void lcd_init()
/*
/*           Funcion:      Rutina de Inicialización del LCD según los parámetros
/*                         definidos al principio.
/*
/*           Parametros:   No se le pasan parámetros.
/*
/*           Retorno:      No retorna nada.
/*
/*************************************************************************/

void lcd_init()

{
    BYTE i;

    set_tris_lcdData(LCD_WRITED);
    set_tris_lcdCtrl(LCD_WRITEC);

    lcd_ctrl.rs = 0;
    lcd_ctrl.rw = 0;
    lcd_ctrl.enable = 0;

    delay_ms(15);

    for(i=1;i<=3;++i)
    {
       lcd_send_nibble(3);
       delay_ms(5);
    }
    lcd_send_nibble(2);

    for(i=0;i<=3;++i)
       lcd_send_byte(0,LCD_INIT_STRING[i]);

#if defined use_caracteres_espanioles
    delay_ms (1);

    lcd_define_char (1, a_conacento);
    lcd_define_char (2, e_conacento);
    lcd_define_char (3, i_conacento);
    lcd_define_char (4, o_conacento);
    lcd_define_char (5, u_conacento);
    lcd_define_char (6, letra_enie);

#endif

   lcd_putc("\f");
}
