//global vars
int keySelectorRead = 0;
int programStatus = 0;


//config settings
void setup() {
  
  Serial.begin(9600);
  
  pinMode(3, INPUT); //pressostato
  pinMode(5, OUTPUT); //motor E
  pinMode(6, OUTPUT); //motor D
  pinMode(7, OUTPUT); //bomba flush
  pinMode(8, OUTPUT); //solenoide inundacao
  pinMode(11, OUTPUT); //speaker
  pinMode(12, OUTPUT); //led status - vermelho
  pinMode(13, OUTPUT); //led status - verde
  pinMode(A0, INPUT_PULLUP); //pullup do selector-key
 
  //zera todas saidas
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  
  delay(2000); //aguarda 3 segundos para inicio do programa, evitando repiques da chave seletora
}


//main loop
void loop() {
  
  if(programStatus == 0){
      
      int programSelectorValue = analogRead(0); //leitura key-selector
      
      //MODO 1
      if(programSelectorValue > 63 && programSelectorValue < 69){
          //sequencia 1
          Serial.println("MODO 1");
      }
      //MODO 2
      else if(programSelectorValue > 59 && programSelectorValue < 63){
          Serial.println("MODO 2");
      }
      //MODO 3
      else if(programSelectorValue > 51 && programSelectorValue < 59){
          Serial.println("MODO 3");
      }
      //MODO 4
      else if(programSelectorValue > 45 && programSelectorValue < 51){
          Serial.println("MODO 4");
      }
      //MODO 5
      else if(programSelectorValue > 37 && programSelectorValue < 45){
          Serial.println("MODO 5");
      }
      //MODO 6
      else if(programSelectorValue > 25 && programSelectorValue < 37){
          Serial.println("MODO 6");
      }
      //MODO 7
      else{
          Serial.println("MODO 7");
      }
      
      programStatus = 1;
  }
  
  /*
  while(1){
      int programSelectorValue = analogRead(0); //leitura tensao chave seletora
      
      Serial.println(programSelectorValue/10);
      
      delay(250);
  }*/
  
  /*
  if(programStatus == 0){
    
      Serial.println("### INICIANDO LAVAGEM ###");
    
      Serial.println(">> Inundando o tanque com agua ate o nivel selecionado...");
      tankFlood(); //enche o tanque ate o nivel selecionado
      
      Serial.println(">> Batendo a roupa 4x com intervalos de 3 segundos...");
      wash(4, 2000); //bate a roupa
      
      Serial.println(">> Esvaziando o tanque ate o fim...");
      tankFlush(0); //esvazia o tanque
      
      Serial.println(">> Centrifugando durante 30 segundos...");
      tankCentrifuge(30); //centrifuga a parada
      
      Serial.println(">> Esvaziando o excesso de agua da centrifugacao...");
      tankFlush(15); //retira a agua restante da centrifugacao
      
      programStatus = 1;
      
      digitalWrite(13, HIGH); //acende o led status de verde pra indicar lavagem completa
      
      Serial.println(">> LAVAGEM COMPLETA! Bora beber! =)");
      
      endOfJobMusic(); //fim da festa!
  }*/
  
}


//lavacao
//shakes = batidas de roupa
//interval = intervalo entre batidas (ms)
boolean wash(int shakes, int interval){
  
  for (int i=0; i < shakes; i++){
      digitalWrite(5, HIGH);
      digitalWrite(6, LOW);
      digitalWrite(12, HIGH); //ledstatus
      delay(750);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(12, LOW); //ledstatus
      delay(1000);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(12, HIGH); //ledstatus
      delay(750);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(12, LOW); //ledstatus
      delay(interval);
  }
  
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  digitalWrite(12, LOW); //ledstatus
}

//centrifugar
//pin5 - gira motor direita
//*duration (segundos)
void tankCentrifuge(int duration){
    digitalWrite(5, HIGH);
    
    for (int i=0; i <= duration; i++){
        digitalWrite(12, HIGH);
        delay(500);
        digitalWrite(12, LOW);
        delay(500);
    }
    
    digitalWrite(5, LOW);
}


//esvaziar o tanque
//pin7 - bomba de exaustao
//*duration (segundos)
void tankFlush(int duration){
    
    digitalWrite(7, HIGH);
    
    //se tem duration, usa ele como param
    if(duration == 0){
      for(int i=0; i < duration; i++){
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
      }
    }
    //se o pressostato esta travado, bombeia agua ate destravar
    else{
      //mantem ativo ate o pressostato gritar
      while(!digitalRead(3)){
          digitalWrite(13, HIGH);
          delay(500);
          digitalWrite(13, LOW);
          delay(500);
      }
    }
   
    digitalWrite(7, LOW);
    digitalWrite(13, LOW);
}


//inundar o tanque
//pin8 - solenoide admissao
void tankFlood(){
  
  //mantem ativo ate o pressostato gritar
  while(digitalRead(3)){
      digitalWrite(8, HIGH); //flood valve
      digitalWrite(12, HIGH);//ledstatus
      delay(500);
      digitalWrite(12, LOW);
      delay(500);
  }
  
  digitalWrite(8, LOW); //flood valve
  digitalWrite(12, LOW); //ledstatus
}



//end of job music
//essa porra eh feia pra caralho mas por eqto eh o q tem!
void endOfJobMusic(){
  
  int speakerOut = 11;               
  byte names[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};  
  int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
  byte melody[] = "2d2a1f2c2d2a2d2c2f2d2a2c2d2a1f2c2d2a2a2g2p8p8p8p";
  int count = 0;
  int count2 = 0;
  int count3 = 0;
  int MAX_COUNT = 24;
  int statePin = LOW;
  
  analogWrite(speakerOut, 0);     
  for (count = 0; count < MAX_COUNT; count++) {
    statePin = !statePin;
    
    for (count3 = 0; count3 <= (melody[count*2] - 48) * 30; count3++) {
      for (count2=0;count2<8;count2++) {
        if (names[count2] == melody[count*2 + 1]) {       
          analogWrite(speakerOut,500);
          delayMicroseconds(tones[count2]);
          analogWrite(speakerOut, 0);
          delayMicroseconds(tones[count2]);
        } 
        if (melody[count*2 + 1] == 'p') {
          // make a pause of a certain size
          analogWrite(speakerOut, 0);
          delayMicroseconds(500);
        }
      }
    }
  }
}


void mode7(){

}

