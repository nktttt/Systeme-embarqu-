# Systeme-embarqu-
/*
  FadeSerial
*/

int led1 = 9;             // the PWM pin the LED is attached to
int led2 = 10;           // the PWM pin the LED is attached to
byte brightness = 0;    // how bright the LED is
byte fadeAmount = 5;   // how many points to fade the LED by

 // the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);
  // declare pin 9 to be an output:
  pinMode(led1, OUTPUT); // branchement led 1
  pinMode(led2, OUTPUT); // branchement led 2 
}

// the loop routine runs over and over again forever:
void loop() {
    // set the brightness of pin 9:
    analogWrite(led1, brightness);
    digitalWrite(led1, HIGH); // allume led 1
    digitalWrite(led2, LOW); // eteint led 2
    Serial.println(led1);    // affiche etat led 1 
    delay(1500);           // attend 2 sec
    

    // set the brightness of pin 9:
    analogWrite(led2, brightness);
    digitalWrite(led1, LOW);   // eteint led 1
    digitalWrite(led2, HIGH); // allume led 2
    Serial.println(led2);    // affiche etat led 2
    delay(1500);          // attend 1,5 sec

    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount;
    
    // change the brightness for next time through the loop:
    brightness = brightness + fadeAmount;
    Serial.println(brightness);
    }
    // wait for 30 milliseconds to see the dimming effect
    delay(30);
}
