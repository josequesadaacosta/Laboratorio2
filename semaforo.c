/car lights being assigned
int LR = 12;  //luz roja vehicular
int LA = 11; // 
int LV = 10; //luz verde vehicular
int LrP = 9; // luz roja peatonal
int LvP = 8; //luz verde peatonal
int boton = 2; // Boton
int Tpp = 10000;  //tiempo de paso peatonal
int TvMin=10000; // tiempo de luz verde vehicular minimo
unsigned long ContTvMin; // almacenar tiempo desde ultima vez que semaforo vehicular se pone en verde

void setup () {
Serial.begin(9600);
  pinMode(LR, OUTPUT);
  pinMode(LA, OUTPUT);
  pinMode(LV, OUTPUT);
  pinMode(LrP, OUTPUT);
  pinMode(LvP, OUTPUT);
  pinMode(boton, INPUT);
 
  digitalWrite(LV,HIGH); //start with green car light on
  digitalWrite(LrP, HIGH); //start with red ped light on
  
}

void loop(){
	
  /* check if button is pressed
  and it is over 5 sec since last button press*/
  int state = digitalRead(boton);
  Serial.println (state);
  if(state==HIGH && (millis() - ContTvMin )> TvMin) {
    pasoPeatonal();  //function to change lights
  
  }
}

void pasoPeatonal() {
	//Parpadeo paso Luz verde vehicular 3s
  for (int i=0; i<6; i++){
    digitalWrite(LV,HIGH);
    delay(250);
    digitalWrite(LV,LOW);
    delay(250);
  }
  digitalWrite(LV,LOW);  //green car light off
  digitalWrite(LA,HIGH); // yellow car light on
  delay(2000); //wait 2 seconds

  digitalWrite(LA,LOW); // yellow car light off
  digitalWrite(LR,HIGH); //red car light on
  delay(1000); //wait 1 second to turn on ped light

  digitalWrite(LrP,LOW); //red ped light off
  digitalWrite(LvP,HIGH); //green ped light on. allow crossing
  delay(Tpp); //  delay preset time of 5 seconds
  //flashing of ped green light
  for (int x=0; x<6; x++){
    digitalWrite(LvP,HIGH);
    delay(250);
    digitalWrite(LvP,LOW);
    delay(250);
  }
 
  digitalWrite(LrP, HIGH); //turn red ped light on
  delay(1000);
 
  digitalWrite(LV,HIGH); //car green light on
  digitalWrite(LR,LOW); //car red light off
 
  ContTvMin = millis(); // inicia la cuenta del tiempo en verde minimo 
