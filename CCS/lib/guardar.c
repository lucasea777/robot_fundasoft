#include <math.h>
#include <internal_eeprom.c>
float READ_FLOAT_EEPROM(long int n);

void WRITE_FLOAT_EEPROM(long int n, float data);
void WRITE_FLOAT_EEPROM(long int n, float data)
{
int8 a,b,c,d,e;

a=  floor(data/100)                               ;
b=  floor(data/10)  -a*10                         ;
c=  floor(data)     -a*100   -b*10                ;
d=  floor(data*10)  -a*1000  -b*100  -c*10        ;
e=  floor(data*100) -a*10000 -b*1000 -c*100 -d*10 ;

write_eeprom(n+1,a);
write_eeprom(n+2,b);
write_eeprom(n+3,c);
write_eeprom(n+4,d);
write_eeprom(n+5,e);
}

float READ_FLOAT_EEPROM(long int n)
{
float data;
int8 a,b,c,d,e;

a = read_eeprom(n+1);
b = read_eeprom(n+2);
c = read_eeprom(n+3);
d = read_eeprom(n+4);
e = read_eeprom(n+5);


data = ( a * 100 ) ;
data = data + ( b * 10 ) +( c )+( d*0.1 )+( e*0.01 );
return(data);
}
