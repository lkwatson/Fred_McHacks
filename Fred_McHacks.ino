#include <Servo.h>

Servo mouth;
Servo l_eye;
Servo r_eye;

int m_pos = -1;
int l_pos = -1;
int r_pos = -1;

int inByte = 0;

void moveit(Servo *servo, int *pos, int newpos) {
  if(*pos == -1) {
    (*servo).write(newpos);
  }else{
    while(*pos != newpos) {
      if(newpos > *pos) {
        *pos = *pos + 1;
      }else{
        *pos = *pos - 1;
      }
      delay(15);
      (*servo).write(*pos);
    }
  }
}

void setup() {
  Serial.begin(9600);
  
  mouth.attach(9);
  l_eye.attach(8);
  r_eye.attach(10);

  //mouth.write(180);
  moveit(&mouth, &m_pos, 180);
  delay(1000);
  //l_eye.write(20);
  moveit(&l_eye, &l_pos, 25);
  delay(200);
  //r_eye.write(100);
  moveit(&r_eye, &r_pos, 95);
  delay(100);

  m_pos = 180;
  l_pos = 20;
  r_pos = 100;
}

void happy() {
  moveit(&mouth, &m_pos, 0);
  moveit(&l_eye, &l_pos, 25);
  moveit(&r_eye, &r_pos, 95);
}

void angry() {
  moveit(&mouth, &m_pos, 180);
  moveit(&l_eye, &l_pos, 0);
  moveit(&r_eye, &r_pos, 120);
}

void sad() {
  moveit(&mouth, &m_pos, 180);
  moveit(&l_eye, &l_pos, 40);
  moveit(&r_eye, &r_pos, 80);
}

void evil() {
  moveit(&mouth, &m_pos, 1);
  moveit(&l_eye, &l_pos, 0);
  moveit(&r_eye, &r_pos, 120);
}

void loop()
{
  if (Serial.available() > 0) {
    inByte = Serial.read();
    Serial.print("Received: ");
    Serial.println(inByte, DEC);

    if(inByte == 97 || inByte == 0) {
      happy();
    }
    if(inByte == 115 || inByte == 1) {
      angry();
    }
    if(inByte == 100 || inByte == 2) {
      sad();
    }
    if(inByte == 102 || inByte == 3) {
      evil();
    }
  }
}

