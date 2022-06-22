#define PC Serial //RX0/TX0
#define FADEC Serial1 //RX1/TX1

void setup() { 
  PC.begin(57600);
  FADEC.begin(9600);   
  delay(500);
  SetupControlesBasicos();
}

void loop() {
  ControlesBasicosMotor();
}
