#!/bin/bash

echo "Installing Digital Effects Processor Enviroment...."
route add default gw 192.168.7.1 && echo "Internet connection rerouted to USB"
echo "Adjusting time...."
ntpdate time.nist.gov 
apt-get update
echo "Installing FFTW3 library...."
apt-get install libfftw3-dev libfftw3-doc
echo "Adding rpi.autostatic repository...."
wget -q -O - http://rpi.autostatic.com/autostatic.gpg.key | sudo apt-key add -
sudo wget -q -O /etc/apt/sources.list.d/autostatic-audio-raspbian.list http://rpi.autostatic.com/autostatic-audio-raspbian.list
sudo apt-get update
echo "Installing JACK library...."
apt-get install libjack-jackd2-0=1.9.8~dfsg.4+20120529git007cdc37-5+fixed1~raspbian1 
apt-get install libjack-jackd2-dev=1.9.8~dfsg.4+20120529git007cdc37-5+fixed1~raspbian1
apt-get install jackd2=1.9.8~dfsg.4+20120529git007cdc37-5+fixed1~raspbian1
npm install socket.io
npm install node-ipc
