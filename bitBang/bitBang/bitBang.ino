#define bignumofreads 1000// This is how many times we'll loop before averaging
float integration[4] = {0,0,0,0};
int step = 0; //counter for output pins' states
void setup() {
#define lowPin 3
pinMode(lowPin, OUTPUT);
#define highPin 4
pinMode(highPin, OUTPUT);
#define biasPin 0
pinMode(biasPin, OUTPUT);
digitalWrite(biasPin, HIGH);//this pin is used to pull up the bias divider so the adc is centered at 3.3/2
analogReadResolution(12); // 12 bit (4096 steps)
}

void loop() {
for (long i = 0;i<bignumofreads;i++)
{
  switch(step)
  {
    case 0:
      integration[3] += analogRead(A1);//capture the end of 3
      digitalWrite(highPin,HIGH);
      digitalWrite(lowPin,HIGH);
      //integration[0] += analogRead(14);
      break;
    case 1:
      integration[0] += analogRead(A1);
      digitalWrite(highPin,LOW);
      digitalWrite(lowPin,HIGH);
      break;
    case 2:
      integration[1] += analogRead(A1);
      digitalWrite(highPin,LOW);
      digitalWrite(lowPin,LOW);
      break;
    case 3:
      integration[2] += analogRead(A1);
      digitalWrite(highPin,HIGH);
      digitalWrite(lowPin,LOW);
      break;
  }
  step++;
  if(step>=4){step=0;} //reset when it overflows
  
  //integration += analogRead(A0);
  //delayMicroseconds(50);
  //delay(10);
}
Serial.println("---");
for(int i = 0; i<4; i++)
{
  Serial.println(integration[i]/bignumofreads);
}
for(int i = 3; i>=0;i--)
  {
    integration[i]=0;
  }
}
