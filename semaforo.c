//definicion de variables
int LR = 12;  //luz roja vehicular
int LA = 11; // 
int LV = 10; //luz verde vehicular
int LrP = 9; // luz roja peatonal
int LvP = 8; //luz verde peatonal
int boton = 2; // Boton
int Tpp = 10000;  //tiempo de paso peatonal
int TvMin=10000; // tiempo de luz verde vehicular minimo
unsigned long ContTvMin; // almacenar tiempo desde ultima vez que semaforo vehicular se pone en verde

int buzz = 6; //pin buzzer
int state = digitalRead(boton);
int cuenta=0;


void setup () {
Serial.begin(9600);
  pinMode(LR, OUTPUT);
  pinMode(LA, OUTPUT);
  pinMode(LV, OUTPUT);
  pinMode(LrP, OUTPUT);
  pinMode(LvP, OUTPUT);
  pinMode(boton, INPUT);
  pinMode (buzz, OUTPUT);
 
  digitalWrite(LV,HIGH); //start with green car light on
  digitalWrite(LrP, HIGH); //start with red ped light on
   int state = digitalRead(boton);
}

void loop(){
  state = digitalRead(boton);
  Serial.println(cuenta);
 if(state==HIGH){cuenta=cuenta+1;} 
// int state = digitalRead(boton);	
  /* check if button is pressed
  and it is over 5 sec since last button press*/
 if(cuenta>=1 && (millis() - ContTvMin )> TvMin) {
    pasoPeatonal();  //function to change lights
  
  }
else {state = digitalRead(boton);}
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
  for (int j=0; j<5; j++){
     tone(6, 440,500);
     delay (1000);
      tone(6, 330,500);
     //digitalWrite(buzz,LOW);
     delay (1000);
   }//  delay preset time of 5 seconds
  
  //flashing of ped green light

  for (int x=0; x<6; x++){
    digitalWrite(LvP,HIGH);
    tone(6, 440,250);
    delay(250);
    digitalWrite(LvP,LOW);
    delay(250);
  }
 
  digitalWrite(LrP, HIGH); //turn red ped light on
  delay(1000);
 
  digitalWrite(LV,HIGH); //car green light on
  digitalWrite(LR,LOW); //car red light off
 
  ContTvMin = millis(); // inicia la cuenta del tiempo en verde minimo 
 cuenta=0;
}