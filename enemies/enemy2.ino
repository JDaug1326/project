#include <Zumo32U4.h>
#include <Wire.h>

Zumo32U4LCD lcd;
Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonB buttonB;
Zumo32U4Motors motors;

unsigned int lineSensorValues[3];
int run = -1;
int start = 1;


void setup() {
  lineSensors.initThreeSensors();
  proxSensors.initThreeSensors();
  lineSensors.emittersOn();
}

void loop() {
  bool buttonPress = buttonB.getSingleDebouncedPress();
  if (buttonPress){
    run = run*-1;
    lcd.gotoXY(0, 0);
    lcd.print("                 ");
    lcd.gotoXY(1,1);
    lcd.print("                 ");
  }
  if (run>0){
    
    lineSensors.read(lineSensorValues);
    int leftLine = 0;
    int midLine = 0;
    int rightLine = 0;
    
    if (lineSensorValues[0]/10 < 100){
      leftLine = 1;
    }
    if (lineSensorValues[1]/10 < 100){
      midLine = 1;
    }
    if (lineSensorValues[2]/10 < 100){
      rightLine = 1;
    }

    proxSensors.read();    
    int left_sensor = proxSensors.countsLeftWithLeftLeds();
    int front_left_sensor = proxSensors.countsFrontWithLeftLeds();
    int front_right_sensor = proxSensors.countsFrontWithRightLeds();
    int right_sensor = proxSensors.countsRightWithRightLeds();

    int output = 0;
    if (start==1){
      motors.setSpeeds(-350,-150);
      delay(400);
      start=2;
    }

    else if (midLine==1){
      motors.setSpeeds(-350,-350);
      delay(400);
    }
    else if (leftLine==1){
      motors.setSpeeds(350,-350);
      delay(100);
      motors.setSpeeds(-350,-350);
      delay(300);    }
    else if (rightLine==1){
      motors.setSpeeds(-350,350);
      delay(100);
      motors.setSpeeds(-350,-350);
      delay(300);
    }
    else{
      motors.setSpeeds(350,350);
    }

    lcd.gotoXY(0, 0);
    lcd.print(left_sensor);
    lcd.print(" ");
    lcd.print(front_left_sensor);
    lcd.print(" ");
    lcd.print(front_right_sensor);
    lcd.print(" ");
    lcd.print(right_sensor);
    lcd.gotoXY(0, 1);
    lcd.print(lineSensorValues[0]/100);
    lcd.print(" ");
    lcd.print(lineSensorValues[1]/100);
    lcd.print(" ");
    lcd.print(lineSensorValues[2]/100);
    lcd.print(" ");
    lcd.print(output);

  }
  else{
    lcd.gotoXY(0,0);
    lcd.print("Press B");
    lcd.gotoXY(0,1);
    lcd.print("to start!");
  }
}
