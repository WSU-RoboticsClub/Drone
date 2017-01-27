// Constant Variables ----------------------------------------------------------------------
const int testPin = 7;

// Global Variables ------------------------------------------------------------------------
unsigned long duration = 0;

// Start Program ---------------------------------------------------------------------------
void setup() 
{
  pinMode(testPin, INPUT);

  //Begin Serial
  Serial.begin(115200);
}

void loop() 
{
  duration = pulseIn(testPin, HIGH);
  Serial.println(duration);
  delay(10);
}
