// mendeskripsikan pin us di tengah 
const int trigPin1 = 11;
const int echoPin1 = 10;

// mendeskripsikan pin us di pojok kiri
const int trigPin2 = A3;
const int echoPin2 = A4;

// mendeskripsikan pin us di pojok kanan
const int trigPin3 = A2;
const int echoPin3 = A5;

// Pin Motor kiri
const int enA = 5;
const int in1 = 2;
const int in2 = 3;

// Pin Motor kanan
const int enB = 6;
const int in3 = 4; 
const int in4 = 7;

#define PWM 100
#define DIS 15

void setup() {
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop() {
  if(FrontSensor() < DIS && RightSensor() < DIS && LeftSensor() < DIS)

  {

    turn_right();
    delay(3000);
  }

  else if(FrontSensor() < DIS && RightSensor() < DIS && LeftSensor() > DIS)

  {
    turn_left();
  }

  else if (FrontSensor() < DIS && RightSensor() > DIS && LeftSensor() < DIS)
  {
    turn_right();
  }
  else if (FrontSensor() < DIS && RightSensor() > DIS && LeftSensor() > DIS)
  {
    turn_right();
  }

  else if (FrontSensor() > DIS && RightSensor() > DIS && LeftSensor() < DIS)
  {
    turn_right();
    delay(180);
    forward();
  }

  else if (FrontSensor() > DIS && RightSensor() < DIS && LeftSensor() > DIS)
  {
    turn_left();
    delay(180);
    forward();
  }
  
  else

  {
    forward();
  }
}

void forward() {
  analogWrite(enA, PWM);
  analogWrite(enB, PWM);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turn_left() {
  analogWrite(enA, PWM);
  analogWrite(enB, PWM);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
   
}

void turn_right() {
  analogWrite(enA, PWM);
  analogWrite(enB, PWM);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
}

void reverse() {
  analogWrite(enA, PWM);
  analogWrite(enB, PWM);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void srtop() {
  analogWrite(enA, LOW);
  analogWrite(enB, LOW);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

long FrontSensor()
{
  long dur;
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin1, LOW);
  dur = pulseIn(echoPin1, HIGH);
  return(dur/30);
}
long RightSensor()
{
  long dur;
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin2, LOW);
  dur = pulseIn(echoPin2, HIGH);
  return(dur/62);
}
long LeftSensor()
{
  long dur;
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin3, LOW);
  dur = pulseIn(echoPin3, HIGH);
  return(dur/50);
}
