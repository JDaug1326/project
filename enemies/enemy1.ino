#include <Zumo32U4.h>
#include <Wire.h>

Zumo32U4LCD lcd;

Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonB buttonB;
Zumo32U4Motors motors;


unsigned int lineSensorValues[3];
int run = -1;


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
    
    if (lineSensorValues[0]/10 < 32){
      leftLine = 1;
    }
    if (lineSensorValues[1]/10 < 32){
      midLine = 1;
    }
    if (lineSensorValues[2]/10 < 32){
      rightLine = 1;
    }

    proxSensors.read();    
    int left_sensor = proxSensors.countsLeftWithLeftLeds();
    int front_left_sensor = proxSensors.countsFrontWithLeftLeds();
    int front_right_sensor = proxSensors.countsFrontWithRightLeds();
    int right_sensor = proxSensors.countsRightWithRightLeds();

    int output = 0;

    if (midLine==1){
      motors.setSpeeds(-350,-350);
      delay(100);
    }
    else if (leftLine==1){
      motors.setSpeeds(350,-350);
      delay(100);
      motors.setSpeeds(-350,-350);
      delay(100);    }
    else if (rightLine==1){
      motors.setSpeeds(-350,350);
      delay(100);
      motors.setSpeeds(-350,-350);
      delay(100);
    }
    else if (front_left_sensor-front_right_sensor>=2){
      motors.setSpeeds(-350,350);
      delay(100);
      motors.setSpeeds(350,350);
    }
    else if (front_right_sensor-front_left_sensor>=2){
      motors.setSpeeds(350,-350);
      delay(100);
      motors.setSpeeds(350,350);
    }
    
    else if(left_sensor<6 && left_sensor>right_sensor){
      motors.setSpeeds(-350,350);
    }
    else if(right_sensor<6 && right_sensor>left_sensor){
      motors.setSpeeds(350,-350);
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
