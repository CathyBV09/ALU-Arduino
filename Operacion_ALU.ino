int W = 0;
int X = 0;
int Y = 0;
int Z = 0;
int A = 0;
int B = 0;

void setup() {
  pinMode(2, INPUT);  // W
  pinMode(3, INPUT);  // X
  pinMode(4, INPUT);  // Y
  pinMode(5, INPUT);  // Z
  pinMode(6, INPUT);  // A
  pinMode(7, INPUT);  // B

  pinMode(9, OUTPUT);  // Resultado
  pinMode(10, OUTPUT); // Acarreo/Error

  Serial.begin(9600);
}

void loop() {
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);

  W = digitalRead(2);
  X = digitalRead(3);
  Y = digitalRead(4);
  Z = digitalRead(5);
  A = digitalRead(6);
  B = digitalRead(7);

  // Suma → 0000
  if (!W && !X && !Y && !Z) {
    if (A ^ B) digitalWrite(9, HIGH);
    if (A & B) digitalWrite(10, HIGH);
  }

  // Resta → 0001
  if (!W && !X && !Y && Z) {
    if (A ^ B) digitalWrite(9, HIGH);
    if (!A && B) digitalWrite(10, HIGH);
  }

  // Multiplicación → 0010
  if (!W && !X && Y && !Z) {
    if (A & B) digitalWrite(9, HIGH);
  }

  // División → 0011
  if (!W && !X && Y && Z) {
    if (B == 0) {
      digitalWrite(10, HIGH);  // Error
    } else {
      if (A) digitalWrite(9, HIGH);  // 1/1 o 1/any = 1
    }
  }

  // AND → 0100
  if (!W && X && !Y && !Z) {
    digitalWrite(9, A & B);
  }

  // XOR → 0101
  if (!W && X && !Y && Z) {
    digitalWrite(9, A ^ B);
  }

  // OR → 0110
  if (!W && X && Y && !Z) {
    digitalWrite(9, A | B);
  }

  // XNOR (nueva) → 0111
  if (!W && X && Y && Z) {
    digitalWrite(9, !(A ^ B));
  }

  // Serial Monitor
  Serial.print("A: "); Serial.print(A);
  Serial.print(" B: "); Serial.print(B);
  Serial.print(" | WXYZ: "); Serial.print(W); Serial.print(X); Serial.print(Y); Serial.print(Z);
  Serial.print(" | Resultado: "); Serial.print(digitalRead(9));
  Serial.print(" | Acarreo/Error: "); Serial.println(digitalRead(10));

  delay(300);
}
