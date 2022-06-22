String DatosControl = "";

void SetupControlesBasicos(){ 
  #define Throttle 13  
  pinMode(13,OUTPUT);
  PC.println("Introduce un valor entre 0 y 100 para acelerar");  
  PC.println("Introduce 'A' para iniciar secuencia de Arranque");
}

void ControlesBasicosMotor(){
  //PC.println("CONTROL");
  if (PC.available() > 0) {
    //Leemos datos recibidos como texto y eliminamos espacio del final  
    DatosControl = PC.readString(); DatosControl.trim(); 

    //Convertimos datos a float para conservar los decimales. Si se mete una letra en el serial el tofloat la convierte en 0.00
    float PorcentajeF = DatosControl.toFloat();

    if(DatosControl == "A"){Arranque();}
    else if(PorcentajeF <= 100 and PorcentajeF >= 0){Acelera(PorcentajeF);}
    else{PC.println("Valor no permitido. Debe ser 'A' o debe estar entre 0.0 y 100.0");} 
    return; 
  }  
}
//███FUNCIONES███
void Arranque(){
  PC.println("████████████████████");
  PC.println("Iniciando secuencia de arranque...");
  delay(2000); Acelera(0);  //Trim 0
  delay(2000); Acelera(100);  //Trim 100
  delay(2000); Acelera(25); //Trim idle
  delay(500); PC.println("Completada");
  return;
}

void Acelera(float PorcentajeF){
  int ThrottleInput = round(PorcentajeF/100*200); //Porcentaje a valores de control
  float ThrottleInputF = float(ThrottleInput);  //Porcentaje real de control en vase a variable de control
  PC.println("Aceleracion: " + String(ThrottleInputF /200*100) + "%"); analogWrite(Throttle,String(ThrottleInput).toInt()); //Acelera a valores de control
  return;
}
