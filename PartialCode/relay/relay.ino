int rHeater = 7;
int rPump = 8;
int delayValue = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(rHeater, OUTPUT);
  pinMode(rPump, OUTPUT);

  digitalWrite(rHeater, HIGH);
  digitalWrite(rPump, HIGH);

  Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  digitalWrite(rHeater, LOW);
 
  digitalWrite(rHeater, HIGH);

  digitalWrite(rPump, LOW);
  
  digitalWrite(rPump, HIGH);
}
