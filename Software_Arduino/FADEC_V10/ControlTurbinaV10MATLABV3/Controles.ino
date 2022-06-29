byte DatoArriba[] = {0xC7, 0x2C, 0x57, 0x44, 0x55, 0x2C, 0x0D};//WDU
byte DatoAbajo[] = {0xC7, 0x2C, 0x57, 0x44, 0x44, 0x2C, 0x0D};//WDD
byte MenuArriba[] = {0xC7, 0x2C, 0x57, 0x4D, 0x55, 0x2C, 0x0D};//WMU
byte MenuAbajo[] = {0xC7, 0x2C, 0x57, 0x4D, 0x44, 0x2C, 0x0D};//WDM
byte VersionAdaptador[] = {0xC7, 0x2C, 0x52, 0x41, 0x56, 0x2C, 0x0D};//WDM
byte LimitesMotor[] = {0xC7, 0x2C, 0x52, 0x44, 0x4C, 0x2C, 0x0D};//WDM

void SetupControlesBasicos(){ 
  #define Throttle 13  
  pinMode(13,OUTPUT);
}

void ControlesBasicosMotor(){
  if (PC.available() > 0) {
    //Leemos datos recibidos como texto y eliminamos espacio del final  
    String DatosControl = PC.readString(); DatosControl.trim();    
    float PorcentajeF = DatosControl.toFloat();
    
    byte buffer[DatosControl.length() + 1];
    DatosControl.toCharArray(buffer,DatosControl.length() + 1);
    //Convertimos datos a float para conservar los decimales. Si se mete una letra en el serial el tofloat la convierte en 0.00

    switch (DatosControl[0]){
      case 'A':{Arranque();break;}
      case 'B':{FADEC.write(LeerValoresActuales, sizeof(LeerValoresActuales));break;}
      case 'C':{FADEC.write(DatoArriba, sizeof(DatoArriba));break;}
      case 'D':{FADEC.write(DatoAbajo, sizeof(DatoAbajo));break;}
      case 'E':{FADEC.write(MenuArriba, sizeof(MenuArriba));break;}
      case 'F':{FADEC.write(MenuAbajo, sizeof(MenuAbajo));break;}
      case 'G':{FADEC.write(VersionAdaptador, sizeof(VersionAdaptador));break;}
      case 'H':{FADEC.write(LimitesMotor, sizeof(LimitesMotor));break;}
      case 'Z':{ApagadoEmergencia(1);break;}
      case 'X':{ApagadoEmergencia(0);break;}
      default:
        PC.println("Hola");
        if(PorcentajeF <= 100 and PorcentajeF >= 0){Acelera(PorcentajeF);}
        else{PC.println("Valor no permitido. Debe ser 'ARRANCAR' o debe estar entre 0.0 y 100.0");} 
    return; 
    } 
  }   
}
//███FUNCIONES███
void Arranque(){
  PC.println("████████████████████");
  PC.println("Iniciando secuencia de arranque...");
  delay(1000); Acelera(0);  //Trim idle
  delay(1000); Acelera(25);  //Trim idle
  delay(1000); Acelera(100);  //Trim 100
  delay(1000); Acelera(25); //Trim idle
  delay(500); PC.println("Completada");
  return;
}

void Acelera(float PorcentajeF){
  int ThrottleInput = round(PorcentajeF/100*200); //Porcentaje a valores de control
  float ThrottleInputF = float(ThrottleInput);  //Porcentaje real de control en vase a variable de control
  analogWrite(Throttle,String(ThrottleInput).toInt()); //Acelera a valores de control
  return;
}

void ApagadoEmergencia(int Valor){
  if(Valor==1){
    analogWrite(2,1000);
    analogWrite(3,1000);
  }  
  else {
    analogWrite(2,0);
    analogWrite(3,0);    
  }
}
