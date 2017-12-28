//http://tet.pub.ro/materiale/altele/Documentatie/Shield%20Driver%20de%20Motoare%20Dual%20L298P%20SMD%20cu%20Buzzer/091035_L298P-Motor-Shield-Instruction.pdf
// This is test code found from above

int E1=10;
int M1=12;
int E2=11;
int M2=13;

void setup(){
  pinMode(M1,OUTPUT);
  pinMode(M2,OUTPUT);
  }
  
  void loop(){
    
      for(int value=0;value<=255;value+=5)
      { 
        digitalWrite(M1,HIGH);
        digitalWrite(M2,HIGH);
        analogWrite(E1,value);
        analogWrite(E2,value);
        delay(30);
        }
        delay(1000);
        
        
         for(int value=0;value<=255;value+=5){
          digitalWrite(M1,LOW);
          digitalWrite(M2,LOW);
          analogWrite(E1,value);
          analogWrite(E2,value);
          delay(30);}
          delay(1000);
          }
         
