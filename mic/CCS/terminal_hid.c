if (usb_enumerated()) {
   if(!avise) {
      lcd_gotoxy(1,1);printf(lcd_putc ,"Enumere!! :D");
      avise = true;
   }
   //usb_puts(1,Mensaje,4,100);
   if (usb_kbhit(1)) {
      lcd_gotoxy(1,1);printf(lcd_putc ,"kbhit!! :D");
      usb_gets(1, &recivido, PACKAGE_LENGTH, 100);
      lcd_gotoxy(1,1);printf(lcd_putc ,"                 ");
      lcd_gotoxy(1,1);printf(lcd_putc , "Recivi %s", recivido);

   }
}
if (avise && !usb_enumerated()) {
   lcd_gotoxy(1,1);printf(lcd_putc ,"Desenumere!! :D");
}
