#include <Ultrasonic.h>

#define CALIBRATION_SAMPLES 10
#define MAX_ANGER 777
#define MAX_FADE_TIME 1000
#define DETECTION_RANGE 0.8
#define AVERAGE_LIGHT 400
#define UPDATE_ANGER_TIME 500

// Anger states
#define ANGER1 (MAX_ANGER / 5)
#define ANGER2 2 * (MAX_ANGER / 5)
#define ANGER3 3 * (MAX_ANGER / 5)
#define ANGER4 4 * (MAX_ANGER / 5)

#define MAX_CALM_LIGHT 100
#define MAX_ANALOG_VALUE 255

// Devices
Ultrasonic mouth(12, 13);
int tailLDR = A0;
int voiceBuzzer = 3;
int redLed = 5;
int greenLed = 6;
int blueLed = 9;

// Emotion Variable
int anger = 0;
int RPower = 0;
int GPower = 0;
int BPower = 0;

// Ambient calibration
int nearestWall = 300;

// Time Variables
int initialUpdateTime = 0;
int initalFadeTime = 0;

// Flags
int isIncreasing = 1; // -1 to decrease

void setup()
{
  Serial.begin(9600);
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);
  delay(10);
  nearestWall = averageDistance();
  delay(10);
}

void loop()
{
  if ((iAmAlone() && itIsDark()) || (!iAmAlone() && !itIsDark())) // xNOR equivalent
    calmDown();
  else
    getAnger();

  if (!anger)
    calmBreathe();
  else
    applyAnger();

  Serial.println(anger);
}

void calmBreathe()
{
  if (millis() - initalFadeTime > (MAX_FADE_TIME / MAX_CALM_LIGHT))
  {
    if (GPower > MAX_CALM_LIGHT)
    {
      isIncreasing = -1; // Starts to decrease
      delay(150);
    }

    if (GPower <= 0)
    {
      isIncreasing = 1; // Starts to decrease
      delay(150);
    }

    GPower = GPower + isIncreasing;
    analogWrite(greenLed, GPower);

    initalFadeTime = millis();
  }
}

void applyAnger()
{
  if (anger < ANGER1)
  {
    RPower = BPower = 0;
    GPower = anger;
  }
  else if (anger < ANGER2)
  {
    RPower = 0;
    GPower = anger;
    BPower = anger - ANGER1;
  }
  else if (anger < ANGER3)
  {
    RPower = GPower = 0;
    BPower = anger - ANGER2;
  }
  else if (anger < ANGER4)
  {
    GPower = 0;
    BPower = anger - ANGER2;
    RPower = anger - ANGER3;
  }
  else{
    RPower = anger - ANGER4;
    BPower = GPower = 0;
  }
    

  analogWrite(redLed, RPower);
  analogWrite(greenLed, GPower);
  analogWrite(blueLed, BPower);
}

void getAnger()
{
  if (millis() - initialUpdateTime > UPDATE_ANGER_TIME)
  {
    if (anger <= MAX_ANGER)
      anger++;
    initialUpdateTime = millis();
  }
}

void calmDown()
{
  if (millis() - initialUpdateTime > UPDATE_ANGER_TIME)
  {
    if (anger > 0)
      anger--;
    initialUpdateTime = millis();
  }
}

int averageDistance()
{
  int average = 0;
  for (int x = 0; x < CALIBRATION_SAMPLES; x++)
  {
    average = average + mouth.distanceRead();
    delay(2);
  }
  return average / CALIBRATION_SAMPLES;
}

bool iAmAlone()
{
  if (mouth.distanceRead() < nearestWall * DETECTION_RANGE)
  {
    delay(3);
    if (mouth.distanceRead() < nearestWall * DETECTION_RANGE)
    {
        Serial.println("US FALSE");
        Serial.println(mouth.distanceRead());
        Serial.println(nearestWall * DETECTION_RANGE);
        
        return false;
    }
  }
  Serial.println("US TRUE");
  return true;
}

bool itIsDark()
{
  if (analogRead(tailLDR) < AVERAGE_LIGHT)
  {
    Serial.println("LIGHT TRUE");
    return true;
  }
  Serial.println("LIGHT FALSE");
  return false;
}
