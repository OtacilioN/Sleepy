#include <Ultrasonic.h>

#define CALIBRATION_SAMPLES 10
#define MAX_ANGER 777
#define MAX_FADE_TIME 1000
#define DETECTION_RANGE 0.8
#define AVERAGE_LIGHT 400
#define UPDATE_ANGER_TIME 500

#define MAX_CALM_LIGHT 100

// Devices
Ultrasonic mouth(12, 13);
int tailLDR = A0;
int voiceBuzzer = 3;
int redLed = 5;
int greenLed = 6;
int blueLed = 9;

// Emotion Variable
int anger = 0;
int GPower = 0;

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
    analogWrite(greenLed, 0);
}

void calmBreathe()
{
  if (millis() - initalFadeTime > (MAX_FADE_TIME / MAX_CALM_LIGHT))
  {
    if (GPower > MAX_CALM_LIGHT){
      isIncreasing = -1; // Starts to decrease
      delay(150);
    }
      
    if (GPower <= 0){
      isIncreasing = 1; // Starts to decrease
      delay(150);
    }

    GPower = GPower + isIncreasing;
    analogWrite(greenLed, GPower);

    initalFadeTime = millis();
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
  Serial.println(mouth.distanceRead());
  if (mouth.distanceRead() < nearestWall * DETECTION_RANGE)
  {
    delay(1);
    if (mouth.distanceRead() < nearestWall * DETECTION_RANGE)
    {
      delay(1);
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
  if (analogRead(tailLDR) < AVERAGE_LIGHT){
    return true;
  }
  return false;
}
