# Guitar Sound Processing on BeagleBone Black Platform

## Content

1. Source files for digital sound processing
2. BeagleBone Audio Cape schematics
3. Prototype

## 1. Source files for digital sound processing
Digital sound processing is dependent on JACK library and all necessary dependencies can be installed
by executing setup.sh script. Ensure that you have internet connection on BeagleBone Black over USB or
Ethernet interface. 

Main program is DEP_main which can be built by executing make in Digital_effects_processor directory.
For controlling parameters of digital sound processing use AudioRack application which is Node.Js. 
application.


## 2. BeagleBone Audio Cape schematics 
Audio Cape schematics can be found in Schematics directory. They were created with Altium Designer 14.


## 3. Prototype
Below you can see images of prototype Digital Guitar Effects processor:

![Cape board](/images/Cape.JPG)
![Cape board installed on BeagleBone Black](/images/CapeBBB.JPG)
![Installing BeagleBone Black in box 1](/images/Installing_1.JPG)
![Installing BeagleBone Black in box 2](/images/Installing_2.JPG)
![Installing BealgeBone Black in box 3](/images/Installing_3.JPG)
![Final look](/image/Final.JPG)




