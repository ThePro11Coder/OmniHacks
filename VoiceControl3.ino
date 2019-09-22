#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>


#define echoPin 12
#define trigPin 13
#define IN1  7   //K1、K2 motor direction
#define IN2  8     //K1、K2 motor direction
#define IN3  9    //K3、K4 motor direction
#define IN4  10   //K3、K4 motor direction
#define ENA  5    // Needs to be a PWM pin to be able to control motor speed ENA
#define ENB  6    // Needs to be a PWM pin to be able to control motor speed ENA
String voice;
float duration, distance;
String string, conca;
int x;





/*motor control*/
void go_ahead()  //motor rotate clockwise -->robot go ahead
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4,LOW);
}
void go_back() //motor rotate counterclockwise -->robot go back
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,HIGH); 
}
void go_stop() //motor brake -->robot stop
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,LOW); 
}
void turn_right(int t)  //left motor rotate clockwise and right motor rotate counterclockwise -->robot turn right
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  delay(t);
}
void turn_left(int t) //left motor rotate counterclockwise and right motor rotate clockwise -->robot turn left
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  delay(t);
}
/*set motor speed */
void set_motorspeed(int lspeed,int rspeed) //change motor speed
{
  analogWrite(ENA,lspeed);//lspeed:0-255
  analogWrite(ENB,rspeed);//rspeed:0-255   
}
void setup() {
  /******L298N******/
  Serial.begin(9600);
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT); 
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT); 
  pinMode(ENA, OUTPUT);  
  pinMode(ENB, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  set_motorspeed(170,170);
}
void object_move(){
  distancefunc();
  if (distance <=30 && distance >=2) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,LOW); 
      delay(500);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,LOW); 
      delay(600);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW); 
  }
  
}

void distancefunc() {
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  string = "Obst dist:";
  conca = string + distance;
// for (x = 0; x<=3; x++){
    Serial.println(distance);
    if (distance <=30) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4,LOW); 
    }
    else {
//      serial.println("No obstacle found");
    }

//}
}
void loop() {
    go_ahead();
    Serial.println("In object move\n");
    object_move();
while(Serial.available()>0)
  {
    delay(10);
    char c=Serial.read();
    if(c=='#')
    {
      break;
    }
    voice+=c;
    }
   if(voice=="back"){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
     delay(5000);
    }
  else
    if(voice=="forward"){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);  
   object_move();
    }
  else
   if(voice=="left"){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(200); 
    }
  else
   if(voice=="right"){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(200);   }
   if(voice.length()>0)
    {
      Serial.println(voice);
       voice="";
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
    }
//    object_move();
  digitalWrite(trigPin, LOW);
//    object_move();
  delayMicroseconds(2);
//    object_move();
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
//    object_move();
  digitalWrite(trigPin, LOW);
//  object_move();
//  distance_func();
  
}
