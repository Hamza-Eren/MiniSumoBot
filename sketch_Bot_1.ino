// Başlatzade
#define BASLAT 2

// IR (Kızılötesi)
#define IR_SOL A4
#define IR_ON A2
#define IR_SAG A0

// QTR
#define QTR_SOL A3
#define QTR_SAG A1

// Switch
#define SW_1 12
#define SW_2 8
#define SW_3 7

// Sol motor
#define in3Pin 11
#define in4Pin 3

// Sağ motor
#define in1Pin 10
#define in2Pin 9

int sol_qtr, sag_qtr, sol_ir, on_ir, sag_ir, mode, turnDuration, bz;
int enemyProximity = 0;
int power = 60;

int search_status = 0;
bool switch_status = true;

void setup() {
  Serial.begin(9600);

  pinMode(BASLAT, INPUT);
  pinMode(IR_SOL, INPUT);
  pinMode(IR_ON, INPUT);
  pinMode(IR_SAG, INPUT);
  pinMode(QTR_SOL, INPUT);
  pinMode(QTR_SAG, INPUT);
  pinMode(SW_1, INPUT_PULLUP);
  pinMode(SW_2, INPUT_PULLUP);
  pinMode(SW_3, INPUT_PULLUP);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
  pinMode(in3Pin, OUTPUT);
  pinMode(in4Pin, OUTPUT);
}

void loop() {
  do {
    bz = digitalRead(BASLAT);
  } while(bz);

  if (digitalRead(SW_1)) {
    moveLeft(90);
    delay(100);
    moveForward(50);
  }

  if (digitalRead(SW_2)) {
    moveLeft(130);
    delay(100);
    moveForward(50);
    moveForward(50);
  }

  if (digitalRead(SW_3)) {
    moveRight(90);
    delay(100);
    moveForward(50);
  }

  while (true) {
    sol_ir = analogRead(IR_SOL);
    on_ir = analogRead(IR_ON);
    sag_ir = analogRead(IR_SAG);
  
    if (on_ir > 400) {
      moveForward(power);
      enemyProximity += 1;
      if (enemyProximity > 7) {
        power = 255;
      } else if (enemyProximity > 4) {
        power = 150;
      }
    } else if (sol_ir > 400) {
      enemyProximity = 0;
      power = 60;
      stopMoving();
      moveLeftToTarget();
    } else if (sag_ir > 400) {
      enemyProximity = 0;
      power = 60;
      stopMoving();
      moveRightToTarget();
    } else {
      enemyProximity = 0;
      if (power > 60) {
        stopMoving();
        delay(500);
      }
      power = 35;
      searchAround();
    }
  
    delay(300);
  }
}
