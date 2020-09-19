# go-back-to-bed-client
We have been trying to experiment with ways to let our child know that when he wakes up if it's alright to get up and get out of bed or if he should remain in bed until an acceptable hour. This child goes through phases where he either wakes up at midnight and plays/talks/sings/etc until we go into his room and remind him that it's the middle of the night or he is awake at a reasonable time of the morning yet he will not get out of bed until someone explicitly gets him out of bed. Unfortunately our child has a disability that prevents him from understanding how "morning works" so we have are experimenting with a signal that he can independently use to know if he should go back to bed or that it's alright to get up.  

# So what's the concept?

This isn't an alarm and isn't designed to wake him up, although that is an option we'd like to explore later. What we are looking for is a signal (maybe in the form of an LED?) that is easy to see from across the room, is not disruptive to sleep, and can clearly indicate a message.

Initially, the we are thinking that there would be an online app (that is mobile first, desktop second) that allows us to login and configure our device rules (brightness, color, any light animations, schedules, etc). The physical device should query a REST endpoint (exposed by that app) to determine what message should be displaying and how it should be displaying that message at any given time.

## Prototype Layout
![Image of prototype](/images/fritzing_diagram.png)

## Parts List

 - [Arduino UNO WiFi Rev.2](https://store.arduino.cc/usa/arduino-uno-wifi-rev2)
 - Breadboard
 - [https://www.sunfounder.com/i2c-2004-lcd-module-shield-for-arduino.html](20x4 LCD Module Shield)
 - [NeoPixel Ring - 24 x 5050 RGB LED](https://www.adafruit.com/product/1586)

## Why is this project so sloppy?
Two reasons, it's a prototype and I'm learning.

## Major outstanding issues
- All the things
