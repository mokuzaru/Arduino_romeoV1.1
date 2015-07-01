//Primero declarar las variables de entrada de los motores.
#include <Servo.h>

Servo codo_der;
Servo codo_izq;
Servo hombro_der;
Servo hombro_izq;
Servo cuello_si;

int E1 = 5;
int E2 = 6;
int M1 = 4;
int M2 = 7;

int digPin = 13;
int digPin2 = 12;

int vel=250;    //velocidad de los motores (0- 255)
int estado = 'x'; //estado inicial

int pecho = 2;
int ptrig = 3;
int duracion, distancia;

void stop(void){
  digitalWrite(E1,LOW);
  digitalWrite(E2,LOW); 
}
void advance(int vel){
 analogWrite(E1,vel);
 digitalWrite(M1, HIGH);
 analogWrite(E2,vel);
 digitalWrite(M2,HIGH);
}
void back_off(int vel){
  analogWrite(E1,vel);
  digitalWrite(M1,LOW);
  analogWrite(E2,vel);
  digitalWrite(M2,LOW);
}
void turn_L (int vel){
  analogWrite(E1,vel);
  digitalWrite(M1, LOW);
  analogWrite(E2,vel);
  digitalWrite(M2, HIGH); 
}
void turn_R (int vel){
  analogWrite(E1, vel);
  digitalWrite(M1, HIGH);
  analogWrite(E2, vel);
  digitalWrite(M2, LOW);
}
void sensar(int vel){
  
  digitalWrite(ptrig, HIGH);
  delay(0.01);
  digitalWrite(ptrig,LOW);
  
  duracion = pulseIn(pecho, HIGH);
  distancia = (duracion/2)/29;
  delay(10);
  
  if(distancia <= 20 && distancia >= 2){
   digitalWrite(8, HIGH);
  
   stop();
   delay(200);
  
   turn_R(vel*0.7);
   delay(500);
  
   advance(vel*0.8);
   delay(1100);
  
   digitalWrite(8, LOW); 
    
  }else
  turn_L(vel*0.7);
}

void moveser(void){
        
        hombro_der.write(90); 
        hombro_izq.write(90);
        cuello_si.write(00); 
        codo_der.write(180);
        codo_izq.write(00);
        delay(250);
        cuello_si.write(90);
        delay(250);
        cuello_si.write(00);      
        hombro_der.write(90); 
        hombro_izq.write(90);       
        delay(250); 
        hombro_der.write(180);
        hombro_izq.write(00);
        delay(250);
        codo_der.write(90);
        codo_izq.write(90);
        delay(250);
        codo_der.write(180);
        codo_izq.write(00);
        delay(250);
        hombro_der.write(90); 
        hombro_izq.write(90);
        cuello_si.write(00); 
        codo_der.write(180);
        codo_izq.write(00);
}

void setup() {
  int i;
  for (i=3;i<=7;i++)
    pinMode(i, OUTPUT);
  
  codo_der.attach(11,600,1500);   
  codo_izq.attach (10,600,1500);
  hombro_der.attach(9,600,1500);
  hombro_izq.attach(12,600,1500);
  cuello_si.attach(13,600,1500);
  
    
  Serial.begin(9600);
  pinMode(pecho, INPUT);
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(12, OUTPUT);
  
  hombro_der.write(90); 
  hombro_izq.write(90);
  cuello_si.write(00); 
  codo_der.write(180);
  codo_izq.write(00);
}

void pwm(int i){
  
  digitalWrite( i, HIGH);
  delay(500);
  digitalWrite(i,LOW);
  delay(500);
}

void loop() {
  if(Serial.available()>0){   //lee el bluetooth y almacena en estado
    /*if (Serial.read() >=10 &&Serial.read()<=254){
      vel = Serial.read();
    }else{*/
    estado = Serial.read();
    if (estado != -1){
     switch(estado) {
       case 'a':
         advance(vel);
         break;
       case 'b':
         back_off(vel);
         break;
       case 'l':
          turn_L(vel/2);
          break;
       case 'r':
           turn_R(vel/2);
           break;
       case 's':
           Serial.println ("holi soy autonomo");
           sensar(vel);
           break;
       case 'x':
           stop();
           break;
       case 'M':
          pwm(digPin);
          pwm(digPin2);
           moveser();
           break;
     }
    }else
    stop();
  }
  //}
  
  
}
