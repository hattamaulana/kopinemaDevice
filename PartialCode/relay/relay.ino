int RELAY1 = A0;
int RELAY2 = A1;
int delayValue = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);

  digitalWrite(RELAY1, HIGH);
  digitalWrite(RELAY2, HIGH);

  Serial.begin(9600);
}

void loop() {
  
  // put your main code here, to run repeatedly:
  digitalWrite(RELAY1, LOW);
  Serial.println("RELAY1 ON");
  delay(delayValue);
 
  digitalWrite(RELAY1, HIGH);
  Serial.println("RELAY1 OFF");

  digitalWrite(RELAY2, LOW);
  Serial.println("RELAY2 ON");
  delay(delayValue);
  
  digitalWrite(RELAY2, HIGH);
  Serial.println("RELAY2 OFF");
}