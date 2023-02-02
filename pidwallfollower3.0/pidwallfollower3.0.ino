#define SENSOR_MAX 
#define DIST_PROPORTIONAL_CONST 0.034/2 //DEPENDS ON ENVIRONMENT AND SPEED OF SOUND
#define INPUT_DISTANCE 15 //in cm
#define ERROR_DIST 5  // in cm
#define SPEED 255
#define MAX_SENSOR_VALUE 10000
#define MAX_OF_SENSOR 3000
#define MAX_DIFFERNCE 10
#define MAX_TURN_SPEED 10
#define CALIBRATION 3
#define MAX_ALLIGN_ANGLE 5
#define COLLISION_DISTANCE 10

//sensor 1 Kiri 
const int trigPin1 = A2;
const int echoPin1 = A5;

//sensor 2 Kanan
const int trigPin2 = A3;
const int echoPin2 = A4;

//sensor 3 Tengah
const int trigPin3 = 11;
const int echoPin3 = 10;

//Motor Kanan(Right)
const int in1R = 4;
const int in2R = 7;
const int enR = 6;

//Motor Kiri(Left)
const int in1L = 2;
const int in2L = 3;
const int enL = 5;

//pid
float kp_a = 1;
float kd_a = 0;
//Paramater
float kp_d = 1;
float kd_d = 0;
float ki_d = 0;
//Jarak (distance)
float errorD;
float previousErrorD = 0;
float dt = 0.1;

// deklarasi jarak , integral, angle
float distance1, distance2, currentDistance, integral, derivative, outputD, outputA, angle, previousAngle=0.0, allign_angle=0.0;

// deklarasi area, jarak PID, kecepatan kanan dan kiri, dan jarak
int region, pidDist, speedL, speedR, distance;

//Pembacaan Sensor
float sensor_output(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

float duration = pulseIn(echoPin, HIGH);
//  Serial.print("duration:");
//  Serial.println(duration);
  if(duration==0.0||duration>=MAX_SENSOR_VALUE){
    duration = MAX_OF_SENSOR;
    }
    

  float distance = duration*DIST_PROPORTIONAL_CONST;
   
  return distance; 
}

/////////// Menghitung Jarak Dari Dinding (wall)/////////////////////

float current_distance(float read1, float read2){
  float distance = (read1 + read2)/2;  //taking average of two values

  return distance;
  }


///////// Harus Berputar Kemana///////////////////////
int check_region(float read1, float read2){
  distance = current_distance(read1, read2);
  if(abs(distance-INPUT_DISTANCE)>ERROR_DIST){
    if(distance > INPUT_DISTANCE){
        return -1; //untuk gerak ke kiri
      }else{
        return 1; //untuk gerak ke kanan
        }
    }else{
      return 0; //masih dalam wilayah mereturn
      }
  }

//fungsi untuk mengarahkan robot ke tujuan yang ingin dicapai
void reach_distance(){
  distance1 = sensor_output(trigPin1, echoPin1);
  distance2 = sensor_output(trigPin2, echoPin2);
  currentDistance = current_distance(distance1, distance2);
  errorD = currentDistance - INPUT_DISTANCE;
  derivative = errorD - previousErrorD;
  integral += errorD;
  outputD = kp_d*errorD + ki_d*integral*dt + kd_d*derivative;
  previousErrorD = errorD;
  speedL = SPEED - (int)outputD;
  speedR = SPEED + (int)outputD;
  //right turn 
  if((speedL-speedR)>MAX_DIFFERNCE){
    speedL = SPEED + MAX_DIFFERNCE;
    speedR = SPEED - MAX_DIFFERNCE;
  }else if((speedL-speedR)<(-1)*MAX_DIFFERNCE){
    speedL = SPEED - MAX_DIFFERNCE;
    speedR = SPEED + MAX_DIFFERNCE;
    }
   analogWrite(enL, speedL);
   analogWrite(enR, speedR);
   digitalWrite(in1L, HIGH);
    digitalWrite(in2L, LOW);
    digitalWrite(in1R, HIGH);
    digitalWrite(in2R, LOW);
  
  }

/////////Supaya Robot Stabil Dengan Dindidng///////////////////

void follow_wall(){
  distance1 = sensor_output(trigPin1, echoPin1);
  distance2 = sensor_output(trigPin2, echoPin2);
  float angle = distance2-distance1;//if +ve turn left else turn right
  float derivativeA = angle - previousAngle;
  outputA = kp_a*angle + kd_a*derivativeA;
  previousAngle = angle;
  speedL = SPEED + CALIBRATION - outputA;
  speedR = SPEED + outputA;
  if((speedL-speedR)>MAX_TURN_SPEED){
    speedL = SPEED + CALIBRATION + MAX_TURN_SPEED;
    speedR = SPEED - MAX_TURN_SPEED;
    }else if((speedL-speedR)>MAX_TURN_SPEED){
      speedL = SPEED + CALIBRATION - MAX_TURN_SPEED;
      speedR = SPEED + MAX_TURN_SPEED;
      }
  analogWrite(enL, speedL);
  analogWrite(enR, speedR);
  digitalWrite(in1L, HIGH);
  digitalWrite(in2L, LOW);
    digitalWrite(in1R, HIGH);
    digitalWrite(in2R, LOW);
  
  }

bool check_collision(){
  int distance3 = sensor_output(trigPin3, echoPin3);
  if(distance3<COLLISION_DISTANCE){
    return true;
  }else{
    return false;
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(in1L,OUTPUT);
  pinMode(in2L,OUTPUT);
  pinMode(in1R,OUTPUT);
  pinMode(in2R,OUTPUT);
  pinMode(enL,OUTPUT);
  pinMode(enR,OUTPUT);                          
  
  pinMode(trigPin1,OUTPUT);
  pinMode(echoPin1,INPUT);
  pinMode(trigPin2,OUTPUT);
  pinMode(echoPin2,INPUT);

  digitalWrite(enL, LOW);
  digitalWrite(enR, LOW);
}

void loop() {
  distance1 = sensor_output(trigPin1, echoPin1);
  distance2 = sensor_output(trigPin2, echoPin2);
  region = check_region(distance1, distance2);
  allign_angle = abs(distance2 - distance1);
//  Serial.print("distance1:");
//  Serial.println(distance1);
  Serial.print("distance2:");
  Serial.println(distance2);
//  Serial.print("region:");
//  Serial.println(region);
  if(check_collision()){
    //turn right
    speedL = speedL + MAX_DIFFERNCE;
    speedR = speedR - MAX_DIFFERNCE;
    analogWrite(enL, speedL);
    analogWrite(enR, speedR);
    digitalWrite(in1L, HIGH);
    digitalWrite(in2L, LOW);
    digitalWrite(in1R, HIGH);
    digitalWrite(in2R, LOW);
  }else{
    if(region==0){
    follow_wall();
    }
   else{
    if(allign_angle>MAX_ALLIGN_ANGLE){
      follow_wall();
      }else{
        reach_distance();
      }
    
    }

  }
  
}
