// utilidades para eeprom
//Agosto-2010 Modificado para eeproms con mas de 256 bytes
///////////////////////////////////////////////////////////////////////////////
void eewrite_float(int16 address, float data)
// Escribe un float a la eeprom interna
// entradas: int16 address, dato float
{

int16 t;
  //data=5.87654;
  for(t = 0; t < 4; ++t){
    write_eeprom(t + address, *((int8*)&data + t) );
  }
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void eewrite_int32(int16 address, int32 data)
// Escribe un float a la eeprom interna
// entradas: int16 address, dato float
{

int16 t;
  //data=5.87654;
  for(t = 0; t < 4; ++t){
    write_eeprom(t + address, *((int8*)&data + t) );
  }
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
float eeread_float(int16 address)
// leer un float desde la eeprom interna
// entrada: la direccion de la eeprom
// salida: el valor float recuperado
{

  int16 t;
  float data;

  for(t = 0; t < 4; ++t){
    *((int8*)&data + t) = read_eeprom(address + t);
  } 
  return data;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
float eeread_int32(int16 address)
// leer un float desde la eeprom interna
// entrada: la direccion de la eeprom
// salida: el valor float recuperado
{

  int16 t;
  int32 data;

  for(t = 0; t < 4; ++t){
    *((int8*)&data + t) = read_eeprom(address + t);
  } 
  return data;
}
///////////////////////////////////////////////////////////////////////////////

