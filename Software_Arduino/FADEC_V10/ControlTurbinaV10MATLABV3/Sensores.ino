const byte  PresionPin = A15; 
const byte  ValvulaGasPin = A14; 
const byte  ValvulaQueroPin = A13; 
const byte  StarterPin = A12;
const byte  BujiaPin = A11;
const byte  CombustiblePin = A10;
 
int Nmuestras = 5;



String DatosSensores(){
return "$SEN"+String(SensorPresion())+","+String(EstadoValvula(ValvulaGasPin))+","+String(EstadoValvula(ValvulaQueroPin))+","+String(EstadoStarter())+","+String(EstadoBujia())+","+String(SensorCombustible())+"SEN$";  
}

float SensorPresion(){
  float valor = 0;
  for (int i = 1; i <= Nmuestras; i++){
    valor = valor + analogRead(PresionPin);  
  }
  valor = ((valor/Nmuestras)/1023*5/216*(4/0.02)*1000);
  valor = map(valor,864,4000,0,4000);
  valor = valor/1000;
  return valor;
}

int EstadoValvula(byte pin){  
  return analogRead(pin)<50;
}

float EstadoStarter(){
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
