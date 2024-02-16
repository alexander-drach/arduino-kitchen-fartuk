
#include <GyverStepper.h>
#include "GyverButton.h"

GButton stopDownSensor(2);
GButton slowDownSpeed(3);

GButton slowUpSpeed(4);
GButton stopUpSensor(5);

GButton hand(6);

GButton moveUp(7);
GButton moveDown(8);

GStepper<STEPPER2WIRE> stepper(200, 11, 10);

int speed = 800;

bool flag = false;

void setup() {
  Serial.begin(9600);

  stepper.setRunMode(KEEP_SPEED);
  stepper.setMaxSpeed(1500);
}

void loop() {

  stopDownSensor.tick();
  slowDownSpeed.tick();

  slowUpSpeed.tick();
  stopUpSensor.tick();

  hand.tick();

  moveUp.tick();
  moveDown.tick();

  stepper.tick();

  if (hand.isPress()) {
    Serial.println("hand sunul ruku STOP"); // проверка на руку
    stepper.brake();
    flag = false;
  }

  if (moveUp.isPress()) {
    Serial.println("moveUp"); // движение фартука вверх    

    if (flag) {
      stepper.stop();
      flag = false;
    } else {
      stepper.setSpeed(speed);
      flag = true;
    }

    if (stopUpSensor.isHold()) {
      stepper.brake();
      flag = false;
    }   
  }

  if (moveDown.isPress()) { // движение фартука вниз
    Serial.println("moveDown");
    
    if (flag) {
      stepper.stop();
      flag = false;
    } else {
      stepper.setSpeed(-speed);
      flag = true;
    };

    if (stopDownSensor.isHold()) {
      stepper.brake();
      flag = false;
    }
  }

  if (stopDownSensor.isPress()) {// остановка фартука внизу ДАТЧИК - 0
    stepper.brake();
    Serial.println("stopDownSensor");
    flag = false;
  }

  if (slowDownSpeed.isPress()) { // замедление скорости внизу ДАТЧИК - 1  
    stepper.setSpeed(200);
    Serial.println("slowDownSpeed");
  }  

  if (slowUpSpeed.isPress()) { // замедление скорости вверху ДАТЧИК - 2
    stepper.setSpeed(-200);
    Serial.println("slowUpSpeed");
  }

  if (stopUpSensor.isPress()) { // остановка фартука вверху ДАТЧИК - 3
    Serial.println("stopUpSensor");
    stepper.brake();
    flag = false;
  }
}
