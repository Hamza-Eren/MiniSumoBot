// İleri hareket ettiren fonksiyon
void moveForward(int power) {
  analogWrite(in1Pin, power);
  analogWrite(in2Pin, 0);
  analogWrite(in3Pin, power);
  analogWrite(in4Pin, 0);
  delay(100);

  stopMoving();
}

// Geri hareket etmesi için fonksiyon
void moveBackward() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, HIGH);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, HIGH);
  delay(1000);

  stopMoving();
}

// Belirli bir derece sola döndüren fonksiyon
void moveLeft(int degrees) {
  if (degrees == 0) {
    turnDuration = 300;
  } else {
    turnDuration = (int)((float)degrees / 90.0 * 30.0);
  }
  analogWrite(in1Pin, 255);
  analogWrite(in2Pin, 0);
  analogWrite(in3Pin, 0);
  analogWrite(in4Pin, 255);
  delay(turnDuration);

  stopMoving();
}

/*void moveLeftToTarget(){
  int i = 0;
  do {
    on_ir = analogRead(IR_ON);
    analogWrite(in1Pin, 30);
    analogWrite(in2Pin, 0);
    analogWrite(in3Pin, 0);
    analogWrite(in4Pin, 30);
    i += 1;
    delay(100);
  } while (on_ir < 400 && i < 20 );

  stopMoving();
}*/

void moveLeftToTarget(){
  int i = 0;
  do {
    on_ir = analogRead(IR_ON);
    analogWrite(in1Pin, 35);
    analogWrite(in2Pin, 0);
    analogWrite(in3Pin, 0);
    analogWrite(in4Pin, 35);
    i += 1;
    delay(100);
  } while (on_ir < 400 && i < 10);

  stopMoving();
}

void moveLeftForSearch(int degrees) {
  if (degrees == 0) {
    turnDuration = 300;
  } else {
    turnDuration = (int)((float)degrees / 90.0 * 30.0);
  }
  
  /*analogWrite(in1Pin, 55);
  analogWrite(in2Pin, 0);
  analogWrite(in3Pin, 0);
  analogWrite(in4Pin, 55);
  delay(turnDuration);*/

  int i = 0;
  do {
    sol_ir = analogRead(IR_SOL);
    on_ir = analogRead(IR_ON);
    sag_ir = analogRead(IR_SAG);
    
    analogWrite(in1Pin, 60);
    analogWrite(in2Pin, 0);
    analogWrite(in3Pin, 0);
    analogWrite(in4Pin, 60);
    delay(100);
    i += 1;
  } while (!(i < (turnDuration/10) || (sol_ir != 0 || on_ir != 0 || sag_ir != 0 )));

  stopMoving();
}

// Belirli bir derece sağa döndüren fonksiyon
void moveRight(int degrees) {
  if (degrees == 0) {
    turnDuration = 300;
  } else {
    turnDuration = (int)((float)degrees / 90.0 * 30.0);
  }
  
  analogWrite(in1Pin, 0);
  analogWrite(in2Pin, 255);
  analogWrite(in3Pin, 255);
  analogWrite(in4Pin, 0);
  delay(turnDuration);

  stopMoving();
}

void moveRightToTarget(){
  int i = 0;
  do {
    on_ir = analogRead(IR_ON);
    analogWrite(in1Pin, 0);
    analogWrite(in2Pin, 40);
    analogWrite(in3Pin, 40);
    analogWrite(in4Pin, 0);
    i += 1;
    delay(100);
  } while (on_ir < 400 && i < 10);

  stopMoving();
}

// Botu durduran fonksiyon
void stopMoving() {
  digitalWrite(in1Pin, LOW);
  digitalWrite(in2Pin, LOW);
  digitalWrite(in3Pin, LOW);
  digitalWrite(in4Pin, LOW);
}

void searchAround() {
  int angle = 60;
  do {
    sol_ir = analogRead(IR_SOL);
    on_ir = analogRead(IR_ON);
    sag_ir = analogRead(IR_SAG);

    //moveForward(40);
    moveLeftForSearch(angle);
  } while (!(sol_ir != 0 || on_ir != 0 || sag_ir != 0 ));
}
