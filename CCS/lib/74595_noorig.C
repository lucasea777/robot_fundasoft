///////////////////////////////////////////////////////////////////////////
////   Library for a 74595 Expanded Output Chip                        ////
////                                                                   ////
////   Any number of these chips may be connected in serise to get     ////
////   8 additional outputs per chip.  The cost is 3 I/O pins for      ////
////   any number of chips.                                            ////
////                                                                   ////
////   write_expanded_outputs(eo);  Writes the array eo to the chips   ////
////                                                                   ////
///////////////////////////////////////////////////////////////////////////
////        (C) Copyright 1996,2003 Custom Computer Services           ////
//// This source code may only be used by licensed users of the CCS C  ////
//// compiler.  This source code may only be distributed to other      ////
//// licensed users of the CCS C compiler.  No other use, reproduction ////
//// or distribution is permitted without written permission.          ////
//// Derivative programs created using this software in object code    ////
//// form are not restricted in any way.                               ////
///////////////////////////////////////////////////////////////////////////

/*
#IFNDEF EXP_OUT_ENABLE

#define EXP_OUT_ENABLE  PIN_A3
#define EXP_OUT_CLOCK   PIN_A1
#define EXP_OUT_DO      PIN_A2
#define NUMBER_OF_74595 1

#ENDIF


void write_expanded_outputs(BYTE* eo) {
  BYTE i;

  output_low(EXP_OUT_CLOCK);
  output_low(EXP_OUT_ENABLE);

  for(i=1;i<=NUMBER_OF_74595*8;++i) {  // Clock out bits from the eo array
    if((*(eo+(NUMBER_OF_74595-1))&0x80)==0)
      output_low(EXP_OUT_DO);
    else
      output_high(EXP_OUT_DO);
   shift_left(eo,NUMBER_OF_74595,0);
   output_high(EXP_OUT_CLOCK);
   output_low(EXP_OUT_CLOCK);
  }
  output_high(EXP_OUT_ENABLE);
  output_low(EXP_OUT_ENABLE);

}
*/
// I currently use only 1 x 74595.. u can modify to suit your project 
/*
void write_expanded_outputs(BYTE* eo) { 
  BYTE i; 
  BYTE tmp; // ++added, to hold data passed by pointer 

  // ++reason: if u manipulate data passed by pointer, ORIGINAL data will also be changed! 

  // re-assign data to temp variable 
  tmp = *eo; 

  output_low(EXP_OUT_CLOCK); 
  output_low(EXP_OUT_ENABLE); 

  for(i=1;i<=NUMBER_OF_74595*8;++i) {       // Clock out bits from the eo array 
  //if((*(eo+(NUMBER_OF_74595-1))&0x80)==0) // ++commented 
  if ((tmp & 0x80) == 0)                    // ++manipulate temp data 
    output_low(EXP_OUT_DO); 
  else 
    output_high(EXP_OUT_DO); 
   //shift_left(eo,NUMBER_OF_74595,0);  // ++ commented 
   tmp <<= 1;                           // ++manipulate temp data, shift 1 bit to the left 
   output_high(EXP_OUT_CLOCK); 
   output_low(EXP_OUT_CLOCK); 
  } 
  output_high(EXP_OUT_ENABLE); 
} 
*/


#define EXP_OUT_ST_CP   PIN_C1
#define EXP_OUT_SH_CP   PIN_C2
#define EXP_OUT_DS      PIN_C0
#define NUMBER_OF_74595 1


void write_expanded_outputs(char eo[])
{
int8 i;
for ( i=0 ; i<=7 ; i++)
{
if(eo[i]=='1') { output_high(exp_out_DS ); }
output_high(exp_out_SH_CP );
if(eo[i]=='1') { output_low (exp_out_DS ); }
output_low (exp_out_SH_CP );
// eo[0]=0; eo[1]=1; eo[2]=0;eo[3]=1; eo[4]=0;eo[5]=1; eo[6]=0;
}
output_high(exp_out_ST_CP );
output_low (exp_out_ST_CP );
//lcd_gotoxy(1,1); printf(lcd_putc "%u%u%u%u%u%u%u%u" eo[0]eo[1]eo[2]eo[3]eo[4]eo[5]eo[6]eo[7]);
//delay_ms(3000);
}

/*
secuencia original
output_high(exp_out_DS );
output_high(exp_out_SH_CP );
output_low (exp_out_DS );
output_low (exp_out_SH_CP );
output_high(exp_out_DS );
output_high(exp_out_SH_CP );
output_low (exp_out_DS );
output_low (exp_out_SH_CP );

output_high(exp_out_SH_CP );
output_low (exp_out_SH_CP );
   output_high(exp_out_SH_CP );
   output_low (exp_out_SH_CP );
output_high(exp_out_SH_CP );
output_low (exp_out_SH_CP );
   output_high(exp_out_SH_CP );
   output_low (exp_out_SH_CP );

output_high(exp_out_DS );
output_high(exp_out_SH_CP );
output_low (exp_out_DS );
output_low (exp_out_SH_CP );
output_high(exp_out_DS );
output_high(exp_out_SH_CP );
output_low (exp_out_DS );
output_low (exp_out_SH_CP );

output_high(exp_out_ST_CP );
output_low (exp_out_ST_CP );
*/
