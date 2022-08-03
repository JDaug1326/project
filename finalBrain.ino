#include <Zumo32U4.h>
#include <Wire.h>

Zumo32U4LCD lcd;

Zumo32U4LineSensors lineSensors;
Zumo32U4ProximitySensors proxSensors;
Zumo32U4ButtonA buttonA;
Zumo32U4Motors motors;

unsigned int lineSensorValues[3];
int run = -1;

void setup() {
  lineSensors.initThreeSensors();
  proxSensors.initThreeSensors();
  lineSensors.emittersOn();
}

void loop() {

  bool buttonPress = buttonA.getSingleDebouncedPress();
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

    double layer1neuron1 = ((leftLine*-8.4279989)+(midLine*-7.0035882)+(rightLine*-6.3510838)+(left_sensor*-1.0312436)+(right_sensor*1.4090265)+(front_left_sensor*5.2697810)+(front_right_sensor*5.7205786));
    double layer1neuron2 = ((leftLine*0.6031827)+(midLine*-0.7543703)+(rightLine*-3.2667462)+(left_sensor*-4.2247193)+(right_sensor*2.7477704)+(front_left_sensor*2.7477181)+(front_right_sensor*3.4516264));
    double layer1neuron3 = ((leftLine*-4.2196410)+(midLine*-2.3586177)+(rightLine*0.1909564)+(left_sensor*5.1449976)+(right_sensor*-3.5222614)+(front_left_sensor*3.0011831)+(front_right_sensor*2.8961229));
    double layer1neuron4 = ((leftLine*3.6753936)+(midLine*6.7244394)+(rightLine*4.5761074)+(left_sensor*-6.6256493)+(right_sensor*-4.4625262)+(front_left_sensor*-6.6174543)+(front_right_sensor*-8.1489333));
    double layer1neuron5 = ((leftLine*6.5519235)+(midLine*5.9296442)+(rightLine*5.7499311)+(left_sensor*-5.6819405)+(right_sensor*-3.1420060)+(front_left_sensor*-5.5852812)+(front_right_sensor*-6.7725081));
    double layer1neuron6 = ((leftLine*-6.6169252)+(midLine*-6.4298812)+(rightLine* -6.2583797)+(left_sensor*-0.0562661)+(right_sensor*0.4003406)+(front_left_sensor*5.8201430)+(front_right_sensor*6.6922589));
    double layer1neuron7 = ((leftLine*2.3272286)+(midLine*0.7630925)+(rightLine*0.2144796)+(left_sensor*3.9414196)+(right_sensor*-1.8363391)+(front_left_sensor*2.7810711)+(front_right_sensor*2.7154222));
    double layer1neuron8 = ((leftLine*-0.2998726)+(midLine* 0.7869503)+(rightLine*-1.9946199)+(left_sensor*-4.8376132)+(right_sensor*3.6126331)+(front_left_sensor*3.4312893)+(front_right_sensor*3.2270152));
    double layer1neuron9 = ((leftLine*-1.1464866)+(midLine* -6.6904505)+(rightLine*-5.5037068)+(left_sensor*2.4321705)+(right_sensor*1.4614460)+(front_left_sensor*6.4125614)+(front_right_sensor*6.4854901));
    double layer1neuron10 = ((leftLine*2.7909224)+(midLine*-3.0227410)+(rightLine*-0.7982797)+(left_sensor*-3.0150721)+(right_sensor*1.5871979)+(front_left_sensor*2.5056250)+(front_right_sensor*2.6427801));
    double layer1neuron11 = ((leftLine*-0.6792731)+(midLine*-4.6495300)+(rightLine*1.0275607)+(left_sensor*3.4078370)+(right_sensor*-1.6143051)+(front_left_sensor*2.5692403)+(front_right_sensor*3.4790882));
    double layer1neuron12 = ((leftLine*5.0949627)+(midLine*5.7087870)+(rightLine*6.6095271)+(left_sensor*-4.7212940)+(right_sensor*-4.7526908)+(front_left_sensor*-5.8890406)+(front_right_sensor*-6.0899068));

    double layer2neuron1 = ((layer1neuron1*-5.5416529)+(layer1neuron2*0.6140295)+(layer1neuron3*0.1662348)+(layer1neuron4*6.3542672)+(layer1neuron5*4.8946732)+(layer1neuron6*-5.0685770)+(layer1neuron7*-2.4153197)+(layer1neuron8*0.4251626)+(layer1neuron9*-6.2897803)+(layer1neuron10*-0.6915570)+(layer1neuron11*1.8946693)+(layer1neuron12*4.5389385));
    double layer2neuron2 = ((layer1neuron1*-0.8515041)+(layer1neuron2*-4.3019167)+(layer1neuron3*5.2151737)+(layer1neuron4*-2.2225647)+(layer1neuron5*-3.4757677)+(layer1neuron6*2.1383315)+(layer1neuron7*5.9799066)+(layer1neuron8*-5.5888304)+(layer1neuron9*-0.7618162)+(layer1neuron10*-4.8011215)+(layer1neuron11*-6.8998981)+(layer1neuron12*-3.6948728));
    double layer2neuron3 = ((layer1neuron1*6.6115891)+(layer1neuron2* 0.6241113)+(layer1neuron3*1.7760930)+(layer1neuron4*-6.8277268)+(layer1neuron5*-6.7635791)+(layer1neuron6*4.5605454)+(layer1neuron7*0.9888863)+(layer1neuron8*1.9843255)+(layer1neuron9*6.1771524)+(layer1neuron10*0.4855120)+(layer1neuron11*1.1177684)+(layer1neuron12*-7.7410057));
    double layer2neuron4 = ((layer1neuron1*-6.9610988)+(layer1neuron2*-0.1057106)+(layer1neuron3*0.7324161)+(layer1neuron4*6.6923586)+(layer1neuron5*6.8301680)+(layer1neuron6*-7.3974217)+(layer1neuron7*-1.4059117)+(layer1neuron8*0.7236663)+(layer1neuron9*-8.0747112)+(layer1neuron10*0.0901647)+(layer1neuron11*1.5268990)+(layer1neuron12*5.6787519));
    double layer2neuron5 = ((layer1neuron1*-0.3904780)+(layer1neuron2*7.0120360)+(layer1neuron3*-4.7117345)+(layer1neuron4*-2.4927151)+(layer1neuron5*-2.4232027)+(layer1neuron6*0.7742733)+(layer1neuron7*-6.3946104)+(layer1neuron8*-6.0118990)+(layer1neuron9*-0.9279368)+(layer1neuron10*6.2372172)+(layer1neuron11*-6.2783170)+(layer1neuron12*-2.8826040));
    double layer2neuron6 = ((layer1neuron1*-7.8552215)+(layer1neuron2*-0.9828883)+(layer1neuron3*-0.5846699)+(layer1neuron4*7.4727764)+(layer1neuron5*5.8246514)+(layer1neuron6*-4.3393133)+(layer1neuron7*-0.5285276)+(layer1neuron8*-0.3368121)+(layer1neuron9*-4.6039150)+(layer1neuron10*-0.6445510)+(layer1neuron11*-2.1787071)+(layer1neuron12*7.2446229));
    double layer2neuron7 = ((layer1neuron1*-0.1832640)+(layer1neuron2*-7.5971420)+(layer1neuron3*5.8528572)+(layer1neuron4*-1.5090236)+(layer1neuron5*-0.8559808)+(layer1neuron6*1.4768111)+(layer1neuron7*6.5240824)+(layer1neuron8*-4.5995751)+(layer1neuron9*-0.9733624)+(layer1neuron10*0.2984871)+(layer1neuron11*6.0918985)+(layer1neuron12*-2.1203237));
    double layer2neuron8 = ((layer1neuron1*1.2940232)+(layer1neuron2*6.4551164)+(layer1neuron3*-5.6882312)+(layer1neuron4*-2.8056708)+(layer1neuron5*-0.8492326)+(layer1neuron6*-0.1917248)+(layer1neuron7*-7.1396318)+(layer1neuron8*5.3247779)+(layer1neuron9*-1.7140927)+(layer1neuron10*5.4456872)+(layer1neuron11*-6.8661626)+(layer1neuron12*-0.9409705));
    double layer2neuron9 = ((layer1neuron1*0.6707201)+(layer1neuron2*-6.0647752)+(layer1neuron3*5.3618234)+(layer1neuron4*-3.0026860)+(layer1neuron5*0.5066174)+(layer1neuron6*1.9742477)+(layer1neuron7*8.1683484)+(layer1neuron8*-6.2389065)+(layer1neuron9*0.1740262)+(layer1neuron10*0.6462164)+(layer1neuron11*4.9739673)+(layer1neuron12* -0.5291709));
    double layer2neuron10 = ((layer1neuron1*2.2912593)+(layer1neuron2*7.3342795)+(layer1neuron3*-4.9307021)+(layer1neuron4*-1.6710905)+(layer1neuron5*-0.0262560)+(layer1neuron6*0.9020203)+(layer1neuron7*-7.3595523)+(layer1neuron8*5.9759720)+(layer1neuron9*-0.8359406)+(layer1neuron10*6.8012659)+(layer1neuron11*-4.7814832)+(layer1neuron12*-0.0499779));
    double layer2neuron11 = ((layer1neuron1*7.7739359)+(layer1neuron2*2.2213415)+(layer1neuron3*2.5641939)+(layer1neuron4*-6.4251983)+(layer1neuron5*-7.7459479)+(layer1neuron6*5.6042962)+(layer1neuron7*1.6577665)+(layer1neuron8*2.1791777)+(layer1neuron9*6.9026834)+(layer1neuron10*0.2355788)+(layer1neuron11*-0.2316910)+(layer1neuron12*-7.5021748));
    double layer2neuron12 = ((layer1neuron1*7.2291425)+(layer1neuron2*0.8180817)+(layer1neuron3*1.5939068)+(layer1neuron4*-4.8526634)+(layer1neuron5*-5.6918454)+(layer1neuron6*5.2248323)+(layer1neuron7*1.2754984)+(layer1neuron8*2.8325739)+(layer1neuron9*8.3128979)+(layer1neuron10*1.1003322)+(layer1neuron11*-1.2153797)+(layer1neuron12*-7.3547014));

    double output1 = ((layer2neuron1*-3.5436157)+(layer2neuron2*0.7716229)+(layer2neuron3*7.3425490)+(layer2neuron4*-5.3122700)+(layer2neuron5*2.2138340)+(layer2neuron6*-3.6419346)+(layer2neuron7*-1.3274868)+(layer2neuron8*-1.0808138)+(layer2neuron9*-2.4074317)+(layer2neuron10*-1.9311673)+(layer2neuron11*6.6537568)+(layer2neuron12*7.0696906));
    double output2 = ((layer2neuron1*-5.1871144)+(layer2neuron2*7.2080880)+(layer2neuron3*-1.1386679)+(layer2neuron4*-6.2676243)+(layer2neuron5*-7.1836091)+(layer2neuron6*-2.5191910)+(layer2neuron7*7.6509634)+(layer2neuron8*-7.4466722)+(layer2neuron9*8.2786562)+(layer2neuron10*-3.7865492)+(layer2neuron11*-2.4654953)+(layer2neuron12*-0.6959822));
    double output3 = ((layer2neuron1*-4.8962208)+(layer2neuron2*-3.5019508)+(layer2neuron3*-1.2769154)+(layer2neuron4*-2.9637238)+(layer2neuron5*6.6137342)+(layer2neuron6*-5.2410653)+(layer2neuron7*-5.6318812)+(layer2neuron8*7.6430704)+(layer2neuron9*-2.9578217)+(layer2neuron10*8.4850505)+(layer2neuron11*-2.1436204)+(layer2neuron12*-0.8175281));
    double output4 = ((layer2neuron1*8.2788222)+(layer2neuron2*-2.4223018)+(layer2neuron3*-3.6995573)+(layer2neuron4*8.2313700)+(layer2neuron5*-0.5939192)+(layer2neuron6*8.4541449)+(layer2neuron7*-0.1958090)+(layer2neuron8*-0.0256387)+(layer2neuron9*1.3731701)+(layer2neuron10*0.1907794)+(layer2neuron11*-2.2063682)+(layer2neuron12*-2.6786015));
    int output = 0;

    if (output1 > output2 && output1 > output3 && output1 > output4){
      motors.setSpeeds(350,350);
      output = 1;
    }
    else if (output2 > output1 && output2 > output3 && output2 > output4){
      motors.setSpeeds(-350, 350);
      output = 2;
    }
    else if (output3 > output1 && output3 > output2 && output3 > output4){
      motors.setSpeeds(350, -350);
      output = 3;
    }
    else if ((output4 > output2 && output4 > output1 && output4 > output3) || leftLine==1 || midLine==1 || rightLine==1){
      motors.setSpeeds(-350,-350);
      output = 4;
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
    lcd.print("Press A");
    lcd.gotoXY(0,1);
    lcd.print("to start!");
  }
}
