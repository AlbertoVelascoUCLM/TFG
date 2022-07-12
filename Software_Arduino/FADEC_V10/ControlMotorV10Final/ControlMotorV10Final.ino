//Definimos los pines que se van a utilizar para la comunición serie
#define PC Serial //RX0/TX0
#define FADEC Serial1 //RX1/TX1

//Definimos los pines de los actuadores del Arduino
#define Throttle 13  
#define Rele1 2
#define Rele2 4

//Definimos los comandos principales que es capaz de recibir el FADEC en hexadecimal
byte LeePantalla[] = {0xC7, 0x2C, 0x52, 0x53, 0x44, 0x2C, 0x0D};//RSV
byte LeerValoresActuales[] = {0xC7, 0x2C, 0x52, 0x43, 0x56, 0x2C, 0x0D};//RCV  RPM, EGT in ºC, Pump Power, Voltage of Battery, Throttle %

void setup() {
  //Inicializamos los puertos serie con su respectiva velocidad y esperamos a que estos esten configurados 
  PC.begin(115200);
  FADEC.begin(9600);   
  delay(1500);
  
  //Configuramos el tipo de pin de nuestros actuadores como salida
  pinMode(Throttle,OUTPUT);
  pinMode(Rele1,OUTPUT);
  pinMode(Rele2,OUTPUT);    
  delay(50);
}

void loop() {

    //Comprobamos si tenemos alguna entrada de comando desde MATLAB
    ControlesBasicosMotor();
    //Pedimos al FADEC que nos muestre la pantalla del HDT
    FADEC.write(LeePantalla, sizeof(LeePantalla));
    delay(50);
    //Pedimos al FADEC que nos muestre los datos de sus sensores
    FADEC.write(LeerValoresActuales, sizeof(LeerValoresActuales));
    //Leemos y enviamos los datos de los sensores de Arduino
    PC.print(DatosSensores());
    //Leemos los datos que nos ha enviadop el FADEC (HDT + sensores)
    if (FADEC.available()) {
      PC.println(FADEC.readString());
    }
    delay(100);   
}
