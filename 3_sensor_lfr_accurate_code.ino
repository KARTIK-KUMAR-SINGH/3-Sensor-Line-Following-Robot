void setup()
{
  pinMode(5, OUTPUT);  // M1 A (in1)(forward)
  pinMode(6, OUTPUT);  // M1 B (in2)(backward)
  pinMode(10, OUTPUT); // M2 A (in3)(forward)
  pinMode(11, OUTPUT); // M2 B (in4)(backward)
 
  pinMode(7, INPUT); // Sensor 1 (Left)
  pinMode(8, INPUT); // Sensor 2 (centre)
  pinMode(9, INPUT); // Sensor 3 (Right)

  pinMode(2, OUTPUT); // Enable 1 (enA)
  pinMode(3, OUTPUT); // Enable 2 (enB)
  pinMode(4, OUTPUT); // Additional VCC centre sensor 
  pinMode(12,OUTPUT);// Additional VCC right sensor
  pinMode(13,OUTPUT);// Additional Ground for right sensor 
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);    
  digitalWrite(4, HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
  
  Serial.begin(9600);
}

void forward()
{
  analogWrite(5, 85);
  analogWrite(6, 0);
  analogWrite(10,85);
  analogWrite(11, 0);
}

void left()
{
  analogWrite(5, 0);
  analogWrite(6, 0);
  analogWrite(10, 100);
  analogWrite(11, 0);
}
void sharpleft()
{
  analogWrite(5, 0);
  analogWrite(6, 10);
  analogWrite(10, 120);
  analogWrite(11, 0);
}

void right()
{
  analogWrite(5, 120);
  analogWrite(6, 0);
  analogWrite(10, 0);
  analogWrite(11, 0);
}

void sharpright()
{
  analogWrite(5, 120);
  analogWrite(6, 0);
  analogWrite(10, 0);
  analogWrite(11,120);
}
void loop()
{
  int s1 = digitalRead(7); // Left sensor
  int s2 = digitalRead(8); // Middle sensor
  int s3 = digitalRead(9); // Right sensor

  Serial.print("S1: "); Serial.print(s1);
  Serial.print(" S2: "); Serial.print(s2);
  Serial.print(" S3: "); Serial.println(s3);

  if (s1 == 0 && s2 == 1 && s3 == 0)  // Middle sensor on track
  {
    forward();
  }
  else if (s1 == 1 && s2 == 1 && s3 == 0) // Left and Middle detect track
  {
    left();
  }
  else if (s1 == 0 && s2 == 1 && s3 == 1) // Right and Middle detect track
  {
    right();
  }
  else if (s1 == 1 && s2 == 0 && s3 == 0) // Only left detects track
  {
    left();
  }
  else if (s1 == 0 && s2 == 0 && s3 == 1) // Only right detects track
  {
    right();
  }
  else if (s1 == 1 && s2 == 1 && s3 == 1) // All sensors detect track (junction)
  {
    forward();
  }
  delay(20); // Small delay for stability
}