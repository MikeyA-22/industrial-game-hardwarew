# Game Hardware Controller Mario-Kart
This is a simple hardware controller system written in GDscript for the engine side of things and in C++ for the Arduino/ESP32 code.

## Team Members
* Michael Atteh
* Jacob Janowitz
* KC Ozoemene

## Task
We were given the task of prototyping a game controller using equipment that we had, and creating a game for it to be used for, and out of the given options, we chose mario-kart, as it would translate well to what we had, an esp32, a button and an IMU.

## Design
After deciding what game to make, we then designed our controller using tinkerCAD. This is our design, made by **Jacob Janowitz**:

![alt text](image.png)

Our design features a potentiometer in place of our IMU, and uses LEDS to visualize the digital and analog information we are capturing.

<video controls src="Screen Recording 2026-02-18 220151.mp4" title="Wiring design showcase">Here is a video of the wiring simulation</video>

## Implementation Arduino/C++

