  int vSpeed = 50;        // MAX 255
  int turn_speed = 50;    // MAX 255 
  int turn_delay = 10;
  //Lights 
  int LDR = A2;
  int led = 7;
 //Ultra sonic 
  int echo = 4;
  int triger = 5;
  long tt;
  int distance;
 //L293 Connection   
   int motorA1      = 8;  //in1
   int motorA2      = 10; //in2
   int motorAspeed  = 9;  //enA
   int motorB1      = 12; //in3
   int motorB2      = 13; //in4
   int motorBspeed  = 11; //enB
 //Sensor Connection
   int left_sensor_pin =A0;
   int right_sensor_pin =A1;
  
  int left_sensor_state;
  int right_sensor_state;
  void move_right(){
  digitalWrite (motorA1,LOW); 
  digitalWrite (motorA2,HIGH);                       
  digitalWrite (motorB1,HIGH);
  digitalWrite (motorB2,LOW);
  }
  void move_left(){
  digitalWrite (motorA1,HIGH);
  digitalWrite (motorA2,LOW);                       
  digitalWrite (motorB1,LOW);
  digitalWrite (motorB2,HIGH);
  }
  void move_forward(){
  digitalWrite (motorA1,HIGH);
  digitalWrite (motorA2,LOW);                       
  digitalWrite (motorB1,HIGH);
  digitalWrite (motorB2,LOW);
  }
  void move_stop(){
  digitalWrite (motorA1,LOW);
  digitalWrite (motorA2,LOW);                       
  digitalWrite (motorB1,LOW);
  digitalWrite (motorB2,LOW);
  }

 void setup() {
  pinMode(LDR,INPUT);
  pinMode(led,OUTPUT);
  pinMode(triger,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  Serial.begin(9600);
  delay(3000);
}

 void loop() {
  if (analogRead(LDR)<200){
    digitalWrite(led,HIGH);
    }
 digitalWrite(triger,LOW);
 delayMicroseconds(2);
 digitalWrite(triger,HIGH);
 delayMicroseconds(10);
 digitalWrite(triger,LOW);
 tt = pulseIn(echo,HIGH);
 distance = tt*.034/2; // distance in cm

 left_sensor_state = analogRead(left_sensor_pin);
 right_sensor_state = analogRead(right_sensor_pin);
 //Serial.println(left_sensor_state);
 //Serial.println(right_sensor_state);
 if(distance < 15){
  move_stop();
  Serial.print(distance);
  Serial.print(" ");
  Serial.println("Move Stop Active");
 }
  else{

 if(right_sensor_state < 500 && left_sensor_state > 500)
 {
  Serial.println("turning right");
  move_right();
  analogWrite (motorAspeed, vSpeed);
  analogWrite (motorBspeed, turn_speed);
  }
 if(right_sensor_state > 500 && left_sensor_state < 500)
 {
  Serial.println("turning left");
  move_left();
  analogWrite (motorAspeed, turn_speed);
  analogWrite (motorBspeed, vSpeed);
  delay(turn_delay);
  }

 if(right_sensor_state < 500 && left_sensor_state < 500)
 {
  Serial.println("going forward");
  move_forward();
  analogWrite (motorAspeed,vSpeed);
  analogWrite (motorBspeed,vSpeed);
  }
 if(right_sensor_state > 500 && left_sensor_state > 500)
 { 
  Serial.println("stop");
  analogWrite (motorAspeed, 0);
  analogWrite (motorBspeed, 0);
  }
  }
}










 
