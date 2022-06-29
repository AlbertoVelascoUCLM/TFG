#define PC Serial //RX0/TX0
#define FADEC Serial1 //RX1/TX1

String dato = "";


byte LeePantalla[] = {0xC7, 0x2C, 0x52, 0x53, 0x44, 0x2C, 0x0D};//RSV

byte LeerValoresActuales[] = {0xC7, 0x2C, 0x52, 0x43, 0x56, 0x2C, 0x0D};//RCV  RPM, EGT in ºC, Pump Power, Voltage of Battery, Throttle %
//String BufferSensores = "$SEN0,0,0,0,0SEN$";



void setup() { 
  PC.begin(115200);
  FADEC.begin(9600);   
  delay(1500);
  
  #define Throttle 13  
  pinMode(13,OUTPUT);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
}

void loop() {
    delay(50);
    ControlesBasicosMotor(); 
    FADEC.write(LeePantalla, sizeof(LeePantalla));
    delay(50);
    FADEC.write(LeerValoresActuales, sizeof(LeerValoresActuales));
    PC.print(DatosSensores());
    LeeFADEC(); 
    //LeeFADEC();    
}

void LeeFADEC(){
    if (FADEC.available()) {
      dato = FADEC.readString();
      //PC.println("FADEC:");
      PC.println(dato);
      delay(50);
    }
  
  }
