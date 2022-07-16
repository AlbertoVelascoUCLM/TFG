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
//Esta funcion se encvarga de generar una trama de texto con los datos de los sensores
return "$SEN"+String(SensorPresion())+","+String(EstadoValvula(ValvulaGasPin))+","+String(EstadoValvula(ValvulaQueroPin))+","+String(VoltajeStarter())+","+String(EstadoBujia())+","+String(SensorCombustible())+"SEN$";  
}

float SensorPresion(){
  //Definimos una variable como float
  float valor = 0;
  //Muestreamos la señal varias veces para evitar el ruido en los datos
  for (int i = 1; i <= Nmuestras; i++){
    //Leemos el pin del sensor de prersión y almacenamos el valor
    valor = valor + analogRead(PresionPin);  
  }
  //La suma de valores logicos obtenida se divide entre el numero de muestras para sacar la media.
  //Este valor medio los dividimos entre el total de valores lógicos (1023) para obtener el porcentaje de voltios que tenemos respecto a 5 voltios.
  //Una vez hecho esto multiplicamos el porcentaje por 5 para sacar el voltaje, este voltaje si lo dividimos entre el valore de la resistencia utilizada nos da el amperaje de la señal del sensor, que al multiplicar 1000 obtenemos en mA.
  //Se vuelve a multiplicar por mil porque solo se pueden interpolar numeros enteros
  valor = ((valor/Nmuestras)/1023*5/221*1000*1000);
  //Desplazamos el cero absoluto hasta los 4 mA  e interpolamos valores de 0 a 4000 milibares entre 4 y 20 mA.
  //Por limitaciones de Arduino los float no muestran mas de dos decimales, entonces debemos enviar la presión medida en milibares.
  valor = map(valor,4*1000,20*1000,0,4000);
  return valor;
}

int EstadoValvula(byte pin){ 
  //Leemos el valor lógico correspondiente al voltaje de la electroválvula, si este es inferior a 50 quiere decir que el voltaje es cercano a 0V.
  //Como se ha detallado en el documento, el FADEC para activar estas cambia el voltaje de uno de los pines de estas a 0V.
  //Entonces cuando el voltaje leido por Arduino es cercano a 0V se considera que la válvula esta abierta, por tanto se manda un 1 (valor bionario).
  //Si el voltaje es lejano a los 0V, se manda un 0.
  return analogRead(pin)<50;
}

float VoltajeStarter(){
  //Definimos una variable como float
  float valor = 0;
  //Muestreamos la señal varias veces para evitar el ruido en los datos
  for (int i = 1; i <= Nmuestras; i++){
    valor = valor + analogRead(StarterPin);   
  }
  //La suma de valores logicos obtenida se divide entre el numero de muestras para sacar la media.
  //Este valor medio los dividimos entre el total de valores lógicos (1023) para obtener el porcentaje de voltios que tenemos respecto a 5 voltios.
  //Como el divisor de tensión tiene una realción de 1/2 si multiplicamos lo obtenido anteriormente por 2 obtendremos el voltaje real.
  return valor/Nmuestras/1023*5*2;
}

float EstadoBujia(){
  //Leemos el valor lógico correspondiente al voltaje de la bujía, si este es mayor a 10 quiere decir que esta activada, por tanto se manda un 1 (valor bionario).
  //Si el valor es inferior a 10 esta apagaada, se manda un 0.
  return analogRead(BujiaPin)>10;
}


//Esta funcion se preparó para una futura adición de un sensor de flujo McMillan Flow Sens 104, si el sensor de combustible utilizado no es el mismo hay que modificarla.
float SensorCombustible(){
  //Definimos una variable como float
  float valor = 0;
  for (int i = 1; i <= Nmuestras; i++){
    valor = valor + analogRead(CombustiblePin);   
  }
  valor=valor/Nmuestras/1023*5*1000;
  return map(valor,500,5000,100,1000);
}
