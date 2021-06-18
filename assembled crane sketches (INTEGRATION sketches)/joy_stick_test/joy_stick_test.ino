
int x = A1;
int y = A2;

void setup() {

  Serial.begin(115200);
  pinMode(x, INPUT);
  pinMode(y, INPUT);
  

}

void loop() {

  Serial.print("X: "); Serial.print(map(analogRead(x), 0, 1023, 0, 180)); Serial.print(" Y: "); Serial.println(map(analogRead(y), 0, 1023, 0, 90));

}
