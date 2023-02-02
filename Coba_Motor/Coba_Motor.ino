#define enA 5
#define in1 2
#define in2 3
#define enB 6
#define in3 4 
#define in4 7
int motorSpeedA = 0;
int motorSpeedB = 0;


void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}


void loop() {
    motorSpeedA = 105; 
    motorSpeedB = 103; 
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
    // Set Motor A Maju
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    // Set Motor B Maju
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(6000);
    // Set Motor A Stop
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // Set Motor B Stop
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(3000);
    // Set Motor A Mundur
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    // Set Motor B Mundur
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(6000);
    //Set Motor A Stop
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // Set Motor B Stop
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(3000);
    
}
