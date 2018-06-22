# Sleepy Robot
_Development of an emotive robot to raise awareness about the use of lamps by Otacilio Maia and Yago Albert, Cesar School students._

## Table of contents
- The Problem
- The Solution
- The Components

## The Problem

One of the great global challenges is the population's awareness against the waste of electricity, several campaigns are created year after year. At the Cesar School, although students generally have a good level of environmental awareness, sometimes even for the sake of distraction, it is possible to find lights on in the living room, with no one inside.

Another problem often encountered is that students forget to turn on the lamps when they enter the auditorium during project hours and, in the dark, perform project and study activities where such practice under inadequate light conditions can be harmful to the health of students.

A possible solution would be the installation of automatic systems to connect the lamps in the classrooms, but this action requires an infrastructure effort, needing to adapt the system to the electrical network, and a high cost for implementation in each environment of the college.

So this project opts for the awareness approach, the Sleepy emotive robot should stay in the environment where the students spend more time, the auditorium, where through emotion reactions the robot should make students aware of Turning on the lamps when entering the environment and disconnect the when you leave. Making this act so natural that the student finishes performing it even in environments where the Sleepy robot is not present.


## The Solution

Develop a robot capable of identifying the presence of people in the environment through a PIR (Passive Infra-Red) sensor, and identify the ambient light through a LDR (Light Dependent Resistor), to express interaction with the environment through emotions using an RGB led, to express emotions by color, and a buzzer to express emotions by sound.

The program will have a variable named "anger" that will store how angry the robot is, whenever the robot detects that there are no people in the room and that the light is on, or that there are people in the room and the light is off, this variable starts to be incremented. As well, if the light is on and there are people in the room or deleted and there are no people in the room, the variable begins to be decremented.

The natural state of Sleepy is sleeping, so when the anger variable is set to zero, Sleepy does not emit sounds and lightly pulsates the RGB led in green color, indicating its vital signs and simulating a relaxed breath. As well as as the anger variable is increased, Sleepy begins to pulse more intensively by varying to a medium level of anger expressed in blue, until reaching a pulsating red level, to express maximum irritation. At the same time, the noise that Sleepy emits intensifies as the anger variable is increased.

## The Components

### General Components
- 1x Arduino Uno
- 1x Breadboard
- A lot of wires

### Sensors
- 1x PIR 
- 1x LDR 

### Outputs
- 1x LED RGB
- 1x Buzzer

### Structure
- Recycled cardboard
- Styrofoam Ball
- Paint
