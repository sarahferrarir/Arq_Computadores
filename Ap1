/*
O sistema aguarda no monitor serial um comando (caractere 'A') através do qual calcula e gera a distância em centímetros do objeto.
*/

//Este código captura e armazena as distâncias detectadas por um sensor ultrassônico
#define VEL_SOM 340 // definição da velocidade do som, em metros por seg

// declaração das variáveis globais
int pinEcho=6; // pino do Arduíno ligado ao pino Echo do sensor
int pinTrig=5; // pino do Arduíno ligado ao pino Trig do sensor
char led;

float disparaTrig(){  // A função diapara um sinal de trigger no pino pinTrig com largura de 10 microssegundos
  digitalWrite(pinTrig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pinTrig,LOW);
  return pulseIn(pinEcho,HIGH);  // determina o tempo em microssegundos
}

float lerDistancia(){
    float tempo, distancia;
      tempo = disparaTrig(); // dispara sinal de Trig E retorna a duracao do pulso (em microssegundos) que indica a distancia
      distancia=tempo*0.000001*VEL_SOM*100/2; // determina a distancia em cm     
      Serial.println("Distancia em centimetros: "); // apresenta o resultado
      Serial.println(distancia,DEC);  
}

float ligarLed(char led){
      if (led == 'A'){
        digitalWrite(8,HIGH);
    }
      if (led == 'B'){
        digitalWrite(9,HIGH);
      }
      if (led == 'C'){
        digitalWrite(10,HIGH);
      }
}

float desligarLed(char led){
  if (led == 'A'){
        digitalWrite(8,LOW);
    }
      if (led == 'B'){
        digitalWrite(9,LOW);
      }
      if (led == 'C'){
        digitalWrite(10,LOW);
      }
}

float ligarBuzzer(){
  digitalWrite(7,HIGH);
}

float desligarBuzzer(){
  digitalWrite(7,LOW);
}

//Defininda as chaves
#define ch1 2
#define ch2 3
#define ch3 4
#define ch4 A8
#define chEnter A9
#define chModo A10

//Vatiaveis a serem testadas
int val1=0, val2=0, val3=0, val4=0, valEnter=0, valModo=0;


void setup() {
  pinMode(pinEcho,INPUT);  // define os pinos do Arduíno
                           // Observe que o pino Echo de saída do módulo ultrassônico se conecta com o pino pinEcho de entrada do Arduíno   
  pinMode(pinTrig,OUTPUT); // Analogamente, o pino Trig de entrada do módulo ultrassônico se conecta com o pino pinTrig de saída do Arduíno
  // inicializa o pino de Trig e a porta serial
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(A8,INPUT);
  pinMode(A9,INPUT);
  pinMode(A10,INPUT);
  digitalWrite(pinTrig,LOW);
  Serial.begin(9600);

}

String comando;

void loop() {
  valModo = digitalRead(chModo);
  if (!valModo){
    if (Serial.available() > 0) { // Verifica se há sinal disponível na serial
      // leitura do byte de entrada:
      comando = Serial.readString();
      if (comando =="DIST_CHECK A"){
        lerDistancia();
      }
      if (comando == "LED_ON A"){
        ligarLed('A');
      }
      if (comando == "LED_ON B"){
        ligarLed('B');
      }
      if (comando == "LED_ON C"){
        ligarLed('C');
      }
      if (comando == "LED_OFF A"){
        desligarLed('A');
      }
      if (comando == "LED_OFF B"){
        desligarLed('B');
      }
      if (comando == "LED_OFF C"){
        desligarLed('C');
      }
      if (comando == "BUZZ_ON"){
        ligarBuzzer();
      }
      if (comando == "BUZZ_OFF"){
        desligarBuzzer();
      }
    }
  }
  
  else {
      // MODO PROG BINARIA
    val1 = digitalRead(ch1);
    val2 = digitalRead(ch2);
    val3 = digitalRead(ch3);
    val4 = digitalRead(ch4);
    valEnter = digitalRead(chEnter);
    
  
    if (!val1 && !val2 && !val3 && !val4 && valEnter){
      ligarLed('A');
    }
    if (!val1 && !val2 && !val3 && val4 && valEnter){
      desligarLed('A');
    }
    if (!val1 && !val2 && val3 && !val4 && valEnter){
      ligarLed('B');
    }
    if (!val1 && !val2 && val3 && val4 && valEnter){
      desligarLed('B');
    }
    if (!val1 && val2 && !val3 && !val4 && valEnter){
      ligarLed('C');
    }
    if (!val1 && val2 && !val3 && val4 && valEnter){
      desligarLed('C');
    }
    if (!val1 && val2 && val3 && !val4 && valEnter){
      ligarBuzzer();
    }
    if (!val1 && val2 && val3 && val4 && valEnter){
      desligarBuzzer();
    }
  delay(2000); //mantém ciclo de 2 seg de trabalho do sensor
  }
}
  
  

