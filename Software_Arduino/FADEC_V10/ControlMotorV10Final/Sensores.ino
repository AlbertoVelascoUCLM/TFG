//Definimos los pines analogicos de cada sensor
const byte  PresionPin = A15; 
const byte  ValvulaGasPin = A14; 
const byte  ValvulaQueroPin = A13; 
const byte  StarterPin = A12;
const byte  BujiaPin = A11;
const byte  CombustiblePin = A10;

//Definimos el numero de muestras que vamos a utilizar al medir la presión o el voltaje del starter
int Nmuestras = 5;



String DatosSensores(){
//Esta funcion se encvarga de generar una trama con los datos de los sensores
return "$SEN"+String(SensorPresion())+","+String(EstadoValvula(ValvulaGasPin))+","+String(EstadoValvula(ValvulaQueroPin))+","+String(VoltajeStarter())+","+String(EstadoBujia())+","+String(SensorCombustible())+"SEN$";  
}

float SensorPresion(){
  float valor = 0;
  for (int i = 1; i <= Nmuestras; i++){
    valor = valor + analogRead(PresionPin);  
  }
  //%Valor leido*Amperajepormuestra*barpor amperio*correcciónparamapeo 

  //La suma de valores logicos obtenida se divide entre el numero de muestras para sacar la media.
  //Este valor medio los dividimos entre el total de valores lógicos (1023) para obtener el porcentaje de voltios que tenemos respecto a 5 voltios.
  //Una vez hecho esto multiplicamos el porcentaje por 5 para sacar los voltios y lo dividimos entre  
  valor = ((valor/Nmuestras)/1023*5/221*(4/0.02)*1000);
  valor = map(valor,864,4000,0,4000);
  return valor;
}

int EstadoValvula(byte pin){  
  return analogRead(pin)<50;
}

float VoltajeStarter(){
  float valor = 0;
  for (int i = 1; i <= Nmuestras; i++){
    valor = valor + analogRead(StarterPin);   
  }
  return valor/5/1023*10;
}

float EstadoBujia(){
  return analogRead(BujiaPin)>10;
}

float SensorCombustible(){
  float valor = 0;
  for (int i = 1; i <= Nmuestras; i++){
    valor = valor + analogRead(CombustiblePin);   
  }
  return map(valor/Nmuestras/1023*5*100,500,5000,100,1000);
}
