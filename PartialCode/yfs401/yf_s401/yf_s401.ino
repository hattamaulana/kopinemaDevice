byte indikator = 13;
byte sensorInt = 0;
byte flowsensor = A0;

float KONSTANTA = 4.5;

volatile byte pulseCount;

float debit;
unsigned int flowmlt;
unsigned long totalmlt;
unsigned long oldtime;

void setup(){
    Serial.begin(9600);
    
    pinMode(indikator, OUTPUT);
    digitalWrite(indikator, HIGH);

    pinMode(flowsensor, INPUT);
    digitalWrite(flowsensor, HIGH);

    // FlowSensor Variable
    pulseCount = 0; debit = 0.0; flowmlt = 0;
    totalmlt = 0; oldtime = 0;

    attachInterrupt(sensorInt, pulseCount, FALLING);
}

void loop(){
    if ((millis() - oldtime) > 1000){
        detachInterrupt(sensorInt);
        debit = ((1000.0 / (millis() - oldtime)) * pulseCount) / KONSTANTA;
        oldtime = millis();
        flowmlt = (debit / 60) * 1000;
        totalmlt += flowmlt;
        
        unsigned int frac;

        Serial.print("Debit air: ");
        Serial.print(int(debit));
        Serial.print("L/min");
        Serial.print("\t");

        Serial.print("Volume: "); 
        Serial.print(totalmlt);
        Serial.println("mL"); 
        
        pulseCount = 0;
        attachInterrupt(sensorInt, pulseCounter, FALLING);
    }
}

void pulseCounter(){
    // Increment the pulse counter
    pulseCount++;
}
