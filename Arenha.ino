/*
 * created by Antonio Galiza
 * Bluetooth Control of Cyber Dona Aranha Mk1
 * 2013
 */
#include "PS2Mouse.h"

PS2Mouse mouse(12,11); //se nao funcionar, testar com 11 e 10

int motorPin1 = 2; // pin 2 on L293D IC
int motorPin2 = 4; // pin 7 on L293D IC,,,
int motorPin3 = 7;
int motorPin4 = 8;
int speedPin1 = 5; //speed control with PWM, motor 1
int speedPin2 = 6; //speed control with PWM, motor 2


int state;
int flag=0;        //makes sure that the serial only prints once the state


void setup() {
    // sets the pins as outputs:
    pinMode(speedPin1, OUTPUT);
    pinMode(speedPin2, OUTPUT);    
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorPin3, OUTPUT);
    pinMode(motorPin4, OUTPUT);
    // initialize serial communication at 9600 bits per second:
    Serial.begin(9600);
    while(!Serial);
    Serial.print("Setup...");
    mouse.begin();
    Serial.println("complete!");
}

void loop() {
    //if some date is sent, reads it and saves in state

    if(Serial.available() > 0){
      state = Serial.read();
      flag=0;
    }
    // if the state is '0' the DC motor will turn off
    if (state == '0') {
        digitalWrite(motorPin1, LOW); // set pin 5 on L293D low
        digitalWrite(motorPin2, LOW); // set pin 6 on L293D low
        digitalWrite(motorPin3, LOW); // set pin 9 on L293D low
        digitalWrite(motorPin4, LOW); // set pin 10 on L293D low
        if(flag == 0){
          Serial.println("CDA: stop");
          flag=1;
        }
    }
    // if the state is '1' spider turns clockwise
    else if (state == '1') {
        analogWrite (speedPin1,255);
        analogWrite (speedPin2,255);
        digitalWrite(motorPin1, LOW); // set pin 2 on L293D low
        digitalWrite(motorPin2, HIGH); // set pin 7 on L293D high
        digitalWrite(motorPin3, LOW); // set pin 2 on L293D low
        digitalWrite(motorPin4, HIGH); // set pin 7 on L293D high


        if(flag == 0){
          Serial.println("CDA: clockwise");
          flag=1;
        }
    }
    // if the state is '2' spider turns counterclockwise
    else if (state == '2') {
        analogWrite (speedPin1,255);
        analogWrite (speedPin2,255);
        digitalWrite(motorPin1, HIGH); // set pin 2 on L293D high
        digitalWrite(motorPin2, LOW); // set pin 7 on L293D low
        digitalWrite(motorPin3, LOW); // set pin 2 on L293D high
        digitalWrite(motorPin4, HIGH); // set pin 7 on L293D low
        if(flag == 0){
          Serial.println("CDA: counterclockwise");
          flag=1;
        }
    }
    // if the state is '3' spider goes forward 100 pulses
      // if the state is '3' spider goes forward
      else if (state == '3') {
          analogWrite (speedPin1,255);
          analogWrite (speedPin2,255);
          digitalWrite(motorPin1, HIGH); // set pin 2 on L293D high
          digitalWrite(motorPin2, LOW); // set pin 7 on L293D low
          digitalWrite(motorPin3, HIGH); // set pin 2 on L293D high
          digitalWrite(motorPin4, LOW); // set pin 7 on L293D low
          if(flag == 0){
            Serial.println("CDA: forward");
            flag=1;
          }

      }


    // if the state is '4' spider goes back
    else if (state == '4') {
        analogWrite (speedPin1,255);
        analogWrite (speedPin2,255);
        digitalWrite(motorPin1, LOW); // set pin 2 on L293D high
        digitalWrite(motorPin2, HIGH); // set pin 7 on L293D low
        digitalWrite(motorPin3, LOW); // set pin 2 on L293D high
        digitalWrite(motorPin4, HIGH); // set pin 7 on L293D low

        if(flag == 0){
          Serial.println("CDA: backwards");
          flag=1;
        }

    }

    else if (state == '5') {
        if(flag == 0){
          Serial.println("CDA: forward");
          flag=1;
        }
        analogWrite (speedPin1,255);
        analogWrite (speedPin2,255);
        int counter = 0;
        while (counter<1000){
          digitalWrite(motorPin1, HIGH); // set pin 2 on L293D high
          digitalWrite(motorPin2, LOW); // set pin 7 on L293D low
          digitalWrite(motorPin3, HIGH); // set pin 2 on L293D high
          digitalWrite(motorPin4, LOW); // set pin 7 on L293D low
          uint8_t stat;
          int x,y;
          mouse.getPosition(stat,x,y);
          counter = counter+y;
          delay(100);
        }
          digitalWrite(motorPin1, LOW); // set pin 2 on L293D high
          digitalWrite(motorPin2, LOW); // set pin 7 on L293D low
          digitalWrite(motorPin3, LOW); // set pin 2 on L293D high
          digitalWrite(motorPin4, LOW); // set pin 7 on L293D low
    }

    // if the state is '6' spider goes foraward, half-speed
    else if (state == '6') {
        analogWrite (speedPin1,120);
        analogWrite (speedPin2,120);
        digitalWrite(motorPin1, HIGH); // set pin 2 on L293D high
        digitalWrite(motorPin2, LOW); // set pin 7 on L293D low
        digitalWrite(motorPin3, HIGH); // set pin 2 on L293D high
        digitalWrite(motorPin4, LOW); // set pin 7 on L293D low

        if(flag == 0){
          Serial.println("CDA: backwards");
          flag=1;
        }

    }

}
