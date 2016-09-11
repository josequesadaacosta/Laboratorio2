/** ENCABEZADOS
*@file semaforo.c
*@brief Experimento 2. IE 0624 Laboratorio de Microcontroladores.
*@autor Andrés Quesada Acosta, B04927. José Pablo Martínez Hernández, B34024.
*@date 7 de septiembre del 2016.
*/

/** Definimos las variables a usar */

/** Luz roja vehicular en el PIN 12 */
int LR = 12;   
/** Luz amarilla vehicular en el PIN 11 */          
int LA = 11; 
/** Luz verde vehicular en el PIN 10 */            
int LV = 10;  
/** Luz roja peatonal en el PIN 9 */           
int LrP = 9; 
/** Luz verde peatonal en el PIN 8 */            
int LvP = 8; 
/** Inicializamos el Botón en el PIN 2*/           
int boton = 2;  
/** Inicializamos el tiempo de paso peatonal */         
int Tpp = 10000; 
/** Inicializamos el tiempo de luz verde vehicular minimo*/        
int TvMin=10000;  
/** Inicializamos el almacenar tiempo desde ultima vez que semaforo vehicular se pone en verde*/       
unsigned long ContTvMin; 
/** Buzzer en el PIN 6 */
int buzz = 6; //pin buzzer
/** Inicializamos un lector del estado del PIN 2*/
int state = digitalRead(boton);
/** Inicializamos un contador*/
int cuenta=0;


/** Ajustamos todas las funciones de los pines que se van a usar */
void setup () {
Serial.begin(9600);
  pinMode(LR, OUTPUT);
  pinMode(LA, OUTPUT);
  pinMode(LV, OUTPUT);
  pinMode(LrP, OUTPUT);
  pinMode(LvP, OUTPUT);
  pinMode(boton, INPUT);
  pinMode (buzz, OUTPUT);
  /** Seleccionamos una lectura del tiempo en alto de la luz verde los carros */
  digitalWrite(LV,HIGH); 
  /** Seleccionamos una lectura del tiempo en alto de la luz roja de los peatones */
  digitalWrite(LrP, HIGH);
  /** Inicializamos un lector del estado del PIN 2*/
  int state = digitalRead(boton);
}

void loop(){
  /** Hacemos pruebra de la lectura usando la consola de Arduino. Nota: extra. */
  state = digitalRead(boton);
  Serial.println(cuenta);
  
/**
* @brief Contador de solicitud de paso. 
* @param Estado del botón.
* @return Si el estado es alto suma un valor a la cuenta de veces que se ha presionado el botón, si el estado está en bajo la cuenta se mantiene igual.
*/
 if(state==HIGH){cuenta=cuenta+1;} 
/** Verificar si el botón ha sido presionado */

/**
* @brief Verfica si se tiene que realizar un cambio de luces. 
* @param Número de veces que se ha presionado el botón, el tiempo transcurrido por el sistema.
* @return Si el número de veces de solocitud del semáforo es igual o mayor que 1 y además se ha transcurrido un tiempo mínimo de encendido de la luz de los carros se activa el cambio, sino las luces se mantienen igual
*/
  and it is over 5 sec since last button press*/
 if(cuenta>=1 && (millis() - ContTvMin )> TvMin) {
	/** Función que activa el cambio de luces y la señal sonora */
    pasoPeatonal();  
  
  }
else {state = digitalRead(boton);}
}

/**
* @brief Activa el cambio de luces 
* @param Número de veces que se ha presionado el botón, el tiempo transcurrido por el sistema.
* @return Parpadeo del cambio de luces con los tiempos configurados, los parpadeos correspondientes y la señal sonora
*/

void pasoPeatonal() {
	/** Parpadeo paso Luz verde vehicular 3s */
  for (int i=0; i<6; i++){
    digitalWrite(LV,HIGH);
    delay(250);
    digitalWrite(LV,LOW);
    delay(250);
  }
  /** Luz verde de los carros se apaga */
  digitalWrite(LV,LOW); 
  /** Luz amarilla de los carros se prende y luego de el sistema mantiene ese estado por 2s */
  digitalWrite(LA,HIGH); 
  delay(2000); 
  
  /** Luz amarilla de los carros se apaga */
  digitalWrite(LA,LOW); 
  /** Luz roja de los carros se prende */
  digitalWrite(LR,HIGH); 
  /** El sistema mantiene este estado por 1s y luego se procede a realizar el cambio de la luz peatonal*/
  delay(1000); 
  
  /** Se apaga la luz roja peatonal */
  digitalWrite(LrP,LOW); 
  /** La luz verde peatonal se prende permitiendo el paso de los peatones */
  digitalWrite(LvP,HIGH); 
  
/**
* @brief Activa el parpadeo de las luces y la señal sonora 
* @param Que se hayan cumplido los requisitos para el cambio de luces
* @return Parpadeo y la señal sonora en el buzzer
*/

  /** Este ciclo genera un retraso de 5s */
  for (int j=0; j<5; j++){
	 /** Se enciende un tono y luego se apaga */
     tone(6, 440,500);
     delay (1000);
	 /** Se enciende un tono y luego se apaga */
      tone(6, 330,500);
     delay (1000);
   }

   /** Este ciclo genera un retraso de 3s, un parpadeo la luz verde peatonal y una señal sonora más intensa */
  for (int x=0; x<6; x++){
    /** Se enciende un tono y la luz verde peatonal */
    digitalWrite(LvP,HIGH);
    tone(6, 440,250);
    delay(250);
	/** Se apaga el tono y la luz verde peatonal */
    digitalWrite(LvP,LOW);
    delay(250);
  }
  
  /** Enciende Luz roja peatonal */
  digitalWrite(LrP, HIGH); 
  delay(1000);
 
 /** Enciende luz verde de los carros y apagamos la luz roja de los carros*/
  digitalWrite(LV,HIGH); 
  digitalWrite(LR,LOW); 
 
 /** Iniciamos la cuenta del tiempo de encendido de la verde para así luego poder comprobar que ha transcurrido el tiempo minimo de encendido de dicha luz */
  ContTvMin = millis();
  
 /** Reinicia el valor de las veces que se ha sido solicitado el paso en cero y se repite el ciclo */
 cuenta=0;
}