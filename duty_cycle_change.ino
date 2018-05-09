#define g1 6
#define g2 9
#define g3 10
#define g4 11

int frequency=44; //frequency to design
int dutyCycle=50; //initialisation
double delayms=1000/(2*frequency);  //each gate signal will be ON for half of the output frequency

double onTime=delayms; //initialisation
double offTime=0;   //initialisation
int delayTune=300;    //tuning variable to get required output frequency

void setup() {
  pinMode(g1,OUTPUT);
  pinMode(g2,OUTPUT);
  pinMode(g3,OUTPUT);
  pinMode(g4,OUTPUT);
  
  Serial.begin(9600);

  Serial.println();
  Serial.println();
  Serial.println("Enter the percentage duty cycle(0-100) you want: ");    
  while(Serial.available()==0) {}   //wait untill user's input
  dutyCycle=Serial.parseInt();    //take input

  if(dutyCycle<100)   //extra tuning, beacuse the output frequecny increased if duty cycle wa less than 100%
  {
    delayTune+=970;
  }
  onTime=(delayms*dutyCycle)/100;   //ON-time based on duty cycle
  offTime=delayms-onTime;   //rest time is OFF-time
  Serial.println();
  Serial.print("Given Duty Cycle: ");
  Serial.print(dutyCycle);
  Serial.println("%");  
}

void loop() {
  digitalWrite(g1,LOW);
  digitalWrite(g2,LOW); 
  digitalWrite(g3,LOW);
  digitalWrite(g4,LOW);
  delay(offTime);
  digitalWrite(g1,HIGH);
  digitalWrite(g2,HIGH);
  delay(onTime);

  delayMicroseconds(delayTune);
  
  digitalWrite(g1,LOW);
  digitalWrite(g2,LOW); 
  digitalWrite(g3,LOW);
  digitalWrite(g4,LOW);
  delay(offTime);
  digitalWrite(g3,HIGH);
  digitalWrite(g4,HIGH);
  delay(onTime);

  delayMicroseconds(delayTune);
}
