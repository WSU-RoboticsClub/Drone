/*
 *  WSU Robotics Club -- Drone Team
 *  Test_PWM
 *  
 *  Procedure built to run and test drone motors by varying the duty cycle of the PWM being supplied to the
 *    drivers
 */

// Global Parameters ----------------------------------------------------------------------------------------
const int s1_pin = 12;
const int period = 2500; //2500us (2.5ms) in a period

// Global Variables -----------------------------------------------------------------------------------------
bool positive = false;
int currentTime = 0, previousTime = 0, duty = 50; //Duty cycle, starts at 50%

void setup() 
{
  Serial.begin(9600);
  
  pinMode(s1_pin, OUTPUT);
  digitalWrite(s1_pin, LOW);
}

void loop() 
{
  //Read from the serial stream to update the duty cycle
  if(Serial.available())
  {
    int temp_duty = Serial.parseInt();

    //Because Serial.parseInt() can timeout if an input is not received fast enough, we want to check and
    //  see if we have a valid entry before updating the duty cycle
    if(temp_duty > 0)
      duty = temp_duty;
  }
  
  currentTime = micros();

  if(positive) //If on the positive side of the cycle...
  {
    if(currentTime-previoustime >= period*duty) //... and we've reached the end of the duty cycle for this period:
    {
      //Drive the output low but don't reset the timer, the period continues
      digitalWrite(s1_pin, LOW);
    }
  }
  else //If on the negative side of the cycle...
  {
    if(currentTime-previousTime >= period) //... and we've reached the end of the period:
    {
      //The next cycle has begun, drive the output high again
      digitalWrite(s1_pin, HIGH);

      //Reset the timer
      previousTime = currenTime;
    }
  }
}
