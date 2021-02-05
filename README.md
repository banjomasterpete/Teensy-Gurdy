# Teensy-Gurdy
Code and design files for building your own hurdy gurdy-inspired, Teensy-powered synthesizer!

Howdy friends, here's the code I'm currently running in the Teensy Gurdy video with some added comments and the STL's for the case. 
I didn't initially intend for others to be looking at this so some details are going to be hazy, 
I highly suggest you watch the Notes and Volts Teensy synthesizer series as I learned how to build this project from watching my old pal Dave. 

Here's a parts list for the project:
15x 10kA potentiometers
2x SPDT switches
1x encoder (I used this one: https://www.ebay.com/itm/Rotary-Encoder-1000P-R-Incremental-Optical-Shaft-Working-Measurement-DC-5-24V-US/233759257400?hash=item366d233338:g:rYAAAOSwpE5fl7l~)
12x conductive surfaces (I used custom PCB's but you can use lots of things. Adafruit's page has some suggestions about what works best)
1x Adafruit MPR121 breakout board
1x Teensy 3.2
1x Teensy 3.x Audio Shield (Not strictly necessary unless you want stereo audio but you will need to redo some code to use the 3.2's built in DAC if you don't want this)
1x CD4067/ 74HC4067 multiplexer chip
1x 5V regulator (Use something suitable like a 7805 and power it per the datasheet. I'm just a guy on the internet, don't blow up your Teensy!)
1x Some kinda way to get electricity to the regulator, a battery might be cool? The hole on the faceplate is sized for this type: https://www.ebay.com/itm/Panel-Mount-2-1mm-DC-barrel-jack/263111763480?hash=item3d42aee618:g:uKIAAOSwOg9ZeyIZ
1x Some kinda way to get audio out. The hole on the faceplate is sized for a 1/4" audio jack
1x USB connector. I didn't build one of these into mine but I wish I did
1x A knob, I pulled one off of a dresser but make sure you have at least one so you can get your clothes out

Resources that I used:
Notes and Volts: https://www.youtube.com/watch?v=UJcZxyB5rVc
Adafruit: https://learn.adafruit.com/adafruit-mpr121-12-key-capacitive-touch-sensor-breakout-tutorial
