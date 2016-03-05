void varBot(tb1,b1,b2,b4,var1,var2,var3,vista)
{
if(tb1>=50)
{
switch (vista) {
case 1: { 
if(b1==1)
{
if(b4==1)
var1=var1+0.01; 
else 
var1=var1+0.10; 
}
}
case 2: var2=var2+0.01;
case 3: var3=var3+0.01;
}
tb1=0;
}
}

