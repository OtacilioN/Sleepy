#include <Ultrasonic.h>

#define CALIBRATION_SAMPLES 30
#define MAX_ANGER 777
#define MAX_FADE_TIME 1000
#define DETECTION_RANGE 0.8
#define AVERAGE_LIGHT 400
#define UPDATE_ANGER_TIME 500

// Devices
Ultrasonic mouth(12, 13);
int tailLDR = A0;
int voiceBuzzer = 3;
int redLed = 5;
int greenLed = 6;
int blueLed = 9;

// Emotion Variable
int anger = 0;

// Ambient calibration
int nearestWall = 300;

// Time Variables
int initialUpdateTime = 0;
int initalFadeTime = 0;

void setup()
{
  Serial.begin(9600);
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
}

void fadeLight()
{
  if (anger < 256)
  {
  }
}

void getAnger()
{
  if (millis() - initialUpdateTime > UPDATE_ANGER_TIME)
  {
    if (anger < MAX_ANGER)
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
    delay(2);
    if (mouth.distanceRead() < nearestWall * DETECTION_RANGE)
    {
      delay(2);
      if (mouth.distanceRead() < nearestWall * DETECTION_RANGE)
      {
        return false;
      }
    }
  }
  return true;
}

bool itIsDark()
{
  if (analogRead(ldr) < AVERAGE_LIGHT)
    return true;
  return false;
}
