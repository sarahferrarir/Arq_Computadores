#include <DHT.h> // biblioteca do sensor de temperatura e umidade DHT11
#include <DHT_U.h>
#define DHTPIN A0 // pino do Arduíno ligado ao sensor DHT11
#define DHTTYPE DHT11 // DHT 11
#define VEL_SOM 340 // definição da velocidade do som, em metros por seg

// declaração das variáveis globais
int progSerial = 0;
int pinEcho=6; // pino do Arduíno ligado ao pino Echo do sensor
int pinTrig=5; // pino do Arduíno ligado ao pino Trig do sensor
char led; 
int r,g,b; 
int ldr = A1;//Atribui A1 a variável ldr
int valorldr = 0;//Declara a variável valorldr como inteiro
DHT dht(DHTPIN, DHTTYPE);
String comando;
String modo;

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

float lerTemp(){
  float t = dht.readTemperature();
  // testa se retorno é valido, caso contrário algo está errado.
  if (isnan(t)) {
    Serial.println("Failed to read from DHT");
  } 
  else {
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" *C");
  }
}

float lerLuminosidade(){
  valorldr = analogRead(ldr); //Lê o valor do sensor ldr e armazena na variável valorldr
  Serial.print("Valor lido pelo LDR = "); //Imprime na serial a mensagem Valor lido pelo LDR
  Serial.println(valorldr); //Imprime na serial os dados de valorldr
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

int definirCorRGB(int r,int g,int b){
  if (r == 1){
    digitalWrite(11,HIGH);
  }
  if (g == 1){
    digitalWrite(12,HIGH);
  }
  if (b == 1){
    digitalWrite(13,HIGH);
  }
}

int desligarRGB(){
  r = 0;
  g = 0;
  b = 0;
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);
}

int modoProgSerial(){
  while(progSerial){
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
      if (comando == "RGB_SET_COLOR A RED"){
        r = 1;
        definirCorRGB(r,g,b);
      }
      if (comando == "RGB_SET_COLOR A GREEN"){
        g = 1;
        definirCorRGB(r, g, b);
      }
      if (comando == "RGB_SET_COLOR A BLUE"){
        b = 1;
        definirCorRGB(r, g, b);
      }
      if (comando == "RGB_OFF"){
        desligarRGB();
      }
      if (comando == "TEMP_READ A"){
        lerTemp();
      }
      if (comando == "LIGHT_READ A"){
        lerLuminosidade();
      }
      if (comando == "FIM_SERIAL"){
         progSerial = 0;
      }
    }
  }
}

//Defininda as chaves
#define ch1 2
#define ch2 3
#define ch3 4
#define ch4 A8
#define chEnter A9
#define chModo A10

//Variaveis a serem testadas
int val1=0, val2=0, val3=0, val4=0, valEnter=0, valModo=0;

int modoProgBinaria(){
  while(valModo){
    // MODO PROG BINARIA
    val1 = digitalRead(ch1);
    val2 = digitalRead(ch2);
    val3 = digitalRead(ch3);
    val4 = digitalRead(ch4);
    valEnter = digitalRead(chEnter);
    valModo = digitalRead(chModo);
    
    if (!val1 && !val2 && !val3 && !val4 && valEnter){ //0000 liga o led verde
      ligarLed('A');
    }
    if (!val1 && !val2 && !val3 && val4 && valEnter){ //0001 desliga o led verde
      desligarLed('A');
    }
    if (!val1 && !val2 && val3 && !val4 && valEnter){ //0010 liga o led azul
      ligarLed('B');
    }
    if (!val1 && !val2 && val3 && val4 && valEnter){ //0011 desliga o led azul
      desligarLed('B');
    }
    if (!val1 && val2 && !val3 && !val4 && valEnter){ //0100 liga o led vermelho
      ligarLed('C');
    }
    if (!val1 && val2 && !val3 && val4 && valEnter){ //0101 desliga o led vermelho
      desligarLed('C');
    }
    if (!val1 && val2 && val3 && !val4 && valEnter){ //0110 liga o buzzer
      ligarBuzzer();
    }
    if (!val1 && val2 && val3 && val4 && valEnter){ //0111 desliga o buzzer
      desligarBuzzer();
    } 
    if (val1 && !val2 && !val3 && !val4 && valEnter){ //1000 liga o led RGB vermelho
      r = 1;
      definirCorRGB(r, g, b);
    }
    if (val1 && !val2 && !val3 && val4 && valEnter){ //1001 liga o led RGB verde
      g = 1;
      definirCorRGB(r, g, b);
    }
    if (val1 && !val2 && val3 && !val4 && valEnter){ //1010 liga o led RGB azul
      b = 1;
      definirCorRGB(r, g, b);
    }
    if (val1 && !val2 && val3 && val4 && valEnter){ //1011 liga o sensor de distância
      lerDistancia();
    }
    if (val1 && val2 && !val3 && !val4 && valEnter){ //1100 liga o sensor de temperatura
      lerTemp();
    }
    if (val1 && val2 && !val3 && val4 && valEnter){ //1101 liga o sensor de luminosidade
      lerLuminosidade();
    }
    if (val1 && val2 && val3 && !val4 && valEnter){ //1110 desliga o led RGB
      progSerial = 1;
      desligarRGB();
    }
    if (val1 && val2 && val3 && val4 && valEnter){ //1110 desliga o led RGB
      progSerial = 1;
      modoProgSerial();
    }
    delay(5000);
  }
}

void setup() {
  pinMode(pinEcho,INPUT);  // define os pinos do Arduíno  
  pinMode(pinTrig,OUTPUT); // Analogamente, o pino Trig de entrada do módulo ultrassônico se conecta com o pino pinTrig de saída do Arduíno
  digitalWrite(pinTrig,LOW);
  // inicializa o pino de Trig e a porta serial
  pinMode(ldr, INPUT); // Define ldr (pino analógico A1) como saída
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(A8,INPUT);
  pinMode(A9,INPUT);
  pinMode(A10,INPUT);
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  modo = Serial.readString();
  if (modo == "MODO_SERIAL"){
    progSerial = 1;
    modoProgSerial();
  } 
  valModo = digitalRead(chModo);
  if (valModo){
    modoProgBinaria();
  }
}
