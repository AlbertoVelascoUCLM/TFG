//Definimos los comandos que es capaz de recibir el FADEC en hexadecimal
byte DatoArriba[] = {0xC7, 0x2C, 0x57, 0x44, 0x55, 0x2C, 0x0D};//WDU
byte DatoAbajo[] = {0xC7, 0x2C, 0x57, 0x44, 0x44, 0x2C, 0x0D};//WDD
byte MenuArriba[] = {0xC7, 0x2C, 0x57, 0x4D, 0x55, 0x2C, 0x0D};//WMU
byte MenuAbajo[] = {0xC7, 0x2C, 0x57, 0x4D, 0x44, 0x2C, 0x0D};//WDM
byte VersionAdaptador[] = {0xC7, 0x2C, 0x52, 0x41, 0x56, 0x2C, 0x0D};//WDM
byte LimitesMotor[] = {0xC7, 0x2C, 0x52, 0x44, 0x4C, 0x2C, 0x0D};//WDM

void ControlesBasicosMotor(){
  if (PC.available() > 0) {
    //Leemos datos recibidos de MATLAB como texto y eliminamos espacio del final  
    String DatosControl = PC.readString(); DatosControl.trim();

    //Convertimos el string de datos a su equivalente en float. Si es texto sale un 0. 
    float PorcentajeF = DatosControl.toFloat();

    //Convertimos el string de datos a char
    byte buffer[DatosControl.length() + 1];
    DatosControl.toCharArray(buffer,DatosControl.length() + 1);

    //En función del caracter recibido desde MATLAB haremos una cosa u otra.
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
        //Si ninguna de las letras anteriores ha sido envida quiere decir que el valor enviado es un numero o un valor no definido.
        //Si es un numero valido aceleramos. Si es otra cosa no hacemos nada.
        if(PorcentajeF <= 100 and PorcentajeF >= 0){Acelera(PorcentajeF);} 
    return; 
    } 
  }   
}

//Funcion de arranque automático para uso mediante terminal serie
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
  int ThrottleInput = round(PorcentajeF/100*200); //Traducimos el porcentaje del acelerador a valores de control (0 a 200)
  analogWrite(Throttle,String(ThrottleInput).toInt()); //Pone el acelerador al valor de control calculado
  return;
}

void ApagadoEmergencia(int Valor){
  //Si el valor está activado se activan los reles de corte de las electrovalvulas y se pone el acelerador a 0.
  if(Valor==1){
    analogWrite(Rele1,255);
    analogWrite(Rele2,255);
    analogWrite(Throttle,0);
  }
  //Si el valor está desactivado se desactivan los reles de corte de las electrovalvulas. 
  else {
    analogWrite(2,0);
    analogWrite(3,0);    
  }
}
