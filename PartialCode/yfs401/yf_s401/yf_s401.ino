byte indikator = 13;

byte sensorInt = 0;
byte flowSensor = 4;

float KONSTANTA = 4.5; //flow-meter const

volatile byte pulseCount;

float debit;
unsigned int flowMlt;
unsigned long totalMlt;
unsigned long oldTime;

void setup(){
  Serial.begin(9600);
  pinMode(indikator, OUTPUT);
  digitalWrite(indikator, HIGH);

  pinMode(indikator, INPUT);
  digitalWrite(indikator, HIGH);

  pulseCount = 0;
  debit = 0.0;
  flowMlt = 0;
  totalMlt = 0;
  oldTime = 0;

  attachInterrupt(sensorInt, pulseCounter, FALLING);
}

void loop(){
  if((millis() - oldTime) > 1000){
    detachInterrupt(sensorInt);
    debit = ((1000.0 / (millis() - oldTime)) * pulseCount) / KONSTANTA;
    oldTime = millis();
    flowMlt = (debit / 60) * 1000;
    totalMlt = totalMlt + flowMlt;

    unsigned int frac;

    Serial.print("Debit air: "); Serial.print(int(debit)); Serial.print("L/min");
    Serial.print("\tVolume"); Serial.print(totalMlt); Serial.println("mL");

    pulseCount = 0;

    attachInterrupt(sensorInt, pulseCounter, FALLING);
  }
}

void pulseCounter(){
  pulseCount++;
}
