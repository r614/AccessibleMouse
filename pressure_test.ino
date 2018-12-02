const int analogInPin = A0; // Analog input pin that the Vout Pressure Sensor is attached to
int sensorValue = 0; // value read from the Pressure Sensor

void setup() {
// initialize serial communications at 9600 bps:
Serial.begin(9600);
}

void loop() {
// read the analog in value:
  sensorValue = analogRead(analogInPin);
// convert the reading to voltage
float sensorVoltage = sensorValue * (5.0 / 1023.0);
// convert the reading to it’s PSI equivilant [(Vout = Vs*(0.0018*P+0.04)), (Vs = 5.0Vdc)]
// thus: P= (-V+0.2)/0.009 (kPa)
float kPa = (sensorVoltage – 0.2) / 0.009;
// convert to psi
float PSI = kPa * (0.145037738);

// print the results to the serial monitor:
Serial.print(“Pressure Output Voltage = ” );
Serial.print(sensorVoltage);
Serial.print(” / “);
Serial.print(kPa);
Serial.print(” kPa (“);
Serial.print(PSI);
Serial.println(” PSI)”);

// wait 2 milliseconds before the next loop
// for the analog-to-digital converter to settle
// after the last reading:
delay(2);
}