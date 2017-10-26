/*
 *  WSU Robotics Club -- Drone Team
 *  Test_PWM
 *  
 *  Procedure built to run and test drone motors by varying the duty cycle of the PWM being supplied to the
 *    drivers
 */

// Global Parameters ----------------------------------------------------------------------------------------
#define S1_PIN 12
#define PERIOD 2500 //2500us (2.5ms) in a period

// Global Variables -----------------------------------------------------------------------------------------
bool _positive = false;
int _currentTime = 0, _previousTime = 0;
float _throttle = 0; //Set to 0% throttle by default

void setup() 
{
  Serial.begin(9600);
  
  pinMode(S1_PIN, OUTPUT);
  digitalWrite(S1_PIN, LOW);
}

void loop() 
{
  //Read from the serial stream to update the duty cycle
  if(Serial.available())
  {
    float temp_throttle = Serial.parseFloat();

    //Because Serial.parseInt() can timeout if an input is not received fast enough, we want to check and
    //  see if we have a valid entry before updating the duty cycle
    if(temp_throttle > 0)
      _throttle = temp_throttle;
  }
  
  _currentTime = micros();

  if(_positive) //If on the positive side of the cycle...
  {
    if(_currentTime-_previousTime >= PERIOD*throttle_to_duty(_throttle)) //... and we've reached the end of the duty cycle for this period:
    {
      //Drive the output low but don't reset the timer, the period continues
      digitalWrite(S1_PIN, LOW);
    }
  }
  else //If on the negative side of the cycle...
  {
    if(_currentTime-_previousTime >= PERIOD) //... and we've reached the end of the period:
    {
      //The next cycle has begun, drive the output high again
      digitalWrite(S1_PIN, HIGH);

      //Reset the timer
      _previousTime = _currentTime;
    }
  }
}

// Custom Functions -------------------------------------------------------------------------------------

//Calculate the required duty cycle for the throttle input
float throttle_to_duty(double throttle)
{
  return (40 + (.309 * throttle))/100; //Equation taken from characteristic analysis of our ESC's throttle response
}

