#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


//LEDS///
#define PIN            6

#define NUMPIXELS      8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

//SERVOS///
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  375 // this is the 'maximum' pulse length count (out of 4096)

// our servo # counter
uint8_t servonum = 0;

//Sliding Pots
int analogPin = A0;
int analogPin1 = A1;
int analogPin2 = A2;
int analogPin3 = A3;
int analogPin4 = A4;

int analogOut = 1;

int val = 0;
int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;

int newVal = 0;
int newVal1 = 0;
int newVal2 = 0;
int newVal3 = 0;
int newVal4 = 0;

int prevVal = 0;
int prevVal1 = 0;
int prevVal2 = 0;
int prevVal3 = 0;
int prevVal4 = 0;

int spMot4 = 0;
int spMot3 = 0;
int spMot2 = 0;
int spMot1 = 0;
int spMot = 0;
int mult4 = 0;
int mult3 = 0;
int mult2 = 0;
int mult1 = 0;
int mult = 0;

void setup() {
  Serial.begin(9600);

  //Sliding pot setup
  pinMode(analogPin, INPUT);
  pinMode(analogPin1, INPUT);
  pinMode(analogPin2, INPUT);
  pinMode(analogPin3, INPUT);
  pinMode(analogPin4, INPUT);

  //LED setup
  pixels.begin(); // This initializes the NeoPixel library.

  //Servo setup
  pwm.begin();
  pwm.setPWMFreq(60);
  pwm.setPWM(0, 0, 338);
  pwm.setPWM(1, 0, 336);
  pwm.setPWM(2, 0, 337);
  pwm.setPWM(3, 0, 337);
  pwm.setPWM(4, 0, 340);

}

void loop() {

  for(int i=0;i<NUMPIXELS;i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(155, 0, 0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    //delay(delayval); // Delay for a period of time (in milliseconds).
  }
  
  val = analogRead(analogPin);
  val1 = analogRead(analogPin1);
  val2 = analogRead(analogPin2);
  val3 = analogRead(analogPin3);
  val4 = analogRead(analogPin4);
  
  //Serial.println(val);
  newVal = getLog(val); //assigns linear values to log pot...not exactly equally, but alas
  newVal1 = getLog(val1);
  newVal2 = getLog(val2);
  newVal3 = getLog(val3);
  newVal4 = getLog(val4);

  //neeeds to be callibrated
  if (newVal != prevVal){
    if (newVal > prevVal){
       spMot = 355;
    }
    else if (newVal < prevVal){
      spMot = 319;
    }

    //mult4 = abs(prevVal4 - newVal4);
    
    pwm.setPWM(0, 0, spMot);
    delay(750);
    pwm.setPWM(0, 0, 337);
  }
  /////
  if (newVal1 != prevVal1){
    if (newVal1 > prevVal1){
       spMot1 = 355;
    }
    else if (newVal1 < prevVal1){
      spMot1 = 319;
    }

    //mult4 = abs(prevVal4 - newVal4);
    
    pwm.setPWM(1, 0, spMot1);
    delay(750);
    pwm.setPWM(1, 0, 336);
  }

  if (newVal2 != prevVal2){
    if (newVal2 > prevVal2){
       spMot2 = 356;
    }
    else if (newVal2 < prevVal2){
      spMot2 = 320;
    }

    //mult4 = abs(prevVal4 - newVal4);
    
    pwm.setPWM(2, 0, spMot2);
    delay(750);
    pwm.setPWM(2, 0, 337);
  }

  if (newVal3 != prevVal3){
    if (newVal3 > prevVal3){
       spMot3 = 356;
    }
    else if (newVal3 < prevVal3){
      spMot3 = 320;
    }

    //mult4 = abs(prevVal4 - newVal4);
    
    pwm.setPWM(3, 0, spMot3);
    delay(750);
    pwm.setPWM(3, 0, 337);
  }

  if (newVal4 != prevVal4){
    if (newVal4 > prevVal4){
       spMot4 = 355;
    }
    else if (newVal4 < prevVal4){
      spMot4 = 319;
    }

    //mult4 = abs(prevVal4 - newVal4);
    
    pwm.setPWM(4, 0, spMot4);
    delay(750);
    pwm.setPWM(4, 0, 340);
  }
  
  
  
  Serial.print(newVal);
  Serial.print("\t");
  Serial.print(newVal1);
  Serial.print("\t");
  Serial.print(newVal2);
  Serial.print("\t");
  Serial.print(newVal3);
  Serial.print("\t");
  Serial.print(newVal4);


  prevVal = newVal; //allows storage of last read
  prevVal1 = newVal1;
  prevVal2 = newVal2;
  prevVal3 = newVal3;
  prevVal4 = newVal4;
  
  //might need some code to make it stay in position until
  //otherwise moved??
  //if val is within 5 of previous read value
  //don't move

  delay(500);

}

int getLog(int x){
  int linVal;
  if (0<=x && x<221){
    linVal = 0;
  }
  else if (222<x && x<700){
    linVal = 1;
  }
  else if (701<x && x<853){
    linVal = 2;
  }
  else if (854<x && x<963){
    linVal = 3;
  }
  else if (964<x && x<1003){
    linVal = 4;
  }
  else if (1004<x && x<1024){
    linVal = 5;
  }
  return linVal;
}

/*Servo runServoCW (Servo servoFun, int Pin){
  servoFun.attach(Pin);
  servoFun.write(95);
  delay(100); //based off of assumption that it takes .600 at 95 speed to unroll/roll finger
  servoFun.detach();
}

Servo runServoCCW (Servo servoFun2, int Pin2){
  servoFun2.attach(Pin2);
  servoFun2.write(95);
  delay(100);
  servoFun2.detach();
}
*/

