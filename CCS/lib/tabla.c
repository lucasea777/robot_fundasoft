float funcion(float X , float  X1 , float Y1 , float X2 , float Y2 )
{
float Y = 0;
/*
X  = 0 ;
X1 = 2 ;
Y1 = -1;
X2 = -3;
Y2 = -2;
*/
Y = (X * Y2 - X * Y1 - Y2 * X1 + X2 * Y1) / ( X2 - X1 ) ;

return(Y);
}


float tabla(float X )
{

float Y ;

if( X >= 0.00 && X <  X1  )  Y = funcion( X ,  0.00 , 0.00 , X1 , Y1 ) ;
if( X >=  X1  && X <  X2  )  Y = funcion( X ,   X1  ,  Y1  , X2 , Y2 ) ;
if( X >=  X2  && X <  X3  )  Y = funcion( X ,   X2  ,  Y2  , X3 , Y3 ) ;
if( X >=  X3  && X <  X4  )  Y = funcion( X ,   X3  ,  Y3  , X4 , Y4 ) ;

return(Y);
}
