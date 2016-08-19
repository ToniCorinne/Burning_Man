//Code for the barbie box Burning man 2016

const int goggleSwitch= 2; //pin for goggle switch
int switchState = 0;

const int LED1 = 3; //pin for LED 1
const int LED2 = 4; //pin for LED 2
const int LED3 = 5; //pin for LED 3
const int LED4 = 6; //pin for LED 4

void setup() {

  pinMode(goggleSwitch, INPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  
}

void loop() {
switchState = digitalRead(goggleSwitch);

if (switchState == HIGH){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
}
else {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);

}
}
